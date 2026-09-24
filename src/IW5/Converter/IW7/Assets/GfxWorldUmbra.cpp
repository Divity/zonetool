#include "stdafx.hpp"
#include "../Include.hpp"

#include "GfxWorld.hpp"
#include "GfxWorldUmbra.hpp"
#include "ComWorld.hpp"

#include "X64/Utils/Umbra/UmbraTome.hpp"
#include "IW3/Structs.hpp"

#include <cmath>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		namespace
		{
			constexpr unsigned int TOME_VERSION_MAGIC = 0xD6000014;

			constexpr float LOD_BASE_DISTANCE = 128.0f;

			constexpr float DEAD_VOLUME_ORIGIN = 200000.0f;
			constexpr float DEAD_VOLUME_SIZE = 64.0f;

			constexpr float VIEW_VOLUME_HALF_EXTENT = 262144.0f;

			constexpr unsigned int BOX_TARGET = ZoneTool::Umbra::SCENE_OBJECT_TARGET | ZoneTool::Umbra::SCENE_OBJECT_VOLUME;

			unsigned int compute_umbra_tome_crc32(const void* data, std::size_t size)
			{
				const auto* bytes = static_cast<const unsigned char*>(data);
				unsigned int crc = 0xFFFFFFFF;

				for (std::size_t i = 0; i < size; i++)
				{
					crc ^= bytes[i];
					for (int bit = 0; bit < 8; bit++)
					{
						crc = (crc & 1u) ? ((crc >> 1) ^ 0x82F63B78u) : (crc >> 1);
					}
				}

				return ~crc;
			}

			IW7::Umbra::ImpTome* build_draw_everything_tome(allocator& allocator)
			{
				auto* tome = allocator.allocate<IW7::Umbra::ImpTome>();

				tome->m_versionMagic = TOME_VERSION_MAGIC;
				tome->m_size = sizeof(IW7::Umbra::ImpTome);
				tome->m_lodBaseDistance = LOD_BASE_DISTANCE;
				tome->m_flags = 0;

				tome->m_treeMin = { DEAD_VOLUME_ORIGIN, DEAD_VOLUME_ORIGIN, DEAD_VOLUME_ORIGIN };
				tome->m_treeMax = { DEAD_VOLUME_ORIGIN + DEAD_VOLUME_SIZE, DEAD_VOLUME_ORIGIN + DEAD_VOLUME_SIZE,
					DEAD_VOLUME_ORIGIN + DEAD_VOLUME_SIZE };
				tome->m_boundsMin = tome->m_treeMin;
				tome->m_boundsMax = tome->m_treeMax;
				tome->m_clusterCoordScale = 1.0f;

				tome->m_crc32 = compute_umbra_tome_crc32(&tome->m_size,
					tome->m_size - offsetof(IW7::Umbra::ImpTome, m_size));

				return tome;
			}

			struct aabb
			{
				float mins[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
				float maxs[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

				bool valid() const
				{
					return this->mins[0] <= this->maxs[0] && this->mins[1] <= this->maxs[1]
						&& this->mins[2] <= this->maxs[2];
				}

				void add(const float* point)
				{
					for (int axis = 0; axis < 3; axis++)
					{
						this->mins[axis] = std::min(this->mins[axis], point[axis]);
						this->maxs[axis] = std::max(this->maxs[axis], point[axis]);
					}
				}

				void add(const Bounds& bounds)
				{
					for (int axis = 0; axis < 3; axis++)
					{
						this->mins[axis] = std::min(this->mins[axis], bounds.midPoint[axis] - bounds.halfSize[axis]);
						this->maxs[axis] = std::max(this->maxs[axis], bounds.midPoint[axis] + bounds.halfSize[axis]);
					}
				}

				void expand(const float amount)
				{
					for (int axis = 0; axis < 3; axis++)
					{
						this->mins[axis] -= amount;
						this->maxs[axis] += amount;
					}
				}
			};

			constexpr unsigned int BLEND_DISABLED = 0;
			constexpr unsigned int BLEND_ZERO = 1;
			constexpr unsigned int BLEND_ONE = 2;

			enum class opaque_verdict
			{
				opaque,
				no_material,
				no_state_bits,
				camera_region,
				blend,
				alpha_test,
				no_depth_write,
				polygon_offset,
				count
			};

			const char* opaque_verdict_name(const opaque_verdict verdict)
			{
				static const char* names[] = {
					"opaque", "no material", "no state bits", "camera region not lit opaque", "blended",
					"alpha tested", "no depth write", "polygon offset",
				};
				return names[static_cast<int>(verdict)];
			}

			struct material_view
			{
				const char* name = nullptr;
				unsigned char camera_region = 0;
				unsigned char state_bits_count = 0;
				const GfxStateBits* state_bits = nullptr;
				bool lit_opaque_region = false;
				std::vector<unsigned char> base_pass_entries;
			};

			material_view view_material(const Material* material)
			{
				material_view view;
				if (!material)
				{
					return view;
				}

				if (get_linker_mode() == linker_mode::iw3)
				{
					const auto* iw3 = reinterpret_cast<const IW3::Material*>(material);
					view.name = iw3->name;
					view.camera_region = static_cast<unsigned char>(iw3->cameraRegion);
					view.state_bits_count = static_cast<unsigned char>(iw3->stateBitsCount);
					static_assert(sizeof(IW3::GfxStateBits) == sizeof(GfxStateBits));
					view.state_bits = reinterpret_cast<const GfxStateBits*>(iw3->stateBitsTable);
					view.lit_opaque_region = iw3->cameraRegion == IW3::CAMERA_REGION_LIT;
					for (const auto technique : { IW3::TECHNIQUE_UNLIT, IW3::TECHNIQUE_EMISSIVE, IW3::TECHNIQUE_LIT,
						IW3::TECHNIQUE_LIT_SUN, IW3::TECHNIQUE_LIT_SUN_SHADOW })
					{
						view.base_pass_entries.push_back(static_cast<unsigned char>(iw3->stateBitsEntry[technique]));
					}
				}
				else
				{
					view.name = material->info.name;
					view.camera_region = material->cameraRegion;
					view.state_bits_count = material->stateBitsCount;
					view.state_bits = material->stateBitsTable;
					view.lit_opaque_region = material->cameraRegion == CAMERA_REGION_LIT_OPAQUE;
					for (const auto technique : { TECHNIQUE_UNLIT, TECHNIQUE_EMISSIVE, TECHNIQUE_EMISSIVE_DFOG,
						TECHNIQUE_LIT, TECHNIQUE_LIT_DFOG, TECHNIQUE_LIT_SUN, TECHNIQUE_LIT_SUN_DFOG,
						TECHNIQUE_LIT_SUN_SHADOW, TECHNIQUE_LIT_SUN_SHADOW_DFOG })
					{
						view.base_pass_entries.push_back(material->stateBitsEntry[technique]);
					}
				}
				return view;
			}

			opaque_verdict judge_material(const material_view& material)
			{
				if (!material.name)
				{
					return opaque_verdict::no_material;
				}
				if (!material.state_bits || !material.state_bits_count)
				{
					return opaque_verdict::no_state_bits;
				}
				if (!material.lit_opaque_region)
				{
					return opaque_verdict::camera_region;
				}

				unsigned int base_passes = 0;
				for (const auto entry : material.base_pass_entries)
				{
					if (entry == 0xFF || entry >= material.state_bits_count)
					{
						continue;
					}
					base_passes++;

					const auto bits0 = material.state_bits[entry].loadBits[0];
					const auto bits1 = material.state_bits[entry].loadBits[1];

					const auto blend_op = (bits0 & GFXS0_BLENDOP_RGB_MASK) >> GFXS0_BLENDOP_RGB_SHIFT;
					const auto src_blend = (bits0 & GFXS0_SRCBLEND_RGB_MASK) >> GFXS0_SRCBLEND_RGB_SHIFT;
					const auto dst_blend = (bits0 & GFXS0_DSTBLEND_RGB_MASK) >> GFXS0_DSTBLEND_RGB_SHIFT;
					const auto blend_off = blend_op == BLEND_DISABLED
						|| (src_blend == BLEND_ONE && dst_blend == BLEND_ZERO);
					if (!blend_off)
					{
						return opaque_verdict::blend;
					}
					if (!(bits0 & GFXS0_ATEST_DISABLE))
					{
						return opaque_verdict::alpha_test;
					}
					if (!(bits1 & GFXS1_DEPTHWRITE))
					{
						return opaque_verdict::no_depth_write;
					}
					if (bits1 & GFXS1_POLYGON_OFFSET_MASK)
					{
						return opaque_verdict::polygon_offset;
					}
				}

				return base_passes ? opaque_verdict::opaque : opaque_verdict::no_state_bits;
			}

			bool finite3(const float* v)
			{
				return std::isfinite(v[0]) && std::isfinite(v[1]) && std::isfinite(v[2]);
			}

			struct gathered_scene
			{
				ZoneTool::Umbra::tome_input input;
				unsigned int occluder_surfaces = 0;
				unsigned int target_surfaces = 0;
				unsigned int sky_surfaces = 0;
				unsigned int skipped_surfaces = 0;
				unsigned int unsorted_surfaces = 0;
				unsigned int triangles = 0;
				unsigned int smodels = 0;
				unsigned int bounded_lights = 0;
				unsigned int unbounded_objects = 0;
				unsigned int verdicts[static_cast<int>(opaque_verdict::count)]{};
				std::string verdict_examples[static_cast<int>(opaque_verdict::count)];
				unsigned int view_box_model = 0;
			};

			bool build_surface_model(const GfxWorld* asset, const unsigned int surface_index,
				ZoneTool::Umbra::tome_model& model)
			{
				const auto& tris = asset->dpvs.surfaces[surface_index].tris;
				if (!tris.triCount || !tris.vertexCount || !asset->draw.vd.vertices || !asset->draw.indices)
				{
					return false;
				}

				if (tris.firstVertex > asset->draw.vertexCount
					|| tris.vertexCount > asset->draw.vertexCount - tris.firstVertex
					|| tris.baseIndex > asset->draw.indexCount
					|| tris.triCount * 3u > asset->draw.indexCount - tris.baseIndex)
				{
					return false;
				}

				std::vector<int> remap(tris.vertexCount, -1);
				model.vertices.reserve(static_cast<std::size_t>(std::min<unsigned int>(
					tris.vertexCount, tris.triCount * 3u)) * 3);
				model.indices.reserve(static_cast<std::size_t>(tris.triCount) * 3);
				for (unsigned int i = 0; i < tris.triCount * 3u; i++)
				{
					const auto index = asset->draw.indices[tris.baseIndex + i];
					if (index >= tris.vertexCount)
					{
						return false;
					}
					if (remap[index] == -1)
					{
						const auto* xyz = asset->draw.vd.vertices[tris.firstVertex + index].xyz;
						if (!finite3(xyz))
						{
							return false;
						}
						remap[index] = static_cast<int>(model.vertices.size() / 3);
						model.vertices.insert(model.vertices.end(), xyz, xyz + 3);
					}
					model.indices.push_back(static_cast<unsigned int>(remap[index]));
				}

				return true;
			}

			bool gather_scene(const GfxWorld* asset, const IW7::GfxWorld* world, gathered_scene& out,
				const ZoneTool::Umbra::log_fn& log)
			{
				auto& input = out.input;
				input.name = world->baseName ? world->baseName : "world";

				if (!asset->dpvs.surfaces || !asset->dpvs.surfacesBounds || !world->dpvs.sortedSurfIndex)
				{
					log("no static surfaces to build a tome from");
					return false;
				}

				std::unordered_map<unsigned int, unsigned int> sorted_position;
				sorted_position.reserve(world->dpvs.staticSurfaceCount);
				for (unsigned int sorted = 0; sorted < world->dpvs.staticSurfaceCount; sorted++)
				{
					sorted_position.emplace(world->dpvs.sortedSurfIndex[sorted], sorted);
				}

				std::unordered_set<unsigned int> sky_surfaces;
				for (int i = 0; i < asset->skyCount; i++)
				{
					for (int j = 0; j < asset->skies[i].skySurfCount; j++)
					{
						sky_surfaces.insert(static_cast<unsigned int>(asset->skies[i].skyStartSurfs[j]));
					}
				}

				aabb view;
				for (int axis = 0; axis < 3; axis++)
				{
					view.mins[axis] = -VIEW_VOLUME_HALF_EXTENT;
					view.maxs[axis] = VIEW_VOLUME_HALF_EXTENT;
				}

				ZoneTool::Umbra::scene_view_volume volume{};
				std::memcpy(volume.mins, view.mins, sizeof(volume.mins));
				std::memcpy(volume.maxs, view.maxs, sizeof(volume.maxs));
				input.view_volumes.push_back(volume);

				const auto view_box_model = input.add_box_model(view.mins, view.maxs);
				out.view_box_model = view_box_model;

				for (unsigned int surface = 0; surface < asset->surfaceCount; surface++)
				{
					const auto sorted = sorted_position.find(surface);
					if (sorted == sorted_position.end())
					{
						out.skipped_surfaces++;
						out.unsorted_surfaces++;
						continue;
					}

					const auto user_id = ZoneTool::Umbra::USER_ID_SURFACE | (sorted->second & ZoneTool::Umbra::USER_ID_INDEX_MASK);

					if (sky_surfaces.count(surface))
					{
						input.objects.push_back({ view_box_model, user_id, BOX_TARGET });
						out.sky_surfaces++;
						continue;
					}

					ZoneTool::Umbra::tome_model model;
					if (!build_surface_model(asset, surface, model))
					{
						input.objects.push_back({ view_box_model, user_id, BOX_TARGET });
						out.skipped_surfaces++;
						const auto& tris = asset->dpvs.surfaces[surface].tris;
						ZONETOOL_WARNING("umbra: surface %u (%s) has no usable geometry: firstVertex %u vertexCount %u "
							"triCount %u baseIndex %u (world has %u vertices, %u indices)", surface,
							view_material(asset->dpvs.surfaces[surface].material).name, tris.firstVertex, tris.vertexCount,
							tris.triCount, tris.baseIndex, asset->draw.vertexCount, asset->draw.indexCount);
						continue;
					}

					out.triangles += static_cast<unsigned int>(model.indices.size() / 3);
					input.models.emplace_back(std::move(model));
					const auto model_index = static_cast<unsigned int>(input.models.size() - 1);

					unsigned int flags = ZoneTool::Umbra::SCENE_OBJECT_TARGET;
					const auto material = view_material(asset->dpvs.surfaces[surface].material);
					const auto verdict = judge_material(material);
					out.verdicts[static_cast<int>(verdict)]++;
					if (material.name && out.verdict_examples[static_cast<int>(verdict)].size() < 200)
					{
						auto& examples = out.verdict_examples[static_cast<int>(verdict)];
						const std::string name = material.name;
						if (examples.find(name) == std::string::npos)
						{
							examples += (examples.empty() ? "" : ", ") + name;
						}
					}
					if (verdict == opaque_verdict::opaque)
					{
						flags |= ZoneTool::Umbra::SCENE_OBJECT_OCCLUDER;
						out.occluder_surfaces++;
					}
					out.target_surfaces++;
					input.objects.push_back({ model_index, user_id, flags });
				}

				if (asset->dpvs.smodelInsts)
				{
					for (unsigned int i = 0; i < asset->dpvs.smodelCount && i < ZoneTool::Umbra::USER_ID_INDEX_MASK; i++)
					{
						const auto& bounds = asset->dpvs.smodelInsts[i].bounds;
						float mins[3], maxs[3];
						for (int axis = 0; axis < 3; axis++)
						{
							mins[axis] = bounds.midPoint[axis] - bounds.halfSize[axis];
							maxs[axis] = bounds.midPoint[axis] + bounds.halfSize[axis];
						}
						if (!finite3(mins) || !finite3(maxs))
						{
							continue;
						}

						const auto model_index = input.add_box_model(mins, maxs);
						input.objects.push_back({ model_index, ZoneTool::Umbra::USER_ID_SMODEL | (i + 1), BOX_TARGET });
						out.smodels++;
					}
				}

				for (unsigned int i = 0; i < world->primaryLightCount; i++)
				{
					auto model_index = view_box_model;
					if (converter_com_world && i < converter_com_world->primaryLightCount)
					{
						const auto& light = converter_com_world->primaryLights[i];
						const auto type = static_cast<unsigned char>(light.type);
						if ((type == IW7::GFX_LIGHT_TYPE_SPOT || type == IW7::GFX_LIGHT_TYPE_OMNI) && light.radius > 0.0f
							&& finite3(light.origin) && std::isfinite(light.radius))
						{
							float mins[3], maxs[3];
							for (int axis = 0; axis < 3; axis++)
							{
								mins[axis] = light.origin[axis] - light.radius;
								maxs[axis] = light.origin[axis] + light.radius;
							}
							model_index = input.add_box_model(mins, maxs);
							out.bounded_lights++;
						}
					}
					if (model_index == view_box_model)
					{
						out.unbounded_objects++;
					}
					input.objects.push_back({ model_index, ZoneTool::Umbra::USER_ID_PRIMARY_LIGHT | i, BOX_TARGET });
				}

				const auto add_unbounded = [&](const unsigned int type, const unsigned int count)
				{
					for (unsigned int i = 0; i < count; i++)
					{
						input.objects.push_back({ view_box_model, type | i, BOX_TARGET });
						out.unbounded_objects++;
					}
				};
				add_unbounded(ZoneTool::Umbra::USER_ID_REFLECTION_PROBE,
					world->draw.reflectionProbeData.reflectionProbeInstanceCount);
				add_unbounded(ZoneTool::Umbra::USER_ID_VOLUMETRIC, world->draw.volumetrics.volumetricCount);
				add_unbounded(ZoneTool::Umbra::USER_ID_DECAL, world->draw.decalVolumeCollectionCount);

				return !input.objects.empty();
			}
		}

		void generate_umbra_tome(const GfxWorld* asset, IW7::GfxWorld* world, allocator& allocator)
		{
			const auto log = [](const std::string& line)
			{
				ZONETOOL_INFO("umbra: %s", line.data());
			};

			const auto fall_back = [&](const char* why)
			{
				ZONETOOL_WARNING("umbra: %s - shipping the draw-everything tome, the map will render with no "
					"static occlusion culling", why);
				auto* tome = build_draw_everything_tome(allocator);
				world->umbraTomeSize = tome->m_size;
				world->umbraTomeData = reinterpret_cast<char*>(tome);
			};

			world->numUmbraGates = 0;
			world->umbraGates = nullptr;
			world->umbraTomePtr = nullptr;

			if (const auto* disable = std::getenv("ZT_UMBRA_DISABLE"); disable && *disable && *disable != '0')
			{
				fall_back("ZT_UMBRA_DISABLE is set");
				return;
			}

			if (ZoneTool::Umbra::find_generator().empty())
			{
				fall_back("umbra-tomegen.exe not found (set ZT_UMBRA_TOMEGEN or put it next to the zonetool dll)");
				return;
			}

			gathered_scene scene;
			if (!gather_scene(asset, world, scene, log))
			{
				fall_back("nothing to build a tome from");
				return;
			}

			const auto& volume = scene.input.view_volumes.front();
			ZONETOOL_INFO("umbra: %s: %u surfaces (%u occluders, %u sky, %u without geometry), %u triangles, %u static models, "
				"%u bounded lights, %u never-culled objects; %zu models, %zu objects; view volume (%g %g %g) - (%g %g %g)",
				scene.input.name.data(), scene.target_surfaces + scene.sky_surfaces, scene.occluder_surfaces,
				scene.sky_surfaces, scene.skipped_surfaces - scene.unsorted_surfaces, scene.triangles, scene.smodels, scene.bounded_lights,
				scene.unbounded_objects, scene.input.models.size(), scene.input.objects.size(), volume.mins[0],
				volume.mins[1], volume.mins[2], volume.maxs[0], volume.maxs[1], volume.maxs[2]);

			for (int i = 0; i < static_cast<int>(opaque_verdict::count); i++)
			{
				if (scene.verdicts[i])
				{
					ZONETOOL_INFO("umbra:   %u surfaces %s (e.g. %s)", scene.verdicts[i],
						opaque_verdict_name(static_cast<opaque_verdict>(i)), scene.verdict_examples[i].data());
				}
			}

			ZoneTool::Umbra::tome_result result;
			const auto view_box_model = scene.view_box_model;
			for (int attempt = 0;; attempt++)
			{
				if (!ZoneTool::Umbra::generate_tome(scene.input, result, log))
				{
					fall_back(result.error.data());
					return;
				}

				const auto ids = ZoneTool::Umbra::read_user_ids(result.data.data(), result.data.size());
				const std::unordered_set<unsigned int> present(ids.begin(), ids.end());

				unsigned int dropped = 0, dropped_by_type[8]{};
				for (auto& object : scene.input.objects)
				{
					if (!present.count(object.user_id))
					{
						dropped++;
						dropped_by_type[(object.user_id >> 28) & 7]++;
						object.model = view_box_model;
						object.flags = BOX_TARGET;
					}
				}

				if (!dropped)
				{
					break;
				}

				ZONETOOL_WARNING("umbra: the optimizer dropped %u of %zu targets (%u surfaces, %u static models, "
					"%u lights, %u probes, %u volumetrics, %u decals)%s", dropped, scene.input.objects.size(),
					dropped_by_type[0], dropped_by_type[1], dropped_by_type[4], dropped_by_type[5], dropped_by_type[3],
					dropped_by_type[6], attempt == 0 ? " - re-running with them as never-culled objects" : "");

				if (attempt > 0)
				{
					fall_back("targets are still missing from the tome after the retry");
					return;
				}
			}

			const auto& stats = result.stats;
			ZONETOOL_INFO("umbra: tome version 0x%X, %u bytes, %d objects (%u user IDs), %d tiles (%d leaf), "
				"%u cells (%u without portals), %u cell portals, %d clusters, %u object list entries, "
				"tree (%g %g %g) - (%g %g %g), lodBase %g, generated in %.1fs",
				stats.version, stats.size, stats.object_count, stats.user_id_count, stats.tile_count,
				stats.leaf_tile_count, stats.cell_count, stats.cells_without_portals, stats.portal_count,
				stats.cluster_count, stats.object_list_entries, stats.tree_min[0], stats.tree_min[1], stats.tree_min[2],
				stats.tree_max[0], stats.tree_max[1], stats.tree_max[2], stats.lod_base_distance,
				result.generation_seconds);

			if (stats.object_count <= 0)
			{
				fall_back("the generated tome has no objects");
				return;
			}
			decltype(scene.input.models){}.swap(scene.input.models);
			decltype(scene.input.objects){}.swap(scene.input.objects);

			auto* data = allocator.manual_allocate<char>(result.data.size());
			std::memcpy(data, result.data.data(), result.data.size());
			world->umbraTomeSize = static_cast<unsigned int>(result.data.size());
			world->umbraTomeData = data;
		}
	}
}
