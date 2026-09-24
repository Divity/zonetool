#include "stdafx.hpp"
#include "Utils/Math.hpp"
#include "../Include.hpp"

#include "ClipMap.hpp"
#include "ClipMapCollision.hpp"
#include "XModel.hpp"
#include "ParticleSystem.hpp"

#include "Common/havok_builder.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <regex>
#include <string>
#include <numbers>

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		namespace
		{
			constexpr auto BRUSHMODEL_PHYSICS_ASSET = "scriptbrushmodeldummydefault";

			constexpr auto PHYSICS_ASSET_KEY = "51961";

			constexpr auto TRIGGER_PHYSICS_ASSET = "triggermodeldummydefault";

			constexpr auto ENTS_TRIGGER_CONTENTS = 0xC7FFBFFFu;

			constexpr auto ENTS_BRUSH_BASIS = 1ull << 48;

			constexpr auto ENTS_TRIGGER_SURF_FLAGS = 0x40080ull;

			bool trigger_shapes_enabled()
			{
				const auto* env = std::getenv("ZT_HAVOK_TRIGGER_SHAPES");
				return !(env && env[0] == '0');
			}

			bool ents_shapes_enabled()
			{
				const auto* env = std::getenv("ZT_HAVOK_ENTS_SHAPES");
				return !(env && env[0] == '0');
			}

			void convert_map_triggers(const MapTriggers& src, IW7::MapTriggers& dst,
				allocator& allocator)
			{
				dst.count = src.count;
				dst.models = allocator.allocate<IW7::TriggerModel>(src.count);
				for (unsigned int i = 0; i < src.count; i++)
				{
					dst.models[i].contents = src.models[i].contents;
					dst.models[i].hullCount = src.models[i].hullCount;
					dst.models[i].firstHull = src.models[i].firstHull;

					dst.models[i].windingCount = 0;
					dst.models[i].firstWinding = 0;
					dst.models[i].flags = 0;

					dst.models[i].physicsAsset = nullptr;
					dst.models[i].physicsShapeOverrideIdx = 0xFFFF;
				}

				dst.hullCount = src.hullCount;
				REINTERPRET_CAST_SAFE_TO_FROM(dst.hulls, src.hulls);
				dst.slabCount = src.slabCount;
				REINTERPRET_CAST_SAFE_TO_FROM(dst.slabs, src.slabs);

				dst.windingCount = 0;
				dst.windings = nullptr;
				dst.windingPointCount = 0;
				dst.windingPoints = nullptr;
			}

			void audit_trigger_references(const char* entity_string, const int num_chars,
				const unsigned int model_count)
			{
				if (!entity_string || num_chars <= 0)
				{
					return;
				}

				const std::string ents{entity_string, static_cast<size_t>(num_chars)};

				auto refs = 0;
				auto out_of_range = 0;
				auto highest = -1;

				for (size_t pos = ents.find("\"?"); pos != std::string::npos;
					pos = ents.find("\"?", pos + 2))
				{
					auto digits = pos + 2;
					auto end = digits;
					while (end < ents.size() && ents[end] >= '0' && ents[end] <= '9')
					{
						end++;
					}

					if (end == digits || end >= ents.size() || ents[end] != '"')
					{
						continue;
					}

					const auto index = std::atoi(ents.substr(digits, end - digits).data());
					refs++;
					highest = std::max(highest, index);
					if (index < 0 || static_cast<unsigned int>(index) >= model_count)
					{
						out_of_range++;
					}
				}

				ZONETOOL_INFO("mapents: %u trigger models, %d referenced by entities "
					"(highest \"?%d\")", model_count, refs, highest);

				if (out_of_range > 0)
				{
					ZONETOOL_WARNING("mapents: %d entity trigger reference(s) point past the "
						"end of the %u-model trigger array", out_of_range, model_count);
				}
			}

			bool same_bounds(const Bounds& left, const Bounds& right)
			{
				constexpr auto epsilon = 0.01f;
				for (auto axis = 0; axis < 3; axis++)
				{
					if (std::fabs(left.midPoint[axis] - right.midPoint[axis]) > epsilon ||
						std::fabs(left.halfSize[axis] - right.halfSize[axis]) > epsilon)
					{
						return false;
					}
				}
				return true;
			}

			int trigger_for_cmodel(const clipMap_t* clipmap, const unsigned int cmodel)
			{
				if (!clipmap || cmodel >= clipmap->numSubModels)
				{
					return -1;
				}

				const auto& bounds = clipmap->cmodels[cmodel].bounds;
				auto match = -1;
				for (unsigned int model = 0; model < clipmap->mapEnts->trigger.count; model++)
				{
					const auto& trigger = clipmap->mapEnts->trigger.models[model];
					for (unsigned int hull = trigger.firstHull;
						hull < trigger.firstHull + trigger.hullCount; hull++)
					{
						if (hull >= clipmap->mapEnts->trigger.hullCount ||
							!same_bounds(bounds, clipmap->mapEnts->trigger.hulls[hull].bounds))
						{
							continue;
						}

						if (match != -1 && match != static_cast<int>(model))
						{
							return -1;
						}
						match = static_cast<int>(model);
					}
				}
				return match;
			}

			std::string fix_entity_model_references(const clipMap_t* clipmap,
				const std::string& source)
			{
				static const std::regex classname_expr(
					R"entity("classname"\s+"([^"]*)")entity");
				static const std::regex model_expr(
					R"entity("model"\s+"([*?])(\d+)")entity");

				std::string result;
				result.reserve(source.size() + 128);
				size_t cursor = 0;
				auto rewritten_triggers = 0;
				auto wired_triggers = 0;
				auto wired_brushmodels = 0;

				while (cursor < source.size())
				{
					const auto open = source.find('{', cursor);
					if (open == std::string::npos)
					{
						result.append(source, cursor, std::string::npos);
						break;
					}
					const auto close = source.find('}', open + 1);
					if (close == std::string::npos)
					{
						result.append(source, cursor, std::string::npos);
						break;
					}

					result.append(source, cursor, open - cursor);
					auto entity = source.substr(open, close - open + 1);
					std::smatch classname;
					std::smatch model;
					if (std::regex_search(entity, classname, classname_expr) &&
						std::regex_search(entity, model, model_expr))
					{
						const auto entity_class = classname[1].str();
						const auto model_kind = model[1].str()[0];
						const auto model_index = static_cast<unsigned int>(
							std::strtoul(model[2].str().c_str(), nullptr, 10));

						auto is_trigger_model = model_kind == '?';
						if (entity_class.starts_with("trigger_") && model_kind == '*')
						{
							const auto trigger = trigger_for_cmodel(clipmap, model_index);
							if (trigger >= 0)
							{
								const auto value_pos = static_cast<size_t>(model.position(2));
								const auto value_len = static_cast<size_t>(model.length(2));
								entity.replace(value_pos, value_len, std::to_string(trigger));
								entity[static_cast<size_t>(model.position(1))] = '?';
								rewritten_triggers++;
								is_trigger_model = true;
							}
						}

						if (is_trigger_model && trigger_shapes_enabled() &&
							entity.find(std::string("\n") + PHYSICS_ASSET_KEY + " ") ==
							std::string::npos)
						{
							entity.insert(entity.size() - 1, std::string(PHYSICS_ASSET_KEY)
								+ " \"" + TRIGGER_PHYSICS_ASSET + "\"\n");
							wired_triggers++;
						}
						else if (entity_class == "script_brushmodel" && model_kind == '*' &&
							entity.find(std::string("\n") + PHYSICS_ASSET_KEY + " ") ==
							std::string::npos)
						{
							entity.insert(entity.size() - 1, std::string(PHYSICS_ASSET_KEY)
								+ " \"" + BRUSHMODEL_PHYSICS_ASSET + "\"\n");
							wired_brushmodels++;
						}
					}

					result.append(entity);
					cursor = close + 1;
				}

				if (rewritten_triggers || wired_brushmodels || wired_triggers)
				{
					ZONETOOL_INFO("mapents: rewrote %d trigger model reference(s), wired %d "
						"script brush model and %d trigger physics asset(s)", rewritten_triggers,
						wired_brushmodels, wired_triggers);
				}
				return result;
			}
		}

		IW7::ScriptableDef* generate_scriptable_def_from_dynent(const DynEntityDef* dynent, allocator& allocator)
		{
			auto generate_name = [](const DynEntityDef* dynent) -> std::string
			{
				std::string name;
				name.reserve(96);
				name.append(dynent->xModel ? dynent->xModel->name : "dynent");
				name.append("_destruct_");
				name.append(std::to_string(dynent->health));
				return name;
			};

			auto* new_def = allocator.allocate<IW7::ScriptableDef>();
			new_def->name = allocator.duplicate_string(generate_name(dynent));
			new_def->flags = IW7::SCRIPTABLE_DEFFLAG_HAS_HEALTH | 0x80;
			new_def->type = 0;
			new_def->nextScriptableDef = nullptr;
			new_def->numParts = 1;
			new_def->parts = allocator.allocate<IW7::ScriptablePartDef>(1);
			new_def->maxNumDynEntsRequired = 0;
			new_def->partCount = 1;
			new_def->serverInstancedPartCount = 0;
			new_def->serverControlledPartCount = 0;
			new_def->maxNumDynEntPartsBase = 1;
			new_def->maxNumDynEntPartsForSpawning = 0;
			new_def->eventStreamSizeRequiredServer = 0;
			new_def->eventStreamSizeRequiredClient = 0;
			new_def->eventStreamSize = 4;
			new_def->ffMemCost = 0;
			new_def->animationTreeName = 0;
			new_def->animationTreeDef[0] = nullptr;
			new_def->animationTreeDef[1] = nullptr;
			new_def->numXModels = dynent->xModel ? 1 : 0;
			new_def->models = new_def->numXModels
				? allocator.allocate<IW7::XModel PTR64>(new_def->numXModels)
				: nullptr;

			if (new_def->models)
			{
				new_def->models[0] = reinterpret_cast<IW7::XModel*>(dynent->xModel);
			}

			auto* part = new_def->parts;
			part->name = "";
			part->flags = 0x180;
			part->flatId = 0;
			part->serverInstanceFlatId = 0;
			part->serverControlledFlatId = 0;
			part->eventStreamBufferOffsetServer = 0;
			part->eventStreamBufferOffsetClient = 0;
			part->eventStreamSize = 0;
			part->numStates = 2;
			part->states = allocator.allocate<IW7::ScriptableStateDef>(2);

			auto* healthy_state = &part->states[0];

			healthy_state->base.name = allocator.duplicate_string("healthy");
			healthy_state->base.flags = 0x80;
			healthy_state->base.numEvents = 1;
			healthy_state->base.events = allocator.allocate<IW7::ScriptableEventDef>(1);
			healthy_state->type = IW7::Scriptable_StateType_Health;

			healthy_state->data.health.base = &healthy_state->base;

			healthy_state->data.health.health = std::max(dynent->health, 1);
			healthy_state->data.health.minimumDamage = 0;
			healthy_state->data.health.damagePropagationFromParent = 1.0f;
			healthy_state->data.health.damagePropagationFromChild = 1.0f;
			healthy_state->data.health.script_id = nullptr;
			healthy_state->data.health.scrScript_id = 0;

			auto* model_event = &healthy_state->base.events[0];
			model_event->base.name = "";
			model_event->type = IW7::Scriptable_EventType_Model;
			model_event->data.model.base = &model_event->base;
			model_event->data.model.model = reinterpret_cast<IW7::XModel*>(dynent->xModel);
			model_event->data.model.dynamicSimulation = false;
			model_event->data.model.activatePhysics = false;
			model_event->data.model.hudOutlineColor = 0;
			model_event->data.model.hudOutlineActive = true;
			model_event->data.model.hudOutlineFill = false;
			model_event->data.model.neverMoves = false;

			auto* dead_state = &part->states[1];

			dead_state->base.name = allocator.duplicate_string("dead");
			dead_state->base.flags = 0;
			dead_state->base.numEvents = dynent->destroyFx ? 2 : 1;
			dead_state->base.events = allocator.allocate<IW7::ScriptableEventDef>(dead_state->base.numEvents);
			dead_state->type = IW7::Scriptable_StateType_Simple;

			dead_state->data.simple.base = allocator.allocate<IW7::ScriptableStateBaseDef>();
			dead_state->data.simple.base->name = dead_state->base.name;
			dead_state->data.simple.base->flags = dead_state->base.flags;
			dead_state->data.simple.base->numEvents = dead_state->base.numEvents;
			dead_state->data.simple.base->events = dead_state->base.events;

			auto* hide_event = &dead_state->base.events[0];
			hide_event->base.name = "";
			hide_event->type = IW7::Scriptable_EventType_Model;
			hide_event->data.model.base = &hide_event->base;
			hide_event->data.model.model = nullptr;
			hide_event->data.model.hudOutlineColor = 1;
			hide_event->data.model.hudOutlineActive = false;
			hide_event->data.model.hudOutlineFill = false;
			hide_event->data.model.neverMoves = false;
			hide_event->data.model.dynamicSimulation = false;
			hide_event->data.model.activatePhysics = false;

			if (dynent->destroyFx)
			{
				auto* destroy_event = &dead_state->base.events[1];
				destroy_event->base.name = "";
				destroy_event->type = IW7::Scriptable_EventType_PFX;
				destroy_event->data.particleFX.base = &destroy_event->base;
				destroy_event->data.particleFX.stateful = false;
				auto* vfx = allocator.manual_allocate<IW7::ParticleSystemDef>(sizeof(const char*));
				vfx->name = allocator.duplicate_string(dynent->destroyFx->name);
				destroy_event->data.particleFX.effectDef.u.vfx = vfx;
				destroy_event->data.particleFX.effectDef.type = IW7::FX_COMBINED_VFX;
				destroy_event->data.particleFX.eventStreamBufferOffsetClient = 0;
			}

			return new_def;
		}

		IW7::MapEnts* generate_mapents(clipMap_t* clipmap, allocator& allocator,
			const std::vector<ZoneTool::IW7::havok::builder::shape_tag>& world_tags)
		{
			const auto* asset = clipmap->mapEnts;
			if (!asset)
			{
				ZONETOOL_ERROR("clipmap \"%s\" has no mapents -- entities and triggers cannot "
					"be converted", clipmap->name);
				return nullptr;
			}

			auto* new_asset = allocator.allocate<IW7::MapEnts>();
			REINTERPRET_CAST_SAFE(name);

			std::string entity_string;
			if (ZoneTool::currentlinkermode == ZoneTool::linker_mode::iw5)
			{
				entity_string = ::mapents::converter::iw5::convert_mapents_ids(
					std::string{ asset->entityString, static_cast<size_t>(asset->numEntityChars) });
			}
			else
			{
				entity_string.assign(asset->entityString, static_cast<size_t>(asset->numEntityChars));
			}
			entity_string = fix_entity_model_references(clipmap, entity_string);

			while (!entity_string.empty() && (entity_string.back() == '\n'
				|| entity_string.back() == '\r' || entity_string.back() == '\0'))
			{
				entity_string.pop_back();
			}

			new_asset->entityString = const_cast<char*>(allocator.duplicate_string(entity_string));
			new_asset->numEntityChars = static_cast<int>(entity_string.size()) + 1;

			convert_map_triggers(asset->trigger, new_asset->trigger, allocator);
			convert_map_triggers(asset->clientTrigger.trigger, new_asset->clientTrigger.trigger,
				allocator);

			audit_trigger_references(new_asset->entityString, new_asset->numEntityChars,
				new_asset->trigger.count);

			COPY_VALUE(clientTrigger.triggerStringLength);
			REINTERPRET_CAST_SAFE(clientTrigger.triggerString);

			auto allocate_uchar = [&](const unsigned char default_value = -1)
			{
				const auto count = asset->clientTrigger.trigger.count;
				auto memory = allocator.allocate<unsigned char>(asset->clientTrigger.trigger.count);
				std::fill(memory, memory + count, default_value);
				return memory;
			};

			auto allocate = [&](const short default_value = -1)
			{
				const auto count = asset->clientTrigger.trigger.count;
				auto memory = allocator.allocate<short>(asset->clientTrigger.trigger.count);
				std::fill(memory, memory + count, default_value);
				return memory;
			};

			new_asset->clientTrigger.triggerType = allocate_uchar(0);
			new_asset->clientTrigger.visionSetTriggers = allocate();

			for (auto i = 0; i < asset->clientTrigger.trigger.count; i++)
			{
				if ((asset->clientTrigger.triggerType[i] & CLIENT_TRIGGER_VISIONSET) != 0)
				{
					new_asset->clientTrigger.triggerType[i] |= IW7::CLIENT_TRIGGER_VISIONSET;

					new_asset->clientTrigger.visionSetTriggers[i] = asset->clientTrigger.triggerStringOffsets[i];
				}
			}

			new_asset->clientTrigger.origins = reinterpret_cast<float(*__ptr64)[3]>(asset->clientTrigger.origins);
			new_asset->clientTrigger.scriptDelay = asset->clientTrigger.scriptDelay;
			new_asset->clientTrigger.audioTriggers = asset->clientTrigger.audioTriggers;
			new_asset->clientTrigger.blendLookup = allocate(); // todo?
			new_asset->clientTrigger.npcTriggers = allocate(); // todo?

			new_asset->clientTrigger.audioStateIds = allocator.allocate<short>(asset->clientTrigger.trigger.count);
			new_asset->clientTrigger.audioRvbPanInfo = allocator.allocate<IW7::CTAudRvbPanInfo>(asset->clientTrigger.trigger.count);
			new_asset->clientTrigger.transientIndex = allocator.allocate<short>(asset->clientTrigger.trigger.count);
			for (unsigned int i = 0; i < asset->clientTrigger.trigger.count; i++)
			{
				new_asset->clientTrigger.audioStateIds[i] = -1;

				new_asset->clientTrigger.audioRvbPanInfo[i].hasCustomPosition = false;
				// has some more data..

				new_asset->clientTrigger.transientIndex[i] = 0;
			}

			new_asset->clientTrigger.linkTo = allocator.allocate<IW7::ClientEntityLinkToDef PTR64>(asset->clientTrigger.trigger.count);
			for (unsigned int i = 0; i < asset->clientTrigger.trigger.count; i++)
			{
				new_asset->clientTrigger.linkTo[i] = nullptr;
			}

			new_asset->clientTriggerBlend.numClientTriggerBlendNodes = 0;
			new_asset->clientTriggerBlend.blendNodes = nullptr;

			new_asset->spawnList.spawnsCount = 0;
			new_asset->spawnList.spawns = nullptr; // later: generate spawnents with mapents2spawns

			new_asset->splineList.splineCount = 0;
			new_asset->splineList.splines = nullptr;

			new_asset->havokEntsShapeDataSize = 0;
			new_asset->havokEntsShapeData = nullptr;

			std::vector<unsigned short> cmodel_shape_index(clipmap->numSubModels, 0xFFFF);
			{
				ZoneTool::IW7::havok::builder::ents_input ents{};
				ents.world_tags = world_tags;
				if (world_tags.empty())
				{
					ZONETOOL_WARNING("mapents: no world shape tag table for \"%s\" -- the "
						"world mesh's tags will resolve against the ents table instead of "
						"its own, giving world surfaces the wrong filters", asset->name);
				}

				const auto dump_obj = collision::obj_dump_enabled();
				std::vector<collision::hull_group> ents_obj;

				auto brush_models = collision::extract_brush_models(clipmap);
				for (auto& model : brush_models)
				{
					if (dump_obj)
					{
						ents_obj.emplace_back(collision::hull_group{
							va("brushmodel_%u", model.index), model.hulls});
					}

					ZoneTool::IW7::havok::builder::ents_shape shape{};
					auto contents = model.contents;
					const auto* solid_as_clip = std::getenv("ZT_HAVOK_SOLID_AS_CLIP");
					if ((contents & 0x1) && solid_as_clip && solid_as_clip[0] == '1')
					{
						auto mask = 0x00031640u;
						const auto* env = std::getenv("ZT_HAVOK_SOLID_CONTENTS");
						if (env && env[0])
						{
							char* end = nullptr;
							const auto value = std::strtoul(env, &end, 0);
							if (end != env && value)
							{
								mask = static_cast<unsigned int>(value);
							}
						}
						contents = (contents & ~0x1) | static_cast<int>(mask);
					}
					shape.contents = contents;
					shape.entity_contents = static_cast<unsigned int>(contents);
					shape.material_crc = model.material_crc;
					shape.user_data = ENTS_BRUSH_BASIS | model.surface_flags;
					shape.name = va("%s:brushmodel %u", asset->name, model.index);

					for (auto& hull : model.hulls)
					{
						ZoneTool::IW7::havok::builder::polytope convex{};
						convex.verts = std::move(hull.verts);
						for (auto& face : hull.faces)
						{
							ZoneTool::IW7::havok::builder::polytope_face out{};
							std::memcpy(out.plane, face.plane, sizeof(float[4]));
							out.indices = std::move(face.indices);
							convex.faces.emplace_back(std::move(out));
						}
						shape.convexes.emplace_back(std::move(convex));
					}

					if (model.index < cmodel_shape_index.size())
					{
						cmodel_shape_index[model.index] =
							static_cast<unsigned short>(ents.shapes.size());
					}
					ents.shapes.emplace_back(std::move(shape));
				}
				decltype(brush_models){}.swap(brush_models);

				std::vector<unsigned short> trigger_shape_index(asset->trigger.count, 0xFFFF);
				if (trigger_shapes_enabled())
				{
					for (unsigned int t = 0; t < asset->trigger.count; t++)
					{
						auto hulls = collision::extract_trigger_hulls(asset->trigger, t);
						if (hulls.empty())
						{
							continue;
						}

						if (dump_obj)
						{
							ents_obj.emplace_back(collision::hull_group{
								va("trigger_%u", t), hulls});
						}

						ZoneTool::IW7::havok::builder::ents_shape shape{};
						shape.contents = static_cast<int>(ENTS_TRIGGER_CONTENTS);
						shape.entity_contents = ENTS_TRIGGER_CONTENTS;
						shape.user_data = ENTS_BRUSH_BASIS | ENTS_TRIGGER_SURF_FLAGS;
						shape.name = va("%s:trigger %u", asset->name, t);

						for (auto& hull : hulls)
						{
							ZoneTool::IW7::havok::builder::polytope convex{};
							convex.verts = std::move(hull.verts);
							for (auto& face : hull.faces)
							{
								ZoneTool::IW7::havok::builder::polytope_face out{};
								std::memcpy(out.plane, face.plane, sizeof(float[4]));
								out.indices = std::move(face.indices);
								convex.faces.emplace_back(std::move(out));
							}
							shape.convexes.emplace_back(std::move(convex));
						}

						trigger_shape_index[t] = static_cast<unsigned short>(ents.shapes.size());
						ents.shapes.emplace_back(std::move(shape));
					}
				}

				if (dump_obj && !ents_obj.empty())
				{
					collision::write_hulls_obj(
						collision::obj_dump_path(asset->name, ".ents.obj"), ents_obj,
						ents.scale);
				}
				decltype(ents_obj){}.swap(ents_obj);

				ZoneTool::IW7::havok::builder::ents_tag_merge tag_merge{};
				auto blob = ents_shapes_enabled()
					? ZoneTool::IW7::havok::builder::build_ents_shape_list(ents, &tag_merge)
					: std::vector<std::uint8_t>{};
				decltype(ents.shapes){}.swap(ents.shapes);
				decltype(ents.world_tags){}.swap(ents.world_tags);

				if (!blob.empty())
				{
					ZONETOOL_INFO("mapents: havok tag table -- world %zu entries, ents %zu "
						"(%zu reused from the world table, %zu appended)",
						tag_merge.prefix, tag_merge.total, tag_merge.reused,
						tag_merge.appended);
				}

				if (dump_obj)
				{
					collision::write_blob(
						collision::obj_dump_path(asset->name, ".ents.hkx"),
						blob.data(), blob.size());
				}

				if (!ents_shapes_enabled())
				{
					ZONETOOL_WARNING("mapents: ZT_HAVOK_ENTS_SHAPES=0 -- emitting a null havok "
						"ents shape list; brush model entities will have no physics body");
				}

				if (!blob.empty())
				{
					auto* memory = allocator.allocate<char>(blob.size());
					std::memcpy(memory, blob.data(), blob.size());

					new_asset->havokEntsShapeData = memory;
					new_asset->havokEntsShapeDataSize = static_cast<unsigned int>(blob.size());
				}
				else
				{
					ZONETOOL_WARNING("mapents: no havok ents shape list generated for \"%s\" -- "
						"brush model entities may fault on link", asset->name);
					std::fill(cmodel_shape_index.begin(), cmodel_shape_index.end(),
						static_cast<unsigned short>(0xFFFF));
					std::fill(trigger_shape_index.begin(), trigger_shape_index.end(),
						static_cast<unsigned short>(0xFFFF));
				}
				decltype(blob){}.swap(blob);

				auto shaped_triggers = 0;
				IW7::PhysicsAsset* trigger_physics = nullptr;
				for (unsigned int t = 0; t < new_asset->trigger.count; t++)
				{
					if (t >= trigger_shape_index.size() || trigger_shape_index[t] == 0xFFFF)
					{
						continue;
					}

					if (!trigger_physics)
					{
						trigger_physics = allocator.allocate<IW7::PhysicsAsset>();
						trigger_physics->name = TRIGGER_PHYSICS_ASSET;

						ZoneTool::IW7::havok::builder::physics_asset_input physics{};
						physics.body_name = "triggermodeldummy";

						const auto physics_blob =
							ZoneTool::IW7::havok::builder::build_physics_asset(physics);
						if (!physics_blob.empty())
						{
							auto* memory = allocator.allocate<char>(physics_blob.size());
							std::memcpy(memory, physics_blob.data(), physics_blob.size());
							trigger_physics->havokData = memory;
							trigger_physics->havokDataSize =
								static_cast<unsigned int>(physics_blob.size());
						}

						trigger_physics->numRigidBodies = 1;
						trigger_physics->numSFXEventAssets = 1;
						trigger_physics->sfxEventAssets =
							allocator.allocate<IW7::PhysicsSFXEventAsset PTR64>(1);
						trigger_physics->numVFXEventAssets = 1;
						trigger_physics->vfxEventAssets =
							allocator.allocate<IW7::PhysicsVFXEventAsset PTR64>(1);
					}

					new_asset->trigger.models[t].physicsShapeOverrideIdx = trigger_shape_index[t];
					new_asset->trigger.models[t].physicsAsset = trigger_physics;
					shaped_triggers++;
				}

				if (shaped_triggers)
				{
					ZONETOOL_INFO("mapents: %d triggers given havok shapes "
						"(ZT_HAVOK_TRIGGER_SHAPES), backed by \"%s\"", shaped_triggers,
						TRIGGER_PHYSICS_ASSET);
				}
			}

			IW7::ClipInfo* info = allocator.allocate<IW7::ClipInfo>();
			info->planeCount = clipmap->info.planeCount;
			info->planes = allocator.allocate<IW7::cplane_s>(info->planeCount);
			for (auto i = 0; i < info->planeCount; i++)
			{
				memcpy(&info->planes[i], &clipmap->info.planes[i], sizeof(cplane_s));
			}

			IW7::PhysicsAsset* brushmodel_physics = nullptr;
			{
				auto shaped = 0;
				for (const auto index : cmodel_shape_index)
				{
					shaped += index != 0xFFFF ? 1 : 0;
				}

				if (shaped > 0)
				{
					brushmodel_physics = allocator.allocate<IW7::PhysicsAsset>();
					brushmodel_physics->name = BRUSHMODEL_PHYSICS_ASSET;

					ZoneTool::IW7::havok::builder::physics_asset_input physics{};
					physics.body_name = "scriptbrushmodeldummy";

					const auto blob = ZoneTool::IW7::havok::builder::build_physics_asset(physics);
					if (!blob.empty())
					{
						auto* memory = allocator.allocate<char>(blob.size());
						std::memcpy(memory, blob.data(), blob.size());
						brushmodel_physics->havokData = memory;
						brushmodel_physics->havokDataSize =
							static_cast<unsigned int>(blob.size());
					}

					brushmodel_physics->numRigidBodies = 1;
					brushmodel_physics->numConstraints = 0;
					brushmodel_physics->numSFXEventAssets = 1;
					brushmodel_physics->sfxEventAssets =
						allocator.allocate<IW7::PhysicsSFXEventAsset PTR64>(1);
					brushmodel_physics->numVFXEventAssets = 1;
					brushmodel_physics->vfxEventAssets =
						allocator.allocate<IW7::PhysicsVFXEventAsset PTR64>(1);

					ZONETOOL_INFO("mapents: %d brush models given havok shapes, backed by a "
						"generated \"%s\" (%zu byte blob)", shaped, BRUSHMODEL_PHYSICS_ASSET,
						blob.size());
				}
			}

			new_asset->numSubModels = clipmap->numSubModels;
			new_asset->cmodels = allocator.allocate<IW7::cmodel_t>(clipmap->numSubModels);
			for (unsigned int i = 0; i < clipmap->numSubModels; i++)
			{
				memcpy(&new_asset->cmodels[i].bounds, &clipmap->cmodels[i].bounds, sizeof(Bounds));
				new_asset->cmodels[i].radius = clipmap->cmodels[i].radius;
				new_asset->cmodels[i].info = info;

				const auto shape_index = i == 0 ? 0xFFFF : cmodel_shape_index[i];
				new_asset->cmodels[i].physicsShapeOverrideIdx = shape_index;
				new_asset->cmodels[i].physicsAsset =
					shape_index != 0xFFFF ? brushmodel_physics : nullptr;

				new_asset->cmodels[i].navObstacleIdx = i == 0 ? 0 : 0xFFFF;
				//new_asset->cmodels[i].edgeFirstIndex = 0;
			}

			new_asset->dynEntCount[0] = clipmap->dynEntCount[0];
			new_asset->dynEntCount[1] = clipmap->dynEntCount[1];

			unsigned short reserved_dynents = 64;
			new_asset->dynEntCount[0] += reserved_dynents;

			unsigned short total_dynents = new_asset->dynEntCount[0] + new_asset->dynEntCount[1];
			new_asset->dynEntCountTotal = total_dynents;

			new_asset->dynEntDefList[0] = allocator.allocate<IW7::DynEntityDef>(new_asset->dynEntCount[0]);
			new_asset->dynEntPoseList[0][0] = allocator.allocate<IW7::DynEntityPose>(new_asset->dynEntCount[0]);
			new_asset->dynEntPoseList[1][0] = allocator.allocate<IW7::DynEntityPose>(new_asset->dynEntCount[0]);
			new_asset->dynEntClientList[0][0] = allocator.allocate<IW7::DynEntityClient>(new_asset->dynEntCount[0]);
			new_asset->dynEntClientList[1][0] = allocator.allocate<IW7::DynEntityClient>(new_asset->dynEntCount[0]);

			new_asset->dynEntDefList[1] = allocator.allocate<IW7::DynEntityDef>(new_asset->dynEntCount[1]);
			new_asset->dynEntPoseList[0][1] = allocator.allocate<IW7::DynEntityPose>(new_asset->dynEntCount[1]);
			new_asset->dynEntPoseList[1][1] = allocator.allocate<IW7::DynEntityPose>(new_asset->dynEntCount[1]);
			new_asset->dynEntClientList[0][1] = allocator.allocate<IW7::DynEntityClient>(new_asset->dynEntCount[1]);
			new_asset->dynEntClientList[1][1] = allocator.allocate<IW7::DynEntityClient>(new_asset->dynEntCount[1]);

			new_asset->dynEntGlobalIdList[0] = allocator.allocate<IW7::DynEntityGlobalId>(new_asset->dynEntCountTotal);
			new_asset->dynEntGlobalIdList[1] = allocator.allocate<IW7::DynEntityGlobalId>(new_asset->dynEntCountTotal);

			struct generated_scriptable
			{
				IW7::ScriptableDef* def;
				GfxPlacement pose;
			};
			std::vector<generated_scriptable> scriptable_defs;
			std::array<int, IW7::DYNENT_TYPE_COUNT> dynent_type_count{};

			const auto copy_dynents = [&](const auto index)
			{
				for (auto i = 0; i < new_asset->dynEntCount[index] - (index == 0 ? reserved_dynents : 0); i++)
				{
					{
						auto* new_dynent_def = &new_asset->dynEntDefList[index][i];
						auto* dynent_def = &clipmap->dynEntDefList[index][i];

						const auto convert_type = [](DynEntityType type) -> IW7::DynEntityType
						{
							switch (type)
							{
							case DYNENT_TYPE_INVALID:
								return IW7::DYNENT_TYPE_INVALID;
								break;
							case DYNENT_TYPE_CLUTTER:
								return IW7::DYNENT_TYPE_CLUTTER;
								break;
							case DYNENT_TYPE_DESTRUCT:
								return IW7::DYNENT_TYPE_CLUTTER;
								break;
							case DYNENT_TYPE_HINGE:
								return IW7::DYNENT_TYPE_HINGE;
								break;
							}
							return IW7::DYNENT_TYPE_INVALID;
						};

						if (dynent_def->type == DYNENT_TYPE_DESTRUCT)
						{
							ZONETOOL_INFO("converting dynent destruct into scriptable");
							auto* scriptable_def = generate_scriptable_def_from_dynent(dynent_def, allocator);
							scriptable_defs.push_back({ scriptable_def, dynent_def->pose });

							new_dynent_def->instanceIndex = static_cast<unsigned int>(500 + scriptable_defs.size() - 1);
							new_dynent_def->type = IW7::DYNENT_TYPE_HINGE;
							memcpy(&new_dynent_def->pose, &dynent_def->pose, sizeof(GfxPlacement));
							new_dynent_def->linkTo = nullptr;
							new_dynent_def->unk5 = 1;
							new_dynent_def->unk6 = static_cast<short>(dynent_def->contents);
							new_dynent_def->spawnEnabled = true;
						}
						else
						{
							new_dynent_def->type = convert_type(dynent_def->type);
							if (new_dynent_def->type == IW7::DYNENT_TYPE_CLUTTER)
							{
								memcpy(&new_dynent_def->initialPose, &dynent_def->pose, sizeof(GfxPlacement));

								if (dynent_def->xModel && !dynent_def->xModel->physCollmap)
								{
									const auto mass = dynent_def->physPreset && dynent_def->physPreset->mass > 0.0f
										? dynent_def->physPreset->mass
										: dynent_def->xModel->physPreset && dynent_def->xModel->physPreset->mass > 0.0f
										? dynent_def->xModel->physPreset->mass : 0.0f;
									IW7Converter::request_dynamic_box(dynent_def->xModel->name, mass);
								}
							}
							memcpy(&new_dynent_def->pose, &dynent_def->pose, sizeof(GfxPlacement));
							new_dynent_def->baseModel = reinterpret_cast<IW7::XModel*>(dynent_def->xModel);
							new_dynent_def->brushModel = dynent_def->brushModel;
							new_dynent_def->linkTo = nullptr;
							new_dynent_def->instanceIndex = 0;
							new_dynent_def->spawnEnabled = true;
						}

						dynent_type_count[new_dynent_def->type]++;
					}

					{
						auto* dynent_pose_model =
							&new_asset->dynEntPoseList[IW7::DynEntityBasis::DYNENT_BASIS_MODEL][index][i];
						auto* dynent_pose_brush =
							&new_asset->dynEntPoseList[IW7::DynEntityBasis::DYNENT_BASIS_BRUSH][index][i];
						auto* dynent_pose = &clipmap->dynEntPoseList[index][i];

						// model
						memcpy(&dynent_pose_model->pose, &dynent_pose->pose, sizeof(IW7::GfxPlacement));
						dynent_pose_model->numPoses = 1;
						dynent_pose_model->poses = allocator.allocate<IW7::GfxPlacement>(1);
						memcpy(&dynent_pose_model->poses[0], &dynent_pose_model->pose, sizeof(IW7::GfxPlacement));
						dynent_pose_model->radius = dynent_pose->radius;
						dynent_pose_model->detailBodyToBoneMap = allocator.allocate<char>(dynent_pose_model->numPoses);

						// brush
						memcpy(&dynent_pose_brush->pose, &dynent_pose->pose, sizeof(IW7::GfxPlacement));
						dynent_pose_brush->numPoses = 1;
						dynent_pose_brush->poses = allocator.allocate<IW7::GfxPlacement>(1);
						memcpy(&dynent_pose_brush->poses[0], &dynent_pose_brush->pose, sizeof(IW7::GfxPlacement));
						dynent_pose_brush->radius = dynent_pose->radius;
						dynent_pose_brush->detailBodyToBoneMap = nullptr;
					}
				}
			};
			copy_dynents(0);
			copy_dynents(1);

			for (auto i = 0; i < reserved_dynents; i++)
			{
				auto base_index = new_asset->dynEntCount[0] - reserved_dynents;
				auto* dyn = &new_asset->dynEntDefList[0][i + base_index];
				dyn->type = IW7::DYNENT_TYPE_SCRIPTABLEINST;
				dyn->instanceIndex = static_cast<unsigned int>(500 + scriptable_defs.size());
				dyn->unk4 = i;
				dyn->spawnActive = true;
				dyn->unk5 = 4;
				dyn->unk6 = 0x666;
				dyn->spawnEnabled = true;
			}

			for (auto i = 0; i < new_asset->dynEntCountTotal; i++)
			{
				new_asset->dynEntGlobalIdList[0][i].basis = 0;
				new_asset->dynEntGlobalIdList[0][i].id = i;

				new_asset->dynEntGlobalIdList[1][i].basis = 1;
				new_asset->dynEntGlobalIdList[1][i].id = i;
			}

			std::fill_n(&new_asset->dynEntPhysicsSetupHead[0][0], 4,
				static_cast<unsigned short>(0xFFFF));
			std::fill_n(&new_asset->dynEntPhysicsSetupTail[0][0], 4,
				static_cast<unsigned short>(0xFFFF));

			new_asset->dynEntTransientGroupCount = 0;
			new_asset->dynEntTransientGroups = nullptr;
			new_asset->dynEntTransientGroupRuntime[0] = nullptr;
			new_asset->dynEntTransientGroupRuntime[1] = nullptr;
			new_asset->dynEntTransientGroupState[0] = nullptr;
			new_asset->dynEntTransientGroupState[1] = nullptr;

			new_asset->unk3Count = 0;
			new_asset->unk3 = nullptr;

			new_asset->clientEntAnchorCount = 0;
			new_asset->clientEntAnchors = nullptr;

			new_asset->scriptableMapEnts.totalInstanceCount = static_cast<unsigned int>(500 + scriptable_defs.size());
			new_asset->scriptableMapEnts.runtimeInstanceCount = 500;
			new_asset->scriptableMapEnts.reservedInstanceCount = 500;

			new_asset->scriptableMapEnts.instances = allocator.allocate<IW7::ScriptableInstance>(new_asset->scriptableMapEnts.totalInstanceCount);
			std::memset(new_asset->scriptableMapEnts.instances, 0,
				sizeof(IW7::ScriptableInstance) *
				new_asset->scriptableMapEnts.totalInstanceCount);

			const auto part_runtime_capacity = new_asset->scriptableMapEnts.totalInstanceCount;
			new_asset->scriptableMapEnts.runtimeData.partRuntimeCount =
				static_cast<int>(part_runtime_capacity);
			new_asset->scriptableMapEnts.runtimeData.partRuntime =
				allocator.allocate<IW7::ScriptablePartRuntime>(part_runtime_capacity);
			new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClientCount =
				static_cast<int>(part_runtime_capacity);
			new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClient[0] =
				allocator.allocate<IW7::ScriptablePartRuntime>(part_runtime_capacity);
			new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClient[1] =
				allocator.allocate<IW7::ScriptablePartRuntime>(part_runtime_capacity);
			std::memset(new_asset->scriptableMapEnts.runtimeData.partRuntime, 0,
				sizeof(IW7::ScriptablePartRuntime) * part_runtime_capacity);
			std::memset(new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClient[0], 0,
				sizeof(IW7::ScriptablePartRuntime) * part_runtime_capacity);
			std::memset(new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClient[1], 0,
				sizeof(IW7::ScriptablePartRuntime) * part_runtime_capacity);

			for (unsigned int i = 0; i < part_runtime_capacity; ++i)
			{
				new_asset->scriptableMapEnts.runtimeData.partRuntime[i].stateId = 0;
				new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClient[0][i].stateId = 0;
				new_asset->scriptableMapEnts.runtimeData.partRuntimeLocalClient[1][i].stateId = 0;
			}

			const auto write_scriptable_placement = [](IW7::ScriptableInstanceContext& context,
				const GfxPlacement& pose)
			{
				context.origin[0] = pose.origin[0];
				context.origin[1] = pose.origin[1];
				context.origin[2] = pose.origin[2];
				math::UnitQuatToAngles(pose.quat, context.angles);

				std::memcpy(context.initialOrigin, pose.origin, sizeof(pose.origin));
				std::memcpy(context.initialAngles, context.angles, sizeof(context.angles));
			};

			for (unsigned int i = 0; i < scriptable_defs.size(); i++)
			{
				auto& instance = new_asset->scriptableMapEnts.instances[500 + i];
				instance.contextHeader.context.def = scriptable_defs[i].def;
				instance.contextHeaderLocalClient[0].context.def = scriptable_defs[i].def;
				instance.contextHeaderLocalClient[1].context.def = scriptable_defs[i].def;
				write_scriptable_placement(instance.contextHeader.context, scriptable_defs[i].pose);
				write_scriptable_placement(instance.contextHeaderLocalClient[0].context, scriptable_defs[i].pose);
				write_scriptable_placement(instance.contextHeaderLocalClient[1].context, scriptable_defs[i].pose);

				const auto definition_event_stream_size =
					static_cast<unsigned int>(scriptable_defs[i].def->eventStreamSize);
				const auto server_event_stream_size = definition_event_stream_size + 8u;
				const auto local_client_event_stream_size = definition_event_stream_size + 16u;
				instance.contextHeader.context.eventStreamBufferSize = server_event_stream_size;
				instance.contextHeader.context.eventStreamBuffer =
					allocator.allocate<char>(server_event_stream_size);
				instance.contextHeaderLocalClient[0].context.eventStreamBufferSize =
					local_client_event_stream_size;
				instance.contextHeaderLocalClient[0].context.eventStreamBuffer =
					allocator.allocate<char>(local_client_event_stream_size);
				instance.contextHeaderLocalClient[1].context.eventStreamBufferSize =
					local_client_event_stream_size;
				instance.contextHeaderLocalClient[1].context.eventStreamBuffer =
					allocator.allocate<char>(local_client_event_stream_size);
				std::fill_n(instance.contextHeader.context.eventStreamBuffer,
					server_event_stream_size, static_cast<char>(0));
				std::fill_n(instance.contextHeaderLocalClient[0].context.eventStreamBuffer,
					local_client_event_stream_size, static_cast<char>(0));
				std::fill_n(instance.contextHeaderLocalClient[1].context.eventStreamBuffer,
					local_client_event_stream_size, static_cast<char>(0));

				std::fill_n(reinterpret_cast<int*>(instance.contextHeader.unk02), 2, -1);
				std::fill_n(reinterpret_cast<int*>(instance.contextHeaderLocalClient[0].unk02), 3, -1);
				std::fill_n(reinterpret_cast<int*>(instance.contextHeaderLocalClient[1].unk02), 3, -1);
			}

			new_asset->scriptableMapEnts.reservedDynents[0].numReservedDynents = reserved_dynents;
			new_asset->scriptableMapEnts.reservedDynents[0].reservedDynents =
				allocator.allocate<IW7::ScriptableReservedDynent>(new_asset->scriptableMapEnts.reservedDynents[0].numReservedDynents);

			new_asset->scriptableMapEnts.reservedDynents[1].numReservedDynents = reserved_dynents;
			new_asset->scriptableMapEnts.reservedDynents[1].reservedDynents =
				allocator.allocate<IW7::ScriptableReservedDynent>(new_asset->scriptableMapEnts.reservedDynents[1].numReservedDynents);

			new_asset->numMayhemScenes = 0;
			new_asset->mayhemScenes = nullptr;

			new_asset->spawners.spawnerCount = 0;
			new_asset->spawners.spawnerList = nullptr;

			new_asset->audioPASpeakerCount = 0;
			new_asset->audioPASpeakers = nullptr;

			return new_asset;
		}

		void GenerateIW7ClipInfo(IW7::ClipInfo* info, IW5::ClipInfo* dinfo, allocator& mem)
		{
			if (!dinfo)
			{
				info = nullptr;
				return;
			}

			info->planeCount = dinfo->planeCount;
			info->planes = reinterpret_cast<IW7::cplane_s*>(dinfo->planes);
		}

		IW7::clipMap_t* GenerateIW7ClipMap(clipMap_t* asset, allocator& allocator)
		{
			// allocate IW7 clipMap_t structure
			const auto IW7_asset = allocator.allocate<IW7::clipMap_t>();

			IW7_asset->name = asset->name;
			IW7_asset->isInUse = asset->isInUse;
			GenerateIW7ClipInfo(&IW7_asset->info, &asset->info, allocator);
			IW7_asset->pInfo = &IW7_asset->info;

			IW7_asset->numStaticModels = asset->numStaticModels;
			IW7_asset->staticModelList = allocator.allocate<IW7::cStaticModel_s>(IW7_asset->numStaticModels);
			for (unsigned int i = 0; i < IW7_asset->numStaticModels; i++)
			{
				IW7_asset->staticModelList[i].xmodel = reinterpret_cast<IW7::XModel*>(asset->staticModelList[i].xmodel);
				std::memcpy(&IW7_asset->staticModelList[i].origin, &asset->staticModelList[i].origin, sizeof(float[3]));
				std::memcpy(&IW7_asset->staticModelList[i].invScaledAxis, &asset->staticModelList[i].invScaledAxis, 
					sizeof(float[3][3]));
				IW7_asset->staticModelList[i].unk1 = false;
				IW7_asset->staticModelList[i].unk2 = false;
				IW7_asset->staticModelList[i].hasTransientModel = false;
				IW7_asset->staticModelList[i].hasTransientPhysicsAsset = false;
			}
			
			IW7_asset->staticModelCollisionModelList.numModels = asset->numStaticModels;
			IW7_asset->staticModelCollisionModelList.staticModelIndex = allocator.allocate<int>(asset->numStaticModels);
			for (unsigned int i = 0; i < asset->numStaticModels; i++)
			{
				IW7_asset->staticModelCollisionModelList.staticModelIndex[i] = i;
			}
			IW7_asset->numStaticModelCollisionModelLists = 0;
			IW7_asset->staticModelCollisionModelLists = nullptr;

			IW7_asset->havokWorldShapeDataSize = 0;
			IW7_asset->havokWorldShapeData = nullptr;
			std::vector<ZoneTool::IW7::havok::builder::shape_tag> world_shape_tags;
			{
				auto world = collision::extract_world(asset);
				if (!world.triangles.empty() || !world.convexes.empty())
				{
					ZoneTool::IW7::havok::builder::mesh_input input{};
					input.convexes.reserve(world.convexes.size());
					for (auto& cvx : world.convexes)
					{
						ZoneTool::IW7::havok::builder::convex out{};
						out.verts = std::move(cvx.verts);
						out.surface_tag = cvx.surface_tag;
						out.contents = cvx.contents;
						out.material_crc = cvx.material_crc;
						out.user_data = cvx.user_data;
						input.convexes.emplace_back(std::move(out));
					}
					decltype(world.convexes){}.swap(world.convexes);

					const auto* flip_winding = std::getenv("ZT_HAVOK_FLIP_WINDING");
					const auto reverse_winding = flip_winding && flip_winding[0] == '1';
					if (reverse_winding)
					{
						ZONETOOL_WARNING("clipmap: reversing world collision winding "
							"(ZT_HAVOK_FLIP_WINDING diagnostic, triangles only)");
					}
					input.triangles = std::move(world.triangles);
					if (reverse_winding)
					{
						for (auto& tri : input.triangles)
						{
							if (tri.is_quad)
							{
								std::swap(tri.verts[1], tri.vert3);
							}
							else
							{
								std::swap(tri.verts[1], tri.verts[2]);
							}
						}
					}

					const auto blob = ZoneTool::IW7::havok::builder::build_world_shape(
						input, &world_shape_tags);
					decltype(input.triangles){}.swap(input.triangles);
					decltype(input.convexes){}.swap(input.convexes);

					if (collision::obj_dump_enabled())
					{
						collision::write_blob(
							collision::obj_dump_path(asset->name, ".world.hkx"),
							blob.data(), blob.size());
					}

					if (!blob.empty())
					{
						auto* memory = allocator.allocate<char>(blob.size());
						std::memcpy(memory, blob.data(), blob.size());

						IW7_asset->havokWorldShapeData = memory;
						IW7_asset->havokWorldShapeDataSize = static_cast<unsigned int>(blob.size());
					}
					else
					{
						ZONETOOL_WARNING("clipmap: no havok world shape generated for \"%s\"",
							asset->name);
					}
				}
			}

			IW7_asset->mapEnts = generate_mapents(asset, allocator, world_shape_tags);
			decltype(world_shape_tags){}.swap(world_shape_tags);

			IW7_asset->stageCount = asset->stageCount;
			IW7_asset->stages = allocator.allocate<IW7::Stage>(IW7_asset->stageCount);
			for (unsigned int i = 0; i < IW7_asset->stageCount; i++)
			{
				IW7_asset->stages[i].name = asset->stages[i].name;
				memcpy(&IW7_asset->stages[i].origin, &asset->stages[i].origin, sizeof(float[3]));
				IW7_asset->stages[i].triggerIndex = asset->stages[i].triggerIndex;
				IW7_asset->stages[i].sunPrimaryLightIndex = asset->stages[i].sunPrimaryLightIndex;
				IW7_asset->stages[i].entityUID = 0x3A83126F;
			}

			IW7_asset->stageTrigger.count = 0;
			IW7_asset->stageTrigger.models = nullptr;
			IW7_asset->stageTrigger.hullCount = 0;
			IW7_asset->stageTrigger.hulls = nullptr;
			IW7_asset->stageTrigger.slabCount = 0;
			IW7_asset->stageTrigger.slabs = nullptr;
			IW7_asset->stageTrigger.windingCount = 0;
			IW7_asset->stageTrigger.windings = nullptr;
			IW7_asset->stageTrigger.windingPointCount = 0;
			IW7_asset->stageTrigger.windingPoints = nullptr;

			if (IW7_asset->stageCount > 1)
			{
				ZONETOOL_WARNING("clipmap: %u stages but no stage triggers survive the dump -- "
					"clamping stageCount to 1", IW7_asset->stageCount);
				IW7_asset->stageCount = 1;
			}

			IW7_asset->broadphaseMin[0] = -131072.f;
			IW7_asset->broadphaseMin[1] = -131072.f;
			IW7_asset->broadphaseMin[2] = -131072.f;
			IW7_asset->broadphaseMax[0] = 131072.f;
			IW7_asset->broadphaseMax[1] = 131072.f;
			IW7_asset->broadphaseMax[2] = 131072.f;
			
			IW7_asset->physicsCapacities;

			IW7_asset->numCollisionHeatmapEntries = 0;
			IW7_asset->collisionHeatmap = nullptr; // todo...

			IW7_asset->topDownMapData = nullptr; // todo...

			IW7_asset->checksum = asset->checksum;

			return IW7_asset;
		}

		IW7::clipMap_t* convert(clipMap_t* asset, allocator& allocator)
		{
			return GenerateIW7ClipMap(asset, allocator);
		}
	}
}
