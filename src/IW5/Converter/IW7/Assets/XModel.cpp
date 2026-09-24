#include "stdafx.hpp"
#include <map>
#include <algorithm>
#include <cctype>
#include <string>
#include "../Include.hpp"

#include "Common/havok_builder.hpp"
#include "ClipMapCollision.hpp"

#include "XModel.hpp"
#include "Assets/Material.hpp"

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		namespace
		{
			IW7::SurfaceFlags surf_flags_conversion_table[31]
			{
				IW7::SurfaceFlags::SURFACE_FLAG_NONE,
				IW7::SurfaceFlags::SURFACE_FLAG_BARK,
				IW7::SurfaceFlags::SURFACE_FLAG_BRICK,
				IW7::SurfaceFlags::SURFACE_FLAG_CARPET_SOLID,
				IW7::SurfaceFlags::SURFACE_FLAG_CLOTH,
				IW7::SurfaceFlags::SURFACE_FLAG_CONCRETE_DRY,
				IW7::SurfaceFlags::SURFACE_FLAG_DIRT,
				IW7::SurfaceFlags::SURFACE_FLAG_FLESH,
				IW7::SurfaceFlags::SURFACE_FLAG_FOLIAGE_DRY,
				IW7::SurfaceFlags::SURFACE_FLAG_GLASS_PANE,
				IW7::SurfaceFlags::SURFACE_FLAG_GRASS_SHORT,
				IW7::SurfaceFlags::SURFACE_FLAG_GRAVEL,
				IW7::SurfaceFlags::SURFACE_FLAG_ICE_SOLID,
				IW7::SurfaceFlags::SURFACE_FLAG_METAL_THICK,
				IW7::SurfaceFlags::SURFACE_FLAG_MUD,
				IW7::SurfaceFlags::SURFACE_FLAG_PAPER,
				IW7::SurfaceFlags::SURFACE_FLAG_PLASTER,
				IW7::SurfaceFlags::SURFACE_FLAG_ROCK,
				IW7::SurfaceFlags::SURFACE_FLAG_SAND,
				IW7::SurfaceFlags::SURFACE_FLAG_SNOW,
				IW7::SurfaceFlags::SURFACE_FLAG_WATER,
				IW7::SurfaceFlags::SURFACE_FLAG_WOOD_SOLID,
				IW7::SurfaceFlags::SURFACE_FLAG_ASPHALT_DRY,
				IW7::SurfaceFlags::SURFACE_FLAG_CERAMIC,
				IW7::SurfaceFlags::SURFACE_FLAG_PLASTIC,
				IW7::SurfaceFlags::SURFACE_FLAG_RUBBER,
				IW7::SurfaceFlags::SURFACE_FLAG_CUSHION,
				IW7::SurfaceFlags::SURFACE_FLAG_FRUIT,
				IW7::SurfaceFlags::SURFACE_FLAG_METAL_PAINTED,
				IW7::SurfaceFlags::SURFACE_FLAG_RIOTSHIELD,
				IW7::SurfaceFlags::SURFACE_FLAG_SLUSH,
			}; IW5::CSurfaceFlags;
		}

		int convert_surf_flags(int flags)
		{
				const auto surf_type = (static_cast<unsigned int>(flags) >> 20) & 0x1Fu;
				int IW7_flags = surf_flags_conversion_table[
					surf_type < ARRAYSIZE(surf_flags_conversion_table) ? surf_type : 0];
				auto convert = [&](IW5::CSurfaceFlags a, IW7::SurfaceFlags b)
				{
					IW7_flags |= (a != 0 && (flags & a) == a) ? b : 0;
				};
				convert(IW5::CSurfaceFlags::SURF_FLAG_CLIPMISSILE, IW7::SurfaceFlags::SURFACE_FLAG_CLIPMISSILE);
				convert(IW5::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT, IW7::SurfaceFlags::SURFACE_FLAG_AI_NOSIGHT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_CLIPSHOT, IW7::SurfaceFlags::SURFACE_FLAG_CLIPSHOT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_PLAYERCLIP, IW7::SurfaceFlags::SURFACE_FLAG_PLAYERCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_MONSTERCLIP, IW7::SurfaceFlags::SURFACE_FLAG_MONSTERCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_AICLIPALLOWDEATH, IW7::SurfaceFlags::SURFACE_FLAG_AICLIPALLOWDEATH);
				convert(IW5::CSurfaceFlags::SURF_FLAG_VEHICLECLIP, IW7::SurfaceFlags::SURFACE_FLAG_VEHICLECLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_ITEMCLIP, IW7::SurfaceFlags::SURFACE_FLAG_ITEMCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODROP, IW7::SurfaceFlags::SURFACE_FLAG_NODROP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NONSOLID, IW7::SurfaceFlags::SURFACE_FLAG_NONSOLID);
				convert(IW5::CSurfaceFlags::SURF_FLAG_DETAIL, IW7::SurfaceFlags::SURFACE_FLAG_DETAIL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_STRUCTURAL, IW7::SurfaceFlags::SURFACE_FLAG_STRUCTURAL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_PORTAL, IW7::SurfaceFlags::SURFACE_FLAG_PORTAL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP, IW7::SurfaceFlags::SURFACE_FLAG_CANSHOOTCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_ORIGIN, IW7::SurfaceFlags::SURFACE_FLAG_ORIGIN);
				convert(IW5::CSurfaceFlags::SURF_FLAG_SKY, IW7::SurfaceFlags::SURFACE_FLAG_SKY);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW, IW7::SurfaceFlags::SURFACE_FLAG_NOCASTSHADOW);
				convert(IW5::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM, IW7::SurfaceFlags::SURFACE_FLAG_PHYSICSGEOM);
				convert(IW5::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL, IW7::SurfaceFlags::SURFACE_FLAG_LIGHTPORTAL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_OUTDOORBOUNDS, IW7::SurfaceFlags::SURFACE_FLAG_OUTDOORBOUNDS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_SLICK, IW7::SurfaceFlags::SURFACE_FLAG_SLICK);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOIMPACT, IW7::SurfaceFlags::SURFACE_FLAG_NOIMPACT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOMARKS, IW7::SurfaceFlags::SURFACE_FLAG_NOMARKS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOPENETRATE, IW7::SurfaceFlags::SURFACE_FLAG_NOPENETRATE);
				convert(IW5::CSurfaceFlags::SURF_FLAG_LADDER, IW7::SurfaceFlags::SURFACE_FLAG_LADDER);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODAMAGE, IW7::SurfaceFlags::SURFACE_FLAG_NODAMAGE);
				convert(IW5::CSurfaceFlags::SURF_FLAG_MANTLEON, IW7::SurfaceFlags::SURFACE_FLAG_MANTLEON);
				convert(IW5::CSurfaceFlags::SURF_FLAG_MANTLEOVER, IW7::SurfaceFlags::SURFACE_FLAG_MANTLEOVER);
				convert(IW5::CSurfaceFlags::SURF_FLAG_STAIRS, IW7::SurfaceFlags::SURFACE_FLAG_STAIRS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_SOFT, IW7::SurfaceFlags::SURFACE_FLAG_SOFT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOSTEPS, IW7::SurfaceFlags::SURFACE_FLAG_NOSTEPS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODRAW, IW7::SurfaceFlags::SURFACE_FLAG_NODRAW);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP, IW7::SurfaceFlags::SURFACE_FLAG_NOLIGHTMAP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODLIGHT, IW7::SurfaceFlags::SURFACE_FLAG_NODLIGHT);
				return IW7_flags;
		}

		namespace
		{
			std::map<std::string, float> dynamic_box_requests;

			ZoneTool::IW7::havok::builder::polytope box_polytope(const Bounds& bounds)
			{
				ZoneTool::IW7::havok::builder::polytope box{};
				float mn[3], mx[3];
				for (auto k = 0; k < 3; k++)
				{
					mn[k] = bounds.midPoint[k] - bounds.halfSize[k];
					mx[k] = bounds.midPoint[k] + bounds.halfSize[k];
				}
				for (auto i = 0; i < 8; i++)
				{
					box.verts.push_back({(i & 1) ? mx[0] : mn[0], (i & 2) ? mx[1] : mn[1], (i & 4) ? mx[2] : mn[2]});
				}
				const struct { int axis; float sign; std::uint8_t idx[4]; } faces[6] = {
					{0, -1.0f, {0, 4, 6, 2}}, {0, 1.0f, {1, 3, 7, 5}},
					{1, -1.0f, {0, 1, 5, 4}}, {1, 1.0f, {2, 6, 7, 3}},
					{2, -1.0f, {0, 2, 3, 1}}, {2, 1.0f, {4, 5, 7, 6}},
				};
				for (const auto& f : faces)
				{
					ZoneTool::IW7::havok::builder::polytope_face face{};
					face.plane[f.axis] = f.sign;
					face.plane[3] = f.sign > 0.0f ? mx[f.axis] : -mn[f.axis];
					face.indices.assign(f.idx, f.idx + 4);
					box.faces.emplace_back(std::move(face));
				}
				return box;
			}
		}

		void request_dynamic_box(const std::string& model, const float mass)
		{
			dynamic_box_requests[model] = mass;
		}

		bool wants_dynamic_box(const std::string& model, float* mass)
		{
			const auto it = dynamic_box_requests.find(model);
			if (it == dynamic_box_requests.end())
			{
				return false;
			}
			if (mass)
			{
				*mass = it->second;
			}
			return true;
		}

		IW7::XModel* GenerateIW7Model(XModel* asset, allocator& mem)
		{
			// allocate IW7 XModel structure
			auto* iw7_asset = mem.allocate<IW7::XModel>();

			iw7_asset->name = asset->name;
			iw7_asset->numBones = asset->numBones;
			iw7_asset->numRootBones = asset->numRootBones;
			iw7_asset->numsurfs = asset->numsurfs;
			iw7_asset->numReactiveMotionParts = 0;
			iw7_asset->scale = asset->scale;
			memcpy(&iw7_asset->noScalePartBits, &asset->noScalePartBits, sizeof(asset->noScalePartBits));

			iw7_asset->boneNames = mem.allocate<IW7::scr_string_t>(asset->numBones);
			for (auto i = 0; i < asset->numBones; i++)
			{
				iw7_asset->boneNames[i] = static_cast<IW7::scr_string_t>(asset->boneNames[i]);
			}

			REINTERPRET_CAST_SAFE_TO_FROM(iw7_asset->parentList, asset->parentList);
			REINTERPRET_CAST_SAFE_TO_FROM(iw7_asset->tagAngles, asset->quats);
			REINTERPRET_CAST_SAFE_TO_FROM(iw7_asset->tagPositions, asset->trans);
			REINTERPRET_CAST_SAFE_TO_FROM(iw7_asset->partClassification, asset->partClassification);
			REINTERPRET_CAST_SAFE_TO_FROM(iw7_asset->baseMat, asset->baseMat);
			iw7_asset->reactiveMotionParts = nullptr;

			iw7_asset->materialHandles = mem.allocate<IW7::Material* __ptr64>(asset->numsurfs);
			for (auto i = 0; i < asset->numsurfs; i++)
			{
				if (asset->materialHandles[i])
				{
					iw7_asset->materialHandles[i] = mem.allocate<IW7::Material>();
					iw7_asset->materialHandles[i]->name = mem.duplicate_string(IW7::resolve_material_name(asset->materialHandles[i]->info.name));
				}
			}

			for (auto i = 0; i < 6; i++)
			{
				iw7_asset->lodInfo[i].dist = 1000000.0f;
			}

			// level of detail data
			for (auto i = 0; i < asset->numLods; i++)
			{
				iw7_asset->lodInfo[i].dist = asset->lodInfo[i].dist;
				iw7_asset->lodInfo[i].numsurfs = asset->lodInfo[i].numsurfs;
				iw7_asset->lodInfo[i].surfIndex = asset->lodInfo[i].surfIndex;
				iw7_asset->lodInfo[i].modelSurfs = mem.allocate<IW7::XModelSurfs>();
				iw7_asset->lodInfo[i].modelSurfs->name = mem.duplicate_string(asset->lodInfo[i].modelSurfs->name);
				memcpy(&iw7_asset->lodInfo[i].partBits, &asset->lodInfo[i].partBits, sizeof(asset->lodInfo[i].partBits));
			}

			iw7_asset->maxLoadedLod = asset->maxLoadedLod;
			iw7_asset->numLods = asset->numLods;
			iw7_asset->collLod = asset->collLod;
			iw7_asset->flags = asset->flags;

			iw7_asset->numCollSurfs = asset->numCollSurfs;
			iw7_asset->collSurfs = mem.allocate<IW7::XModelCollSurf_s>(asset->numCollSurfs);
			for (auto i = 0; i < asset->numCollSurfs; i++)
			{
				memcpy(&iw7_asset->collSurfs[i].bounds, &asset->collSurfs[i].bounds, sizeof(float[2][3]));

				iw7_asset->collSurfs[i].boneIdx = asset->collSurfs[i].boneIdx;
				iw7_asset->collSurfs[i].contents = asset->collSurfs[i].contents;
				iw7_asset->collSurfs[i].surfFlags = convert_surf_flags(asset->collSurfs[i].surfFlags);
			}

			iw7_asset->contents = asset->contents;

			REINTERPRET_CAST_SAFE_TO_FROM(iw7_asset->boneInfo, asset->boneInfo);

			iw7_asset->radius = asset->radius;
			memcpy(&iw7_asset->bounds, &asset->bounds, sizeof(asset->bounds));
			iw7_asset->memUsage = asset->memUsage;

			iw7_asset->physicsLODData = nullptr;
			iw7_asset->physicsLODDataSize = 0;
			iw7_asset->physicsLODDataNameCount = 0;
			iw7_asset->physicsLODDataNames = nullptr;
			iw7_asset->physicsAsset = nullptr;

			const auto make_physics_asset = [&](const std::vector<std::uint8_t>& blob)
			{
				auto* physics = mem.allocate<IW7::PhysicsAsset>();
				physics->name = mem.duplicate_string(asset->name);
				physics->havokDataSize = static_cast<unsigned int>(blob.size());
				physics->havokData = mem.allocate<char>(static_cast<unsigned int>(blob.size()));
				std::memcpy(physics->havokData, blob.data(), blob.size());
				physics->numRigidBodies = 1;
				physics->numSFXEventAssets = 1;
				physics->sfxEventAssets = mem.allocate<IW7::PhysicsSFXEventAsset PTR64>(1);
				physics->numVFXEventAssets = 1;
				physics->vfxEventAssets = mem.allocate<IW7::PhysicsVFXEventAsset PTR64>(1);
				return physics;
			};

			{
				const auto* env = std::getenv("ZT_MODEL_DYNAMIC");
				const auto enabled = !(env && env[0] == '0');
				float box_mass = 0.0f;
				const auto box_fallback = enabled && !asset->physCollmap && wants_dynamic_box(asset->name, &box_mass);
				if (enabled && (asset->physCollmap || box_fallback))
				{
					const auto hulls = asset->physCollmap
						? collision::extract_phys_collmap(asset->physCollmap) : std::vector<collision::convex_hull>{};
					ZoneTool::IW7::havok::builder::dynamic_physics_asset_input dynamic{};
					if (box_fallback)
					{
						dynamic.convexes.emplace_back(box_polytope(asset->bounds));
					}
					for (const auto& hull : hulls)
					{
						ZoneTool::IW7::havok::builder::polytope convex{};
						convex.verts = hull.verts;
						for (const auto& face : hull.faces)
						{
							ZoneTool::IW7::havok::builder::polytope_face out{};
							std::memcpy(out.plane, face.plane, sizeof(float[4]));
							out.indices = face.indices;
							convex.faces.emplace_back(std::move(out));
						}
						dynamic.convexes.emplace_back(std::move(convex));
					}

					if (dynamic.convexes.empty())
					{
						ZONETOOL_WARNING("XModel \"%s\": physCollmap \"%s\" produced no hulls -- "
							"falling back to the static collision LOD", asset->name,
							asset->physCollmap && asset->physCollmap->name ? asset->physCollmap->name : "?");
					}
					else
					{
						auto mass_scale = 0.3f;
						if (const auto* scale_env = std::getenv("ZT_MODEL_MASS_SCALE"))
						{
							char* end = nullptr;
							const auto value = std::strtof(scale_env, &end);
							if (end != scale_env && value > 0.0f)
							{
								mass_scale = value;
							}
						}
						dynamic.mass = box_fallback && box_mass > 0.0f ? box_mass * mass_scale
							: asset->physPreset && asset->physPreset->mass > 0.0f
							? asset->physPreset->mass * mass_scale : 5.0f;
						dynamic.mass = std::max(dynamic.mass, 1.0f);
						if (asset->collSurfs && asset->numCollSurfs > 0)
						{
							dynamic.material_crc = collision::iw7_material_crc(asset->collSurfs[0].surfFlags);
						}

						const auto blob = ZoneTool::IW7::havok::builder::build_dynamic_physics_asset(dynamic);
						if (!blob.empty())
						{
							iw7_asset->physicsAsset = make_physics_asset(blob);
							ZONETOOL_INFO("XModel \"%s\": dynamic physics asset from %s "
								"\"%s\" (%zu hull(s), preset \"%s\" mass %.2f)", asset->name,
								box_fallback ? "a bounds box (clutter dynent, no collmap)" : "physCollmap",
								asset->physCollmap && asset->physCollmap->name ? asset->physCollmap->name : "-",
								dynamic.convexes.size(),
								asset->physPreset && asset->physPreset->name ? asset->physPreset->name : "<none>", dynamic.mass);
						}
					}
				}
			}

			{
				constexpr auto model_scale = 0.03125f;
				constexpr auto contents_solid = 0x1;
				constexpr auto contents_foliage = 0x2;
				constexpr auto contents_static_prop = 0x3180u;
				const auto* solid_env = std::getenv("ZT_MODELS_SOLID");
				const auto body_contents = (solid_env && solid_env[0] == '1')
					? 0x32180u : contents_static_prop;

				ZoneTool::IW7::havok::builder::mesh_input mesh{};
				const char* source = nullptr;

				const auto add_triangle = [&mesh](const float (&corners)[3][3], const float* normal,
					const int contents, const unsigned int material_crc, const unsigned short tag,
					const std::uint64_t user_data)
				{
					ZoneTool::IW7::havok::builder::triangle tri{};
					for (auto c = 0; c < 3; c++)
					{
						for (auto k = 0; k < 3; k++)
						{
							tri.verts[c][k] = corners[c][k] * model_scale;
						}
					}

					for (auto c = 0; c < 3; c++)
					{
						const auto n = (c + 1) % 3;
						if (tri.verts[c][0] == tri.verts[n][0] && tri.verts[c][1] == tri.verts[n][1]
							&& tri.verts[c][2] == tri.verts[n][2])
						{
							return;
						}
					}

					if (normal)
					{
						float e1[3], e2[3];
						for (auto k = 0; k < 3; k++)
						{
							e1[k] = tri.verts[1][k] - tri.verts[0][k];
							e2[k] = tri.verts[2][k] - tri.verts[0][k];
						}
						const float cross[3] = {
							e1[1] * e2[2] - e1[2] * e2[1],
							e1[2] * e2[0] - e1[0] * e2[2],
							e1[0] * e2[1] - e1[1] * e2[0],
						};
						if (cross[0] * normal[0] + cross[1] * normal[1] + cross[2] * normal[2] < 0.0f)
						{
							for (auto k = 0; k < 3; k++)
							{
								std::swap(tri.verts[1][k], tri.verts[2][k]);
							}
						}
					}

					tri.contents = contents;
					tri.material_crc = material_crc;
					tri.surface_tag = tag;
					tri.user_data = user_data;
					mesh.triangles.emplace_back(tri);
				};

				if (asset->collSurfs && asset->numCollSurfs > 0)
				{
					for (auto i = 0; i < asset->numCollSurfs; i++)
					{
						const auto& surf = asset->collSurfs[i];

						if (!surf.collTris || surf.numCollTris <= 0
							|| (surf.contents & ~contents_foliage) == 0)
						{
							continue;
						}

						source = "collision LOD";
						const auto material_crc = collision::iw7_material_crc(surf.surfFlags);
						const auto user_data = static_cast<std::uint64_t>(
							static_cast<std::uint32_t>(convert_surf_flags(surf.surfFlags)));

						for (auto t = 0; t < surf.numCollTris; t++)
						{
							const auto& ct = surf.collTris[t];
							const float* rows[3] = {ct.plane, ct.svec, ct.tvec};

							const auto cross = [](const float* a, const float* b, float(&out)[3])
							{
								out[0] = a[1] * b[2] - a[2] * b[1];
								out[1] = a[2] * b[0] - a[0] * b[2];
								out[2] = a[0] * b[1] - a[1] * b[0];
							};

							float c12[3], c20[3], c01[3];
							cross(rows[1], rows[2], c12);
							cross(rows[2], rows[0], c20);
							cross(rows[0], rows[1], c01);

							const auto det = rows[0][0] * c12[0] + rows[0][1] * c12[1]
								+ rows[0][2] * c12[2];
							if (std::fabs(det) < 1e-12f)
							{
								continue;
							}

							constexpr float barycentric[3][2] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
							float corners[3][3];
							for (auto c = 0; c < 3; c++)
							{
								const float rhs[3] = {
									ct.plane[3],
									barycentric[c][0] + ct.svec[3],
									barycentric[c][1] + ct.tvec[3],
								};
								for (auto k = 0; k < 3; k++)
								{
									corners[c][k] = (rhs[0] * c12[k] + rhs[1] * c20[k]
										+ rhs[2] * c01[k]) / det;
								}
							}

							add_triangle(corners, ct.plane, surf.contents, material_crc,
								static_cast<unsigned short>(i), user_data);
						}
					}
				}

				if (mesh.triangles.empty() && asset->physCollmap)
				{
					const auto hulls = collision::extract_phys_collmap(asset->physCollmap);
					const auto contents = asset->contents ? asset->contents : contents_solid;
					const auto user_data = (asset->collSurfs && asset->numCollSurfs > 0)
						? static_cast<std::uint64_t>(static_cast<std::uint32_t>(
							convert_surf_flags(asset->collSurfs[0].surfFlags)))
						: 0ull;

					for (const auto& hull : hulls)
					{
						for (const auto& face : hull.faces)
						{
							for (std::size_t i = 2; i < face.indices.size(); i++)
							{
								const std::size_t corner[3] = {
									face.indices[0], face.indices[i - 1], face.indices[i]
								};
								if (corner[0] >= hull.verts.size() || corner[1] >= hull.verts.size()
									|| corner[2] >= hull.verts.size())
								{
									continue;
								}

								float corners[3][3];
								for (auto c = 0; c < 3; c++)
								{
									for (auto k = 0; k < 3; k++)
									{
										corners[c][k] = hull.verts[corner[c]][k];
									}
								}
								add_triangle(corners, nullptr, contents, 0x1AB7BC33u, 0, user_data);
							}
						}
					}

					source = "physCollmap";
				}

				if (mesh.triangles.empty())
				{
					if (source && !iw7_asset->physicsAsset)
					{
						ZONETOOL_WARNING("XModel \"%s\": %s produced no triangles -- it will collide "
							"with nothing", asset->name, source);
					}
				}
				else if (!iw7_asset->physicsAsset)
				{
					ZoneTool::IW7::havok::builder::physics_asset_input info{};
					info.body_name = asset->name;
					info.body_contents = body_contents;

					auto blob = ZoneTool::IW7::havok::builder::build_model_physics_asset(mesh, info);
					if (!blob.empty())
					{
						auto* physics = mem.allocate<IW7::PhysicsAsset>();
						physics->name = mem.duplicate_string(asset->name);
						physics->havokDataSize = static_cast<unsigned int>(blob.size());
						physics->havokData = mem.allocate<char>(
							static_cast<unsigned int>(blob.size()));
						std::memcpy(physics->havokData, blob.data(), blob.size());
						physics->numRigidBodies = 1;

						physics->numSFXEventAssets = 1;
						physics->sfxEventAssets =
							mem.allocate<IW7::PhysicsSFXEventAsset PTR64>(1);
						physics->numVFXEventAssets = 1;
						physics->vfxEventAssets =
							mem.allocate<IW7::PhysicsVFXEventAsset PTR64>(1);

						iw7_asset->physicsAsset = physics;
					}
				}

				const auto* lod_env = std::getenv("ZT_MODEL_PHYSICS_LOD");
				const auto lod_enabled = !(lod_env && lod_env[0] == '0');
				std::string bone_name = (asset->numBones > 0 && asset->boneNames)
					? Shared::SL_ConvertToString(asset->boneNames[0]) : "";
				if (lod_enabled && !mesh.triangles.empty() && iw7_asset->physicsAsset
					&& bone_name.empty())
				{
					ZONETOOL_INFO("XModel \"%s\": no bones, no physics LOD -- traces on it will "
						"report surfFlags 0", asset->name);
				}
				if (lod_enabled && !mesh.triangles.empty() && iw7_asset->physicsAsset
					&& !bone_name.empty())
				{
					std::transform(bone_name.begin(), bone_name.end(), bone_name.begin(),
						[](const unsigned char c) { return static_cast<char>(std::tolower(c)); });

					auto lod_mesh = mesh;
					for (auto& tri : lod_mesh.triangles)
					{
						tri.contents |= static_cast<int>(body_contents);
					}

					const auto lod_blob = ZoneTool::IW7::havok::builder::build_model_physics_lod(
						lod_mesh, bone_name);
					if (!lod_blob.empty())
					{
						const auto lod_name = std::string(asset->name) + "_lod0";
						iw7_asset->physicsLODDataSize = static_cast<unsigned int>(lod_blob.size());
						iw7_asset->physicsLODData = mem.allocate<char>(iw7_asset->physicsLODDataSize);
						std::memcpy(iw7_asset->physicsLODData, lod_blob.data(), lod_blob.size());
						iw7_asset->physicsLODDataNameCount = 1;
						iw7_asset->physicsLODDataNames = mem.allocate<IW7::scr_string_t>(1);
						iw7_asset->physicsLODDataNames[0] =
							static_cast<IW7::scr_string_t>(Shared::SL_AllocString(lod_name));
					}
				}
			}

			if (asset->physCollmap)
			{
				// ?
				//iw7_asset->physFxShape = mem.allocate<IW7::PhysicsFXShape>();
				//iw7_asset->physFxShape->name = mem.duplicate_string(asset->physCollmap->name);
			}

			// idk
			iw7_asset->invHighMipRadius = mem.allocate<unsigned short>(asset->numsurfs);
			for (unsigned char i = 0; i < asset->numsurfs; i++)
			{
				iw7_asset->invHighMipRadius[i] = 0xFFFF;
			}

			//iw7_asset->quantization = 0.0f;

			iw7_asset->hasLods = asset->numLods ? 1 : 0;
			iw7_asset->shadowCutoffLod = 6;
			iw7_asset->characterCollBoundsType = 1; // CharCollBoundsType_Human

			iw7_asset->unknownIndex = 0xFF;
			iw7_asset->unknownIndex2 = 0xFF;

			//iw7_asset->flags |= 0x40;

			return iw7_asset;
		}

		IW7::XModel* convert(XModel* asset, allocator& allocator)
		{
			// generate IW7 model
			return GenerateIW7Model(asset, allocator);
		}
	}
}
