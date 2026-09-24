#include "stdafx.hpp"
#include "../Include.hpp"

#include "GfxWorld.hpp"
#include "GfxImage.hpp"

#include "X64/Utils/Utils.hpp"
#include "X64/Utils/LightGrid/LightGridSH.hpp"
#include "X64/Utils/LightGrid/LightGridProbes.hpp"
#include "X64/Utils/LightGrid/LightGridTree.hpp"
#include <unordered_map>
#include <unordered_set>

#include "ComWorld.hpp"
#include "GfxWorldUmbra.hpp"

#include <set>
#include <map>

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		//
		//
		namespace
		{
			constexpr unsigned int smodel_probe_samples = 2;

			bool is_sun_light(const unsigned int pli, const unsigned int last_sun)
			{
				const bool low_range_is_sun = ZoneTool::get_linker_mode() == ZoneTool::linker_mode::iw3;
				return (low_range_is_sun && last_sun != 0 && pli >= 1 && pli <= last_sun)
					|| pli >= 256 - last_sun;
			}

			constexpr float light_proxy_pi = 3.14159265358979f;
			constexpr unsigned int light_proxy_segments = 8;
			constexpr unsigned int light_proxy_spot_rings = 3;
			constexpr unsigned int light_proxy_omni_rings = 5;

			constexpr unsigned char light_type_dir = 1;
			constexpr unsigned char light_type_spot = 2;
			constexpr unsigned char light_type_omni = 3;

			constexpr unsigned int sun_trace_rays = 8;
			constexpr float sun_trace_cone = 0.09f;
			constexpr unsigned int sun_trace_max_steps = 384;

			constexpr float light_proxy_wide_spot_cutoff = 1.3962634f;

			constexpr float light_proxy_safety_margin = 1.20f;

			constexpr bool light_proxy_use_sphere = false;
			constexpr float light_proxy_sphere_scale = 2.0f;

			struct proxy_mesh
			{
				std::vector<float> vertices;
				std::vector<unsigned short> indices;

				unsigned short add_vertex(const float* p)
				{
					vertices.push_back(p[0]);
					vertices.push_back(p[1]);
					vertices.push_back(p[2]);
					return static_cast<unsigned short>((vertices.size() / 3) - 1);
				}

				void add_triangle(const unsigned short a, const unsigned short b, const unsigned short c)
				{
					indices.push_back(a);
					indices.push_back(c);
					indices.push_back(b);
				}
			};

			void normalize_proxy_axis(float v[3])
			{
				const auto len = std::sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
				if (len > 0.0f)
				{
					v[0] /= len;
					v[1] /= len;
					v[2] /= len;
				}
			}

			void build_proxy_basis(const float axis[3], float u[3], float v[3])
			{
				float helper[3] = { 0.0f, 0.0f, 1.0f };
				if (std::fabs(axis[2]) > 0.9f)
				{
					helper[0] = 1.0f;
					helper[2] = 0.0f;
				}

				u[0] = (helper[1] * axis[2]) - (helper[2] * axis[1]);
				u[1] = (helper[2] * axis[0]) - (helper[0] * axis[2]);
				u[2] = (helper[0] * axis[1]) - (helper[1] * axis[0]);
				normalize_proxy_axis(u);

				v[0] = (axis[1] * u[2]) - (axis[2] * u[1]);
				v[1] = (axis[2] * u[0]) - (axis[0] * u[2]);
				v[2] = (axis[0] * u[1]) - (axis[1] * u[0]);
				normalize_proxy_axis(v);
			}

			float proxy_circumscribe_scale(const float polar_gap)
			{
				return 1.0f / (std::cos(light_proxy_pi / light_proxy_segments) * std::cos(polar_gap * 0.5f));
			}

			float expand_spot_cone(const float half_angle)
			{
				return std::atan(std::tan(half_angle) / std::cos(light_proxy_pi / light_proxy_segments));
			}

			void add_proxy_ring(proxy_mesh& mesh, const float origin[3], const float axis[3],
				const float u[3], const float v[3], const float theta, const float dist,
				std::vector<unsigned short>& out)
			{
				const auto sin_theta = std::sin(theta);
				const auto cos_theta = std::cos(theta);

				for (unsigned int s = 0; s < light_proxy_segments; s++)
				{
					const auto phi = (2.0f * light_proxy_pi * s) / light_proxy_segments;
					const auto cos_phi = std::cos(phi);
					const auto sin_phi = std::sin(phi);

					float p[3];
					for (int c = 0; c < 3; c++)
					{
						p[c] = origin[c] + (((axis[c] * cos_theta)
							+ (((u[c] * cos_phi) + (v[c] * sin_phi)) * sin_theta)) * dist);
					}
					out.push_back(mesh.add_vertex(p));
				}
			}

			void bridge_proxy_rings(proxy_mesh& mesh, const std::vector<unsigned short>& inner,
				const std::vector<unsigned short>& outer)
			{
				for (unsigned int s = 0; s < light_proxy_segments; s++)
				{
					const auto n = (s + 1) % light_proxy_segments;
					mesh.add_triangle(inner[s], outer[s], outer[n]);
					mesh.add_triangle(inner[s], outer[n], inner[n]);
				}
			}

			void cap_proxy_ring(proxy_mesh& mesh, const unsigned short pole,
				const std::vector<unsigned short>& ring, const bool flip)
			{
				for (unsigned int s = 0; s < light_proxy_segments; s++)
				{
					const auto n = (s + 1) % light_proxy_segments;
					if (flip)
					{
						mesh.add_triangle(pole, ring[n], ring[s]);
					}
					else
					{
						mesh.add_triangle(pole, ring[s], ring[n]);
					}
				}
			}

			void build_spot_proxy(proxy_mesh& mesh, const float origin[3], const float axis[3],
				const float half_angle, const float range)
			{
				float u[3], v[3];
				build_proxy_basis(axis, u, v);

				const auto ring_step = expand_spot_cone(half_angle) / light_proxy_spot_rings;
				const auto dist = range * proxy_circumscribe_scale(ring_step) * light_proxy_safety_margin;

				float tip[3];
				for (int c = 0; c < 3; c++)
				{
					tip[c] = origin[c] + (axis[c] * dist);
				}

				const auto apex = mesh.add_vertex(origin);
				const auto axial = mesh.add_vertex(tip);

				std::vector<std::vector<unsigned short>> rings;
				for (unsigned int k = 1; k <= light_proxy_spot_rings; k++)
				{
					std::vector<unsigned short> ring;
					add_proxy_ring(mesh, origin, axis, u, v, ring_step * k, dist, ring);
					rings.push_back(ring);
				}

				cap_proxy_ring(mesh, axial, rings.front(), false);
				for (std::size_t k = 0; k + 1 < rings.size(); k++)
				{
					bridge_proxy_rings(mesh, rings[k], rings[k + 1]);
				}
				cap_proxy_ring(mesh, apex, rings.back(), true);
			}

			void build_omni_proxy(proxy_mesh& mesh, const float origin[3], const float range)
			{
				constexpr float axis[3] = { 0.0f, 0.0f, 1.0f };
				float u[3], v[3];
				build_proxy_basis(axis, u, v);

				const auto ring_step = light_proxy_pi / (light_proxy_omni_rings + 1);
				const auto dist = range * proxy_circumscribe_scale(ring_step) * light_proxy_safety_margin;

				float pole[3];
				for (int c = 0; c < 3; c++)
				{
					pole[c] = origin[c] + (axis[c] * dist);
				}
				const auto north = mesh.add_vertex(pole);

				for (int c = 0; c < 3; c++)
				{
					pole[c] = origin[c] - (axis[c] * dist);
				}
				const auto south = mesh.add_vertex(pole);

				std::vector<std::vector<unsigned short>> rings;
				for (unsigned int k = 1; k <= light_proxy_omni_rings; k++)
				{
					std::vector<unsigned short> ring;
					add_proxy_ring(mesh, origin, axis, u, v, ring_step * k, dist, ring);
					rings.push_back(ring);
				}

				cap_proxy_ring(mesh, north, rings.front(), false);
				for (std::size_t k = 0; k + 1 < rings.size(); k++)
				{
					bridge_proxy_rings(mesh, rings[k], rings[k + 1]);
				}
				cap_proxy_ring(mesh, south, rings.back(), true);
			}
		}

		unsigned int first_reflection_probe(unsigned int reflection_probe_count)
		{
			return reflection_probe_count > 1 ? 1 : 0;
		}

		IW7::GfxImage* generate_reflection_probe_array_image(GfxWorldDraw* draw, allocator& allocator)
		{
			const std::string image_name = "*reflection_probe_array";
			/*const std::string image_name_clean = "_reflection_probe_array";

			std::uint32_t width = 0, height = 0, mip_levels = 0;
			std::uint16_t depth = 0;
			std::int32_t format = 0;
			bool once = false;

			std::vector<DirectX::Image> images{};

			for (unsigned int image_index = 1; image_index < draw->reflectionProbeCount; image_index++)
			{
				GfxImage* probe_image = draw->reflectionProbes[image_index];
				std::uint8_t* data = probe_image->pixelData;

				if (once) {
					assert(width == probe_image->width && height == probe_image->height && format == probe_image->imageFormat);
				}

				width = probe_image->width;
				height = probe_image->height;
				depth = probe_image->depth;
				mip_levels = probe_image->levelCount;
				format = probe_image->imageFormat;
				once = true;

				for (auto a = 0; a < 6; a++)
				{
					unsigned int divider = 1;
					for (auto i = 0; i < (int)probe_image->levelCount; i++)
					{
						DirectX::Image srcImg{};
						srcImg.width = std::max(1u, probe_image->width / divider);
						srcImg.height = std::max(1u, probe_image->height / divider);
						srcImg.format = DXGI_FORMAT(probe_image->imageFormat);
						srcImg.pixels = data;

						DirectX::ComputePitch(srcImg.format, srcImg.width, srcImg.height, srcImg.rowPitch, srcImg.slicePitch);

						DirectX::ScratchImage hdrTemp;
						auto hr = DirectX::Convert(srcImg, DXGI_FORMAT_R16G16B16A16_FLOAT, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, hdrTemp);

						if (FAILED(hr)) return nullptr;

						auto* persistentPixels = allocator.allocate_array<uint8_t>(hdrTemp.GetPixelsSize());
						memcpy(persistentPixels, hdrTemp.GetPixels(), hdrTemp.GetPixelsSize());

						DirectX::Image finalImg{};
						finalImg.width = srcImg.width;
						finalImg.height = srcImg.height;
						finalImg.format = DXGI_FORMAT_R16G16B16A16_FLOAT;
						finalImg.pixels = persistentPixels;
						DirectX::ComputePitch(finalImg.format, finalImg.width, finalImg.height, finalImg.rowPitch, finalImg.slicePitch);

						images.push_back(finalImg);

						data += srcImg.slicePitch;
						divider *= 2;
					}
				}
			}

			DirectX::TexMetadata mdata{};
			mdata.width = width;
			mdata.height = height;
			mdata.depth = depth;
			mdata.arraySize = (draw->reflectionProbeCount - 1) * 6;
			mdata.mipLevels = mip_levels;
			mdata.format = DXGI_FORMAT_R16G16B16A16_FLOAT;
			mdata.dimension = DirectX::TEX_DIMENSION_TEXTURE2D;
			mdata.miscFlags |= DirectX::TEX_MISC_TEXTURECUBE;

			DirectX::ScratchImage compressed;
			auto hr = DirectX::Compress(images.data(), images.size(), mdata, DXGI_FORMAT_BC6H_UF16, DirectX::TEX_COMPRESS_PARALLEL, DirectX::TEX_THRESHOLD_DEFAULT, compressed);

			if (FAILED(hr)) return nullptr;

			std::string spath = filesystem::get_dump_path() + "images\\" + image_name_clean + ".dds";
			std::wstring wpath(spath.begin(), spath.end());
			std::filesystem::create_directories(filesystem::get_dump_path() + "images\\");

			hr = DirectX::SaveToDDSFile(compressed.GetImages(), compressed.GetImageCount(), compressed.GetMetadata(), DirectX::DDS_FLAGS_NONE, wpath.data());
			if (FAILED(hr)) return nullptr;*/

			auto* image = allocator.allocate<IW7::GfxImage>();
			image->name = allocator.duplicate_string(image_name);
			return image;
		}

		IW7::GfxWorld* GenerateIW7GfxWorld(GfxWorld* asset, allocator& allocator)
		{
			const auto new_asset = allocator.allocate<IW7::GfxWorld>();

			new_asset->name = asset->name;
			new_asset->baseName = asset->baseName;
			new_asset->bspVersion = 159;

			COPY_VALUE(planeCount);
			COPY_VALUE(nodeCount);
			COPY_VALUE(surfaceCount);

			COPY_VALUE(skyCount);
			new_asset->skies = allocator.allocate<IW7::GfxSky>(asset->skyCount);
			for (int i = 0; i < asset->skyCount; i++)
			{
				COPY_VALUE(skies[i].skySurfCount);
				REINTERPRET_CAST_SAFE(skies[i].skyStartSurfs);
				COPY_ASSET(skies[i].skyImage);
				COPY_VALUE(skies[i].skySamplerState);

			}

			COPY_VALUE(lastSunPrimaryLightIndex);
			COPY_VALUE(primaryLightCount);

			new_asset->movingScriptablePrimaryLightCount = 0;

			new_asset->sortKeyLitDecal = 7;
			new_asset->sortKeyEffectDecal = 14;
			new_asset->sortKeyTopDecal = 17;
			new_asset->sortKeyEffectAuto = 35;
			new_asset->sortKeyDistortion = 24;
			new_asset->sortKeyEffectDistortion = 36;
			new_asset->sortKey2D = 41;
			new_asset->sortKeyOpaqueBegin = 1;
			new_asset->sortKeyOpaqueEnd = 6;
			new_asset->sortKeyDecalBegin = 7;
			new_asset->sortKeyDecalEnd = 17;
			new_asset->sortKeyTransBegin = 18;
			new_asset->sortKeyTransEnd = 34;
			new_asset->sortKeyEmissiveBegin = 35;
			new_asset->sortKeyEmissiveEnd = 40;

			//
			const auto source_cell_count = asset->dpvsPlanes.cellCount;
			const auto merge_cells = source_cell_count > 1;

			new_asset->dpvsPlanes.cellCount = merge_cells ? 1 : source_cell_count;
			REINTERPRET_CAST_SAFE(dpvsPlanes.planes);
			REINTERPRET_CAST_SAFE(dpvsPlanes.sceneEntCellBits);
			if (merge_cells)
			{
				new_asset->dpvsPlanes.nodes = allocator.allocate<unsigned short>(asset->nodeCount);
				memcpy(new_asset->dpvsPlanes.nodes, asset->dpvsPlanes.nodes, sizeof(unsigned short) * asset->nodeCount);

				auto* nodes = new_asset->dpvsPlanes.nodes;
				std::vector<int> pending{ 0 };
				while (!pending.empty())
				{
					const auto node = pending.back();
					pending.pop_back();
					if (node < 0 || node + 1 >= asset->nodeCount)
					{
						continue;
					}
					auto& value = nodes[node];
					if (value == 0)
					{
						continue;
					}
					if (value <= source_cell_count)
					{
						value = 1;
						continue;
					}
					value = static_cast<unsigned short>(value - (source_cell_count + 1) + 2);
					pending.push_back(node + 2);
					pending.push_back(node + nodes[node + 1]);
				}

				new_asset->cells = allocator.allocate<IW7::GfxCell>(1);
				float mins[3]{ FLT_MAX, FLT_MAX, FLT_MAX };
				float maxs[3]{ -FLT_MAX, -FLT_MAX, -FLT_MAX };
				for (int i = 0; i < source_cell_count; i++)
				{
					for (int k = 0; k < 3; k++)
					{
						mins[k] = std::min(mins[k], asset->cells[i].bounds.midPoint[k] - asset->cells[i].bounds.halfSize[k]);
						maxs[k] = std::max(maxs[k], asset->cells[i].bounds.midPoint[k] + asset->cells[i].bounds.halfSize[k]);
					}
				}
				for (int k = 0; k < 3; k++)
				{
					new_asset->cells[0].bounds.midPoint[k] = (mins[k] + maxs[k]) * 0.5f;
					new_asset->cells[0].bounds.halfSize[k] = (maxs[k] - mins[k]) * 0.5f;
				}
				new_asset->cells[0].portalCount = 0;
				new_asset->cells[0].portals = nullptr;

				ZONETOOL_INFO("GfxWorld \"%s\": merged %d cells into one", asset->name, source_cell_count);
			}
			else
			{
				REINTERPRET_CAST_SAFE(dpvsPlanes.nodes);
				new_asset->cells = allocator.allocate<IW7::GfxCell>(asset->dpvsPlanes.cellCount);
				for (int i = 0; i < new_asset->dpvsPlanes.cellCount; i++)
				{
					memcpy(&new_asset->cells[i].bounds, &asset->cells[i].bounds, sizeof(float[2][3]));
					new_asset->cells[i].portalCount = asset->cells[i].portalCount;

					auto add_portal = [](IW7::GfxPortal* iw7_portal, IW5::GfxPortal* iw5_portal)
					{
						memcpy(&iw7_portal->plane, &iw5_portal->plane, sizeof(float[4]));
						iw7_portal->vertices = reinterpret_cast<float(PTR64)[3]>(iw5_portal->vertices);
						iw7_portal->cellIndex = iw5_portal->cellIndex;
						iw7_portal->closeDistance = 0;
						iw7_portal->vertexCount = iw5_portal->vertexCount;
						memcpy(&iw7_portal->hullAxis, &iw5_portal->hullAxis, sizeof(float[2][3]));
					};
					new_asset->cells[i].portals = allocator.allocate<IW7::GfxPortal>(new_asset->cells[i].portalCount);
					for (int j = 0; j < new_asset->cells[i].portalCount; j++)
					{
						add_portal(&new_asset->cells[i].portals[j], &asset->cells[i].portals[j]);
					}
				}
			}

			new_asset->cellTransientInfos = allocator.allocate<IW7::GfxCellTransientInfo>(new_asset->dpvsPlanes.cellCount);
			for (unsigned short i = 0; i < new_asset->dpvsPlanes.cellCount; i++)
			{
				new_asset->cellTransientInfos[i].aabbTreeIndex = i;
				new_asset->cellTransientInfos[i].transientZone = 0;
			}

			assert(asset->draw.reflectionProbeCount);

			const auto firstProbe = first_reflection_probe(asset->draw.reflectionProbeCount);
			const auto realProbeCount = asset->draw.reflectionProbeCount - firstProbe;

			new_asset->draw.reflectionProbeData.reflectionProbeCount = realProbeCount;
			new_asset->draw.reflectionProbeData.sharedReflectionProbeCount = 0;
			new_asset->draw.reflectionProbeData.reflectionProbes = allocator.allocate<IW7::GfxReflectionProbe>(realProbeCount);
			new_asset->draw.reflectionProbeData.reflectionProbeArrayImage = generate_reflection_probe_array_image(&asset->draw, allocator);

			new_asset->draw.reflectionProbeData.probeRelightingCount = 0;
			new_asset->draw.reflectionProbeData.probeRelightingData = nullptr;

			new_asset->draw.reflectionProbeData.reflectionProbeGBufferImageCount = 0;
			new_asset->draw.reflectionProbeData.reflectionProbeGBufferImages = nullptr;
			new_asset->draw.reflectionProbeData.reflectionProbeGBufferTextures = nullptr;

			new_asset->draw.reflectionProbeData.reflectionProbeLightgridSampleData =
				allocator.allocate<IW7::GfxReflectionProbeSampleData>(new_asset->draw.reflectionProbeData.reflectionProbeCount);
			new_asset->draw.reflectionProbeData.reflectionProbeLightgridSampleDataBuffer = nullptr;
			new_asset->draw.reflectionProbeData.reflectionProbeLightgridSampleDataBufferView = nullptr;
			new_asset->draw.reflectionProbeData.reflectionProbeLightgridSampleDataBufferRWView = nullptr;

			{
				constexpr float kFallbackVolumeHalfExtent = 262144.0f; // "infinite" bounding volume
				constexpr float kFallbackFeather = 8.0f;

				constexpr float kProbeVolumeMargin = 16.0f;
				constexpr float kProbeVolumeFeather = 32.0f;

				constexpr float kOrphanProbeMinHalfSize = 64.0f;
				constexpr float kOrphanProbeMaxHalfSize = 2048.0f;

				const unsigned int probeCount = realProbeCount;
				const unsigned int totalInstanceCount = probeCount + 1;

				//
				//
				//
				struct probe_region
				{
					unsigned int refs = 0;
					float lo[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
					float hi[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
				};
				std::vector<probe_region> regions(asset->draw.reflectionProbeCount);

				const auto add_probe_bounds = [&regions](const unsigned int probe, const Bounds& bounds)
				{
					if (probe >= regions.size())
					{
						return;
					}
					auto& region = regions[probe];
					region.refs++;
					for (int k = 0; k < 3; k++)
					{
						region.lo[k] = std::min(region.lo[k], bounds.midPoint[k] - bounds.halfSize[k]);
						region.hi[k] = std::max(region.hi[k], bounds.midPoint[k] + bounds.halfSize[k]);
					}
				};

				if (asset->dpvs.surfaces && asset->dpvs.surfacesBounds)
				{
					for (unsigned int i = 0; i < asset->surfaceCount; i++)
					{
						add_probe_bounds(asset->dpvs.surfaces[i].laf.fields.reflectionProbeIndex,
							asset->dpvs.surfacesBounds[i].bounds);
					}
				}
				if (asset->dpvs.smodelDrawInsts && asset->dpvs.smodelInsts)
				{
					for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
					{
						add_probe_bounds(asset->dpvs.smodelDrawInsts[i].reflectionProbeIndex,
							asset->dpvs.smodelInsts[i].bounds);
					}
				}

				const auto nearest_probe_distance = [&](const unsigned int src_index)
				{
					float best = FLT_MAX;
					const auto* a = asset->draw.reflectionProbeOrigins[src_index].origin;
					for (unsigned int j = firstProbe; j < asset->draw.reflectionProbeCount; j++)
					{
						if (j == src_index)
						{
							continue;
						}
						const auto* b = asset->draw.reflectionProbeOrigins[j].origin;
						const float d[3] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
						best = std::min(best, std::sqrt((d[0] * d[0]) + (d[1] * d[1]) + (d[2] * d[2])));
					}
					return best;
				};

				// 1. Allocation
				new_asset->draw.reflectionProbeData.reflectionProbeInstanceCount = totalInstanceCount;

				auto* instances = allocator.allocate<IW7::GfxReflectionProbeInstance>(totalInstanceCount);
				new_asset->draw.reflectionProbeData.reflectionProbeInstances = instances;

				auto* globalProbeInstanceIndices = allocator.allocate<unsigned int>(totalInstanceCount);

				unsigned int reconstructed_volumes = 0;
				unsigned int spacing_volumes = 0;

				for (unsigned int i = 0; i < probeCount; i++)
				{
					const auto srcIndex = firstProbe + i;
					auto& srcProbe = asset->draw.reflectionProbeOrigins[srcIndex];
					auto& dstProbe = new_asset->draw.reflectionProbeData.reflectionProbes[i];
					auto& inst = instances[i];

					// --- probe entry ---
					dstProbe.livePath = nullptr;
					memcpy(dstProbe.origin, srcProbe.origin, sizeof(vec3_t));
					memset(dstProbe.angles, 0, sizeof(vec3_t));
					dstProbe.probeRelightingIndex = static_cast<unsigned int>(-1);
					if (i == 0)
					{
						dstProbe.probeInstanceCount = 2;
						dstProbe.probeInstances = &globalProbeInstanceIndices[0];
						dstProbe.probeInstances[0] = 0;
						dstProbe.probeInstances[1] = probeCount;
					}
					else
					{
						dstProbe.probeInstanceCount = 1;
						dstProbe.probeInstances = &globalProbeInstanceIndices[i + 1];
						dstProbe.probeInstances[0] = i;
					}

					// --- instance entry ---
					memset(&inst, 0, sizeof(inst));
					memcpy(inst.probePosition, srcProbe.origin, sizeof(vec3_t));
					inst.probeImageIndex = static_cast<unsigned short>(i);
					inst.probeRotation[3] = 1.0f; // identity quat
					inst.volumeObb.xAxis[0] = 1.0f;
					inst.volumeObb.yAxis[1] = 1.0f;
					inst.volumeObb.zAxis[2] = 1.0f;

					float half[3];
					const auto& region = regions[srcIndex];
					if (region.refs)
					{
						for (int k = 0; k < 3; k++)
						{
							inst.volumeObb.center[k] = (region.lo[k] + region.hi[k]) * 0.5f;
							half[k] = ((region.hi[k] - region.lo[k]) * 0.5f) + kProbeVolumeMargin;
						}
						reconstructed_volumes++;
					}
					else
					{
						auto extent = nearest_probe_distance(srcIndex) * 0.5f;
						if (!(extent > 0.0f) || extent > kOrphanProbeMaxHalfSize)
						{
							extent = kOrphanProbeMaxHalfSize;
						}
						extent = std::max(extent, kOrphanProbeMinHalfSize);
						for (int k = 0; k < 3; k++)
						{
							inst.volumeObb.center[k] = srcProbe.origin[k];
							half[k] = extent;
						}
						spacing_volumes++;
					}

					memcpy(inst.volumeObb.halfSize, half, sizeof(half));

					inst.priority = -(half[0] + half[1] + half[2]);

					for (int k = 0; k < 3; k++)
					{
						inst.feather[k] = std::min(kProbeVolumeFeather, half[k] * 0.25f);
					}
				}

				{
					auto& inst = instances[probeCount];
					const auto* origin = new_asset->draw.reflectionProbeData.reflectionProbes[0].origin;

					memset(&inst, 0, sizeof(inst));
					memcpy(inst.probePosition, origin, sizeof(vec3_t));
					memcpy(inst.volumeObb.center, origin, sizeof(vec3_t));
					inst.probeImageIndex = 0;
					inst.probeRotation[3] = 1.0f;
					inst.volumeObb.xAxis[0] = 1.0f;
					inst.volumeObb.yAxis[1] = 1.0f;
					inst.volumeObb.zAxis[2] = 1.0f;
					inst.volumeObb.halfSize[0] = kFallbackVolumeHalfExtent;
					inst.volumeObb.halfSize[1] = kFallbackVolumeHalfExtent;
					inst.volumeObb.halfSize[2] = kFallbackVolumeHalfExtent;
					inst.priority = -FLT_MAX;
					inst.feather[0] = inst.feather[1] = inst.feather[2] = kFallbackFeather;
				}

				ZONETOOL_INFO("GfxWorld \"%s\": %u reflection probe instances - %u volumes from the "
					"source assignment, %u from probe spacing, plus the world fallback",
					asset->name, totalInstanceCount, reconstructed_volumes, spacing_volumes);
			}

			// todo...
			//new_asset->draw.lightmapReindexData;

			new_asset->draw.iesLookupTexture = GenerateIesLookup(allocator);

			new_asset->draw.decalVolumeCollectionCount = 0;
			new_asset->draw.decalVolumeCollections = nullptr;

			COPY_ASSET(draw.lightmapOverridePrimary);
			COPY_ASSET(draw.lightmapOverrideSecondary);

			new_asset->draw.lightMapCount = asset->draw.lightmapCount;
			new_asset->draw.lightMaps = allocator.allocate<IW7::GfxLightMap PTR64>(asset->draw.lightmapCount);
			for (int i = 0; i < asset->draw.lightmapCount; i++)
			{
				new_asset->draw.lightMaps[i] = allocator.allocate<IW7::GfxLightMap>();
				new_asset->draw.lightMaps[i]->name = allocator.duplicate_string(va("*lightmap%d", i));
				if (asset->draw.lightmaps[i].primary) // primary
				{
					new_asset->draw.lightMaps[i]->textures[0] = allocator.allocate<IW7::GfxImage>();
					new_asset->draw.lightMaps[i]->textures[0]->name = asset->draw.lightmaps[i].primary->name;
				}
				if (asset->draw.lightmaps[i].secondary) // secondary
				{
					new_asset->draw.lightMaps[i]->textures[1] = allocator.allocate<IW7::GfxImage>();
					new_asset->draw.lightMaps[i]->textures[1]->name = asset->draw.lightmaps[i].secondary->name;
				}
				new_asset->draw.lightMaps[i]->textures[2] = allocator.allocate<IW7::GfxImage>();
				new_asset->draw.lightMaps[i]->textures[2]->name = allocator.duplicate_string(va("*lightmap%d_secondunorm", i));
			}
			new_asset->draw.lightmapTextures = nullptr; // runtime data, allocated elsewhere

			new_asset->draw.unused1 = nullptr;
			new_asset->draw.unused2 = nullptr;
			new_asset->draw.unused3 = nullptr;

			new_asset->draw.transientZoneCount = 1;
			new_asset->draw.transientZones[0] = allocator.allocate<IW7::GfxWorldTransientZone>();
			new_asset->draw.transientZones[0]->name = allocator.duplicate_string(filesystem::get_fastfile());
			new_asset->draw.transientZones[0]->transientZoneIndex = 0;

			new_asset->draw.transientZones[0]->vertexCount = asset->draw.vertexCount;
			new_asset->draw.transientZones[0]->vd.vertices = allocator.allocate<IW7::GfxWorldVertex>(asset->draw.vertexCount);
			for (unsigned int i = 0; i < asset->draw.vertexCount; i++)
			{
				static_assert(sizeof(GfxWorldVertex) == sizeof(IW7::GfxWorldVertex));
				memcpy(&new_asset->draw.transientZones[0]->vd.vertices[i], &asset->draw.vd.vertices[i], sizeof(GfxWorldVertex));

				// re-calculate these...
				float normal_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedVec::Vec3UnpackUnitVec(asset->draw.vd.vertices[i].normal.array, normal_unpacked);

				float tangent_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedVec::Vec3UnpackUnitVec(asset->draw.vd.vertices[i].tangent.array, tangent_unpacked);

				float normal[3] = { normal_unpacked[0], normal_unpacked[1], normal_unpacked[2] };
				float tangent[3] = { tangent_unpacked[0], tangent_unpacked[1], tangent_unpacked[2] };

				new_asset->draw.transientZones[0]->vd.vertices[i].normal.packed = PackedVec::Vec3PackUnitVec(normal);
				new_asset->draw.transientZones[0]->vd.vertices[i].tangent.packed = PackedVec::Vec3PackUnitVec(tangent);

				// correct color : bgra->rgba
				new_asset->draw.transientZones[0]->vd.vertices[i].color.array[0] = asset->draw.vd.vertices[i].color.array[2];
				new_asset->draw.transientZones[0]->vd.vertices[i].color.array[1] = asset->draw.vd.vertices[i].color.array[1];
				new_asset->draw.transientZones[0]->vd.vertices[i].color.array[2] = asset->draw.vd.vertices[i].color.array[0];
				new_asset->draw.transientZones[0]->vd.vertices[i].color.array[3] = asset->draw.vd.vertices[i].color.array[3];
			}

			new_asset->draw.transientZones[0]->vertexLayerDataSize = asset->draw.vertexLayerDataSize;
			new_asset->draw.transientZones[0]->vld.data = asset->draw.vld.data;

			auto convert_aabb_node = [](IW7::GfxAabbTree* dst, const GfxAabbTree* src, int children_index_delta)
			{
				memcpy(&dst->bounds, &src->bounds, sizeof(float[2][3]));
				dst->startSurfIndex = src->startSurfIndex;
				dst->surfaceCount = src->surfaceCount;
				dst->smodelIndexCount = src->smodelIndexCount;
				dst->smodelIndexes = src->smodelIndexes;
				dst->childCount = src->childCount;
				dst->childrenOffset = static_cast<int>(
					(src->childrenOffset / sizeof(GfxAabbTree) + children_index_delta) * sizeof(IW7::GfxAabbTree));
			};

			new_asset->draw.transientZones[0]->cellCount = new_asset->dpvsPlanes.cellCount;
			new_asset->draw.transientZones[0]->aabbTreeCounts = allocator.allocate<IW7::GfxCellTreeCount>(new_asset->dpvsPlanes.cellCount);
			new_asset->draw.transientZones[0]->aabbTrees = allocator.allocate<IW7::GfxCellTree>(new_asset->dpvsPlanes.cellCount);
			if (merge_cells)
			{
				std::vector<int> cell_roots;
				int node_count = 1;
				for (int i = 0; i < source_cell_count; i++)
				{
					if (asset->aabbTreeCounts[i].aabbTreeCount > 0)
					{
						cell_roots.push_back(i);
						node_count += asset->aabbTreeCounts[i].aabbTreeCount;
					}
				}

				auto* tree = allocator.allocate<IW7::GfxAabbTree>(node_count);
				auto& root = tree[0];
				memset(&root, 0, sizeof(root));

				float mins[3]{ FLT_MAX, FLT_MAX, FLT_MAX };
				float maxs[3]{ -FLT_MAX, -FLT_MAX, -FLT_MAX };
				unsigned int surf_begin = UINT_MAX, surf_end = 0;
				std::vector<unsigned short> root_smodels;

				const auto child_slots = static_cast<int>(cell_roots.size());
				int next_node = 1 + child_slots;
				for (int slot = 0; slot < child_slots; slot++)
				{
					const auto cell = cell_roots[slot];
					const auto* src_nodes = asset->aabbTrees[cell].aabbTree;
					const auto src_count = asset->aabbTreeCounts[cell].aabbTreeCount;

					const auto root_slot = 1 + slot;
					convert_aabb_node(&tree[root_slot], &src_nodes[0], next_node - 1 - root_slot);
					for (int j = 1; j < src_count; j++)
					{
						convert_aabb_node(&tree[next_node + j - 1], &src_nodes[j], 0);
					}
					next_node += src_count - 1;

					for (int k = 0; k < 3; k++)
					{
						mins[k] = std::min(mins[k], src_nodes[0].bounds.midPoint[k] - src_nodes[0].bounds.halfSize[k]);
						maxs[k] = std::max(maxs[k], src_nodes[0].bounds.midPoint[k] + src_nodes[0].bounds.halfSize[k]);
					}
					if (src_nodes[0].surfaceCount)
					{
						surf_begin = std::min<unsigned int>(surf_begin, src_nodes[0].startSurfIndex);
						surf_end = std::max<unsigned int>(surf_end, src_nodes[0].startSurfIndex + src_nodes[0].surfaceCount);
					}
					root_smodels.insert(root_smodels.end(), src_nodes[0].smodelIndexes,
						src_nodes[0].smodelIndexes + src_nodes[0].smodelIndexCount);
				}

				for (int k = 0; k < 3; k++)
				{
					root.bounds.midPoint[k] = (mins[k] + maxs[k]) * 0.5f;
					root.bounds.halfSize[k] = (maxs[k] - mins[k]) * 0.5f;
				}
				root.childCount = static_cast<unsigned short>(child_slots);
				root.childrenOffset = static_cast<int>(sizeof(IW7::GfxAabbTree));
				if (surf_begin < surf_end)
				{
					root.startSurfIndex = surf_begin;
					root.surfaceCount = static_cast<unsigned short>(surf_end - surf_begin);
				}
				root.smodelIndexCount = static_cast<unsigned short>(root_smodels.size());
				root.smodelIndexes = root_smodels.empty() ? nullptr
					: allocator.allocate<unsigned short>(root_smodels.size());
				if (root.smodelIndexes)
				{
					memcpy(root.smodelIndexes, root_smodels.data(), sizeof(unsigned short) * root_smodels.size());
				}

				new_asset->draw.transientZones[0]->aabbTreeCounts[0].aabbTreeCount = node_count;
				new_asset->draw.transientZones[0]->aabbTrees[0].aabbTree = tree;
			}
			else
			{
				for (int i = 0; i < asset->dpvsPlanes.cellCount; i++)
				{
					new_asset->draw.transientZones[0]->aabbTreeCounts[i].aabbTreeCount = asset->aabbTreeCounts[i].aabbTreeCount;
					new_asset->draw.transientZones[0]->aabbTrees[i].aabbTree = allocator.allocate<IW7::GfxAabbTree>(asset->aabbTreeCounts[i].aabbTreeCount);
					for (int j = 0; j < asset->aabbTreeCounts[i].aabbTreeCount; j++)
					{
						convert_aabb_node(&new_asset->draw.transientZones[0]->aabbTrees[i].aabbTree[j], &asset->aabbTrees[i].aabbTree[j], 0);
					}
				}
			}

			new_asset->draw.indexCount = asset->draw.indexCount;
			new_asset->draw.indices = asset->draw.indices;

			//
			struct light_cell_box
			{
				unsigned int cells = 0;
				float lo[3] = { 1e30f, 1e30f, 1e30f };
				float hi[3] = { -1e30f, -1e30f, -1e30f };
			};
			std::map<unsigned int, light_cell_box> light_boxes;

			// todo...
			{
				new_asset->draw.volumetrics.volumetricCount = 0;
				new_asset->draw.volumetrics.volumetrics = nullptr;

				constexpr int unk_values[] = { 0, 0, 5, 5, 6, 32, 32, 64, 0 };
				memcpy(new_asset->lightGrid.unk, unk_values, sizeof(unk_values));
				new_asset->lightGrid.tableVersion = 1;
				new_asset->lightGrid.paletteVersion = 1;
				new_asset->lightGrid.rangeExponent8BitsEncoding = 0;
				new_asset->lightGrid.rangeExponent12BitsEncoding = 4;
				new_asset->lightGrid.rangeExponent16BitsEncoding = 23;
				new_asset->lightGrid.stageCount = 0;
				new_asset->lightGrid.stageLightingContrastGain = 0;
				static const int stub_palette_addresses[3] = { 0, 30, 86 };
				static const unsigned char stub_palette_bitstream[116] = {
					0xE7,0x1C,0x00,0xF8,0x08,0x80,0x80,0x80,0x80,0x80,0xF1,0x00,0x08,0x80,0xF8,0x80,
					0x80,0x80,0xB8,0x48,0x00,0x80,0xF8,0x08,0x80,0x80,0x80,0x48,0x48,0x00,0x00,0x00,
					0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x80,0x80,
					0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x5C,0x5E,0x4A,0x3F,
					0xFF,0xFF,0x7F,0x7F,0xFF,0xFF,0x7F,0x7F,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0x7F,0xFF,
					0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
					0x80,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x80,
					0x80,0x80,0x80,0x00,
				};

				new_asset->lightGrid.paletteEntryCount = 3;
				new_asset->lightGrid.paletteEntryAddress = allocator.allocate<int>(3);
				memcpy(new_asset->lightGrid.paletteEntryAddress, stub_palette_addresses,
					sizeof(stub_palette_addresses));
				new_asset->lightGrid.paletteBitstreamSize = sizeof(stub_palette_bitstream);
				new_asset->lightGrid.paletteBitstream =
					allocator.allocate<unsigned char>(sizeof(stub_palette_bitstream));
				memcpy(new_asset->lightGrid.paletteBitstream, stub_palette_bitstream,
					sizeof(stub_palette_bitstream));
				//
				memset(&new_asset->lightGrid.skyLightGridColors, 0, sizeof(IW7::GfxLightGridColorsHDR));
				for (int i = 0; i < 56; i++)
				{
					new_asset->lightGrid.defaultLightGridColors.rgb[i][0] = 0.0f;
					new_asset->lightGrid.defaultLightGridColors.rgb[i][1] = 0.0f;
					new_asset->lightGrid.defaultLightGridColors.rgb[i][2] = 0.21875f;
				}
				static const unsigned int stub_node_table[2] = { 16777217u, 2147483648u };
				static const unsigned char stub_leaf_table[6] = { 0x01, 0x83, 0x00, 0x04, 0x06, 0x11 };

				new_asset->lightGrid.tree.maxDepth = 1;
				new_asset->lightGrid.tree.nodeCount = 2;
				new_asset->lightGrid.tree.leafCount = 1;
				new_asset->lightGrid.tree.coordMinGridSpace[0] = 4092;
				new_asset->lightGrid.tree.coordMinGridSpace[1] = 4092;
				new_asset->lightGrid.tree.coordMinGridSpace[2] = 2047;
				new_asset->lightGrid.tree.coordMaxGridSpace[0] = 4100;
				new_asset->lightGrid.tree.coordMaxGridSpace[1] = 4100;
				new_asset->lightGrid.tree.coordMaxGridSpace[2] = 2049;
				new_asset->lightGrid.tree.coordHalfSizeGridSpace[0] = 4;
				new_asset->lightGrid.tree.coordHalfSizeGridSpace[1] = 4;
				new_asset->lightGrid.tree.coordHalfSizeGridSpace[2] = 1;
				new_asset->lightGrid.tree.defaultColorIndexBitCount = 2;
				new_asset->lightGrid.tree.defaultLightIndexBitCount = 32;
				new_asset->lightGrid.tree.p_nodeTable = allocator.allocate<unsigned int>(2);
				memcpy(new_asset->lightGrid.tree.p_nodeTable, stub_node_table, sizeof(stub_node_table));
				new_asset->lightGrid.tree.leafTableSize = sizeof(stub_leaf_table);
				new_asset->lightGrid.tree.p_leafTable =
					allocator.allocate<unsigned char>(sizeof(stub_leaf_table));
				memcpy(new_asset->lightGrid.tree.p_leafTable, stub_leaf_table, sizeof(stub_leaf_table));

				memset(&new_asset->lightGrid.probeData, 0, sizeof(IW7::GfxLightGridProbeData));
				new_asset->lightGrid.probeData.zoneCount = 1;
				new_asset->lightGrid.probeData.zones = allocator.allocate<IW7::GfxGpuLightGridZone>(1);
				//
				float ambient[3] = { 0.0f, 0.0f, 0.0f };
				if (asset->lightGrid.colorCount && asset->lightGrid.colors)
				{
					std::vector<double> usage(asset->lightGrid.colorCount, 0.0);
					double total_usage = 0.0;
					for (unsigned int i = 0; asset->lightGrid.entries && i < asset->lightGrid.entryCount; i++)
					{
						const auto colors_index = asset->lightGrid.entries[i].colorsIndex;
						if (colors_index < asset->lightGrid.colorCount)
						{
							usage[colors_index] += 1.0;
							total_usage += 1.0;
						}
					}

					if (total_usage == 0.0)
					{
						std::fill(usage.begin(), usage.end(), 1.0);
						total_usage = static_cast<double>(asset->lightGrid.colorCount);
					}

					double accum[3] = { 0.0, 0.0, 0.0 };
					float hdr_colors[56][3];
					for (unsigned int i = 0; i < asset->lightGrid.colorCount; i++)
					{
						if (usage[i] == 0.0)
						{
							continue;
						}

						lightgrid_sh::ldr_colors_to_hdr(asset->lightGrid.colors[i].rgb, hdr_colors);
						double entry[3] = { 0.0, 0.0, 0.0 };
						for (unsigned int j = 0; j < 56; j++)
						{
							entry[0] += hdr_colors[j][0];
							entry[1] += hdr_colors[j][1];
							entry[2] += hdr_colors[j][2];
						}

						for (int c = 0; c < 3; c++)
						{
							accum[c] += (entry[c] / 56.0) * usage[i];
						}
					}

					for (int c = 0; c < 3; c++)
					{
						ambient[c] = static_cast<float>(accum[c] / total_usage);
					}
				}

				constexpr float sh_ambient_scale = 1.0f;

				lightgrid_probes::build_params probe_params{};
				for (int i = 0; i < 3; i++)
				{
					probe_params.bounds_min[i] = asset->bounds.midPoint[i] - asset->bounds.halfSize[i];
					probe_params.bounds_max[i] = asset->bounds.midPoint[i] + asset->bounds.halfSize[i];
				}

				using probe_sh = std::array<float, 28>;
				std::unordered_map<unsigned long long, probe_sh> grid_samples;

				{
					std::vector<probe_sh> colour_cache;
					std::vector<char> colour_cached;
					if (asset->lightGrid.colorCount)
					{
						colour_cache.resize(asset->lightGrid.colorCount, probe_sh{});
						colour_cached.resize(asset->lightGrid.colorCount, 0);
					}

					std::vector<lightgrid_tree::grid_entry_ref> refs;
					if (asset->lightGrid.rowDataStart && asset->lightGrid.rawRowData)
					{
						refs = lightgrid_tree::enumerate_row_data(
							asset->lightGrid.mins, asset->lightGrid.maxs,
							asset->lightGrid.rowAxis, asset->lightGrid.colAxis,
							asset->lightGrid.rowDataStart, asset->lightGrid.rawRowData);
					}

					float bins[56][3];
					for (const auto& ref : refs)
					{
						if (ref.entry_index >= asset->lightGrid.entryCount || !asset->lightGrid.entries)
						{
							continue;
						}
						const auto colors_index = asset->lightGrid.entries[ref.entry_index].colorsIndex;
						if (colors_index >= asset->lightGrid.colorCount || !asset->lightGrid.colors)
						{
							continue;
						}

						if (!colour_cached[colors_index])
						{
							lightgrid_sh::ldr_colors_to_hdr(asset->lightGrid.colors[colors_index].rgb, bins);
							lightgrid_probes::project_sh(bins, lightgrid_sh::grid_basis_dirs, 56,
								sh_ambient_scale, colour_cache[colors_index].data());
							colour_cached[colors_index] = 1;
						}

						const auto key = (static_cast<unsigned long long>(ref.pos[0]) << 32)
							| (static_cast<unsigned long long>(ref.pos[1]) << 16)
							| static_cast<unsigned long long>(ref.pos[2]);

						auto cell = colour_cache[colors_index];
						cell[27] = is_sun_light(asset->lightGrid.entries[ref.entry_index].primaryLightIndex,
							asset->lastSunPrimaryLightIndex) ? 1.0f : 0.0f;
						grid_samples[key] = cell;
					}

					ZONETOOL_INFO("GfxWorld \"%s\": %zu populated light grid cells for probe sampling",
						asset->name, grid_samples.size());

					for (const auto& ref : refs)
					{
						if (ref.entry_index >= asset->lightGrid.entryCount
							|| !asset->lightGrid.entries)
						{
							continue;
						}
						const auto pli = static_cast<unsigned int>(
							asset->lightGrid.entries[ref.entry_index].primaryLightIndex);

						const float world[3] = {
							(static_cast<float>(ref.pos[0]) - 4096.0f) * 32.0f,
							(static_cast<float>(ref.pos[1]) - 4096.0f) * 32.0f,
							(static_cast<float>(ref.pos[2]) - 2048.0f) * 64.0f,
						};

						auto& box = light_boxes[pli];
						box.cells++;
						for (int k = 0; k < 3; k++)
						{
							box.lo[k] = std::min(box.lo[k], world[k]);
							box.hi[k] = std::max(box.hi[k], world[k]);
						}
					}

					for (const auto& kv : light_boxes)
					{
						const auto& b = kv.second;
						ZONETOOL_INFO("GfxWorld \"%s\": lightgrid primaryLightIndex %u -> %u "
							"cells, box (%.0f %.0f %.0f)..(%.0f %.0f %.0f)", asset->name,
							kv.first, b.cells, b.lo[0], b.lo[1], b.lo[2], b.hi[0], b.hi[1], b.hi[2]);
					}

				//
				//
				if (!grid_samples.empty())
				{
					float sun_dir[3] = { 0.0f, 0.0f, 1.0f };
					bool have_sun = false;
					if (const auto sun_world = converter_com_world)
					{
						for (unsigned int i = 0; i < sun_world->primaryLightCount; i++)
						{
							const auto& sun_light = sun_world->primaryLights[i];
							if (sun_light.type != light_type_dir)
							{
								continue;
							}
							const auto len = std::sqrt((sun_light.dir[0] * sun_light.dir[0])
								+ (sun_light.dir[1] * sun_light.dir[1])
								+ (sun_light.dir[2] * sun_light.dir[2]));
							if (len <= 0.0f)
							{
								continue;
							}
							sun_dir[0] = sun_light.dir[0] / len;
							sun_dir[1] = sun_light.dir[1] / len;
							sun_dir[2] = sun_light.dir[2] / len;
							have_sun = true;
							break;
						}
					}

					if (have_sun)
					{
						int lo[3] = { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF };
						int hi[3] = { -0x7FFFFFFF, -0x7FFFFFFF, -0x7FFFFFFF };
						for (const auto& entry : grid_samples)
						{
							const int cell[3] = {
								static_cast<int>((entry.first >> 32) & 0xFFFF),
								static_cast<int>((entry.first >> 16) & 0xFFFF),
								static_cast<int>(entry.first & 0xFFFF),
							};
							for (int k = 0; k < 3; k++)
							{
								lo[k] = std::min(lo[k], cell[k]);
								hi[k] = std::max(hi[k], cell[k]);
							}
						}

						float jitter_u[3], jitter_v[3];
						{
							float helper[3] = { 0.0f, 0.0f, 1.0f };
							if (std::fabs(sun_dir[2]) > 0.9f)
							{
								helper[0] = 1.0f;
								helper[2] = 0.0f;
							}
							jitter_u[0] = (helper[1] * sun_dir[2]) - (helper[2] * sun_dir[1]);
							jitter_u[1] = (helper[2] * sun_dir[0]) - (helper[0] * sun_dir[2]);
							jitter_u[2] = (helper[0] * sun_dir[1]) - (helper[1] * sun_dir[0]);
							normalize_proxy_axis(jitter_u);

							jitter_v[0] = (sun_dir[1] * jitter_u[2]) - (sun_dir[2] * jitter_u[1]);
							jitter_v[1] = (sun_dir[2] * jitter_u[0]) - (sun_dir[0] * jitter_u[2]);
							jitter_v[2] = (sun_dir[0] * jitter_u[1]) - (sun_dir[1] * jitter_u[0]);
							normalize_proxy_axis(jitter_v);
						}

						//
						//
						std::unordered_set<unsigned long long> model_blocked;
						{
							size_t marked = 0;
							for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
							{
								const auto& inst = asset->dpvs.smodelDrawInsts[i];
								if (!inst.model)
								{
									continue;
								}

								const auto* mid = inst.model->bounds.midPoint;
								const auto* half = inst.model->bounds.halfSize;

								float centre[3], extent[3];
								for (int r = 0; r < 3; r++)
								{
									centre[r] = inst.placement.origin[r] + inst.placement.scale
										* ((inst.placement.axis[0][r] * mid[0])
											+ (inst.placement.axis[1][r] * mid[1])
											+ (inst.placement.axis[2][r] * mid[2]));
									extent[r] = inst.placement.scale
										* ((std::fabs(inst.placement.axis[0][r]) * half[0])
											+ (std::fabs(inst.placement.axis[1][r]) * half[1])
											+ (std::fabs(inst.placement.axis[2][r]) * half[2]));
								}

								const int cell_lo[3] = {
									static_cast<int>(std::floor((centre[0] - extent[0]) / 32.0f)) + 4096,
									static_cast<int>(std::floor((centre[1] - extent[1]) / 32.0f)) + 4096,
									static_cast<int>(std::floor((centre[2] - extent[2]) / 64.0f)) + 2048,
								};
								const int cell_hi[3] = {
									static_cast<int>(std::floor((centre[0] + extent[0]) / 32.0f)) + 4096,
									static_cast<int>(std::floor((centre[1] + extent[1]) / 32.0f)) + 4096,
									static_cast<int>(std::floor((centre[2] + extent[2]) / 64.0f)) + 2048,
								};

								const unsigned long long span =
									static_cast<unsigned long long>(cell_hi[0] - cell_lo[0] + 1)
									* static_cast<unsigned long long>(cell_hi[1] - cell_lo[1] + 1)
									* static_cast<unsigned long long>(cell_hi[2] - cell_lo[2] + 1);
								if (span > 200000ull)
								{
									continue;
								}

								for (int z = cell_lo[2]; z <= cell_hi[2]; z++)
								{
									if (z < 0 || z > 0xFFFF) continue;
									for (int y = cell_lo[1]; y <= cell_hi[1]; y++)
									{
										if (y < 0 || y > 0xFFFF) continue;
										for (int x = cell_lo[0]; x <= cell_hi[0]; x++)
										{
											if (x < 0 || x > 0xFFFF) continue;
											model_blocked.insert(
												(static_cast<unsigned long long>(x) << 32)
												| (static_cast<unsigned long long>(y) << 16)
												| static_cast<unsigned long long>(z));
											marked++;
										}
									}
								}
							}
							ZONETOOL_INFO("GfxWorld \"%s\": %u static models occlude %zu grid cells for the "
								"sun visibility bake", asset->name, asset->dpvs.smodelCount, marked);
						}

						unsigned int fully_lit = 0;
						unsigned int fully_dark = 0;
						unsigned int clamped_by_source = 0;

						for (auto& entry : grid_samples)
						{
							const auto source_sees_sun = entry.second[27];

							const float start[3] = {
								static_cast<float>((entry.first >> 32) & 0xFFFF),
								static_cast<float>((entry.first >> 16) & 0xFFFF),
								static_cast<float>(entry.first & 0xFFFF),
							};

							unsigned int open_rays = 0;
							for (unsigned int r = 0; r < sun_trace_rays; r++)
							{
								const auto phi = (2.0f * light_proxy_pi * r) / sun_trace_rays;
								const auto spread = (r == 0) ? 0.0f : sun_trace_cone;

								float dir[3];
								for (int k = 0; k < 3; k++)
								{
									dir[k] = sun_dir[k] + (((jitter_u[k] * std::cos(phi))
										+ (jitter_v[k] * std::sin(phi))) * spread);
								}
								normalize_proxy_axis(dir);

								float step[3] = { dir[0] / 32.0f, dir[1] / 32.0f, dir[2] / 64.0f };
								const auto longest = std::max(std::fabs(step[0]),
									std::max(std::fabs(step[1]), std::fabs(step[2])));
								if (longest <= 0.0f)
								{
									open_rays++;
									continue;
								}
								for (int k = 0; k < 3; k++)
								{
									step[k] /= (longest * 2.0f);
								}

								float pos[3] = { start[0], start[1], start[2] };
								bool escaped = false;
								for (unsigned int walked = 0; walked < sun_trace_max_steps; walked++)
								{
									for (int k = 0; k < 3; k++)
									{
										pos[k] += step[k];
									}

									const int cell[3] = {
										static_cast<int>(std::lround(pos[0])),
										static_cast<int>(std::lround(pos[1])),
										static_cast<int>(std::lround(pos[2])),
									};
									if (cell[0] < lo[0] || cell[0] > hi[0]
										|| cell[1] < lo[1] || cell[1] > hi[1]
										|| cell[2] < lo[2] || cell[2] > hi[2])
									{
										escaped = true;
										break;
									}

									const auto key = (static_cast<unsigned long long>(cell[0]) << 32)
										| (static_cast<unsigned long long>(cell[1]) << 16)
										| static_cast<unsigned long long>(cell[2]);
									if (grid_samples.find(key) == grid_samples.end())
									{
										break;
									}
									if (model_blocked.find(key) != model_blocked.end())
									{
										break;
									}
								}

								if (escaped)
								{
									open_rays++;
								}
							}

							const auto traced = static_cast<float>(open_rays)
								/ static_cast<float>(sun_trace_rays);

							const auto visibility = traced * source_sees_sun;
							if (visibility < traced)
							{
								clamped_by_source++;
							}
							entry.second[27] = visibility;

							if (visibility >= 1.0f)
							{
								fully_lit++;
							}
							else if (visibility <= 0.0f)
							{
								fully_dark++;
							}
						}

						ZONETOOL_INFO("GfxWorld \"%s\": sun visibility traced over %zu cells "
							"(%.1f%% fully lit, %.1f%% fully shadowed, %u clamped by the source "
							"bake), sun dir (%.2f, %.2f, %.2f)",
							asset->name, grid_samples.size(),
							(100.0f * fully_lit) / grid_samples.size(),
							(100.0f * fully_dark) / grid_samples.size(),
							clamped_by_source,
							sun_dir[0], sun_dir[1], sun_dir[2]);
					}
				}

					for (int pass = 0; pass < 2; pass++)
					{
						std::unordered_map<unsigned long long, float> smoothed;
						smoothed.reserve(grid_samples.size());

						for (const auto& entry : grid_samples)
						{
							const auto cx = static_cast<int>((entry.first >> 32) & 0xFFFF);
							const auto cy = static_cast<int>((entry.first >> 16) & 0xFFFF);
							const auto cz = static_cast<int>(entry.first & 0xFFFF);

							float sum = 0.0f;
							int seen = 0;
							for (int dz = -1; dz <= 1; dz++)
							{
								for (int dy = -1; dy <= 1; dy++)
								{
									for (int dx = -1; dx <= 1; dx++)
									{
										const auto x = cx + dx, y = cy + dy, z = cz + dz;
										if (x < 0 || y < 0 || z < 0 || x > 0xFFFF || y > 0xFFFF || z > 0xFFFF)
										{
											continue;
										}
										const auto key = (static_cast<unsigned long long>(x) << 32)
											| (static_cast<unsigned long long>(y) << 16)
											| static_cast<unsigned long long>(z);
										const auto it = grid_samples.find(key);
										if (it != grid_samples.end())
										{
											sum += it->second[27];
											seen++;
										}
									}
								}
							}
							smoothed[entry.first] = seen ? (sum / static_cast<float>(seen)) : entry.second[27];
						}

						for (auto& entry : grid_samples)
						{
							entry.second[27] = smoothed[entry.first];
						}
					}
				}

				constexpr bool debug_position_ramp = false;

				unsigned int resolve_radius_hits[6] = {};

				const auto sample_sh = [&](const float* pos, float* out_sh)
					{
						if (debug_position_ramp)
						{
							float ramp[3];
							for (int c = 0; c < 3; c++)
							{
								const auto span = probe_params.bounds_max[c] - probe_params.bounds_min[c];
								const auto t = span > 0.0f ? (pos[c] - probe_params.bounds_min[c]) / span : 0.0f;
								ramp[c] = std::min(std::max(t, 0.0f), 1.0f) * 0.25f;
							}
							lightgrid_probes::constant_sh(ramp, sh_ambient_scale, out_sh);
							out_sh[27] = 1.0f;
							return;
						}

						const auto gx = static_cast<int>(std::floor(pos[0] / 32.0f)) + 4096;
						const auto gy = static_cast<int>(std::floor(pos[1] / 32.0f)) + 4096;
						const auto gz = static_cast<int>(std::floor(pos[2] / 64.0f)) + 2048;

						//
						constexpr int probe_resolve_max_radius = 1;
						for (int radius = 0; radius <= probe_resolve_max_radius; radius++)
						{
							const float* best = nullptr;
							int best_dist = 0x7FFFFFFF;
							for (int dz = -radius; dz <= radius; dz++)
							{
								for (int dy = -radius; dy <= radius; dy++)
								{
									for (int dx = -radius; dx <= radius; dx++)
									{
										if (std::max(std::max(std::abs(dx), std::abs(dy)), std::abs(dz)) != radius)
										{
											continue;
										}
										const auto x = gx + dx, y = gy + dy, z = gz + dz;
										if (x < 0 || y < 0 || z < 0 || x > 0xFFFF || y > 0xFFFF || z > 0xFFFF)
										{
											continue;
										}
										const auto key = (static_cast<unsigned long long>(x) << 32)
											| (static_cast<unsigned long long>(y) << 16)
											| static_cast<unsigned long long>(z);
										const auto it = grid_samples.find(key);
										if (it == grid_samples.end())
										{
											continue;
										}
										const auto dist = dx * dx + dy * dy + 4 * dz * dz;
										if (dist < best_dist)
										{
											best_dist = dist;
											best = it->second.data();
										}
									}
								}
							}
							if (best)
							{
								resolve_radius_hits[radius]++;
								memcpy(out_sh, best, sizeof(float) * 28);
								return;
							}
						}

						resolve_radius_hits[5]++;
						lightgrid_probes::constant_sh(ambient, sh_ambient_scale, out_sh);
						out_sh[27] = 1.0f;
					};

				//
				if (!grid_samples.empty())
				{
					probe_params.cell_occupied = [&grid_samples](const float* lo, const float size)
					{
						const auto lo_x = static_cast<int>(std::floor(lo[0] / 32.0f)) + 4096 - 1;
						const auto hi_x = static_cast<int>(std::floor((lo[0] + size) / 32.0f)) + 4096 + 1;
						const auto lo_y = static_cast<int>(std::floor(lo[1] / 32.0f)) + 4096 - 1;
						const auto hi_y = static_cast<int>(std::floor((lo[1] + size) / 32.0f)) + 4096 + 1;
						const auto lo_z = static_cast<int>(std::floor(lo[2] / 64.0f)) + 2048 - 1;
						const auto hi_z = static_cast<int>(std::floor((lo[2] + size) / 64.0f)) + 2048 + 1;

						for (int z = lo_z; z <= hi_z; z++)
						{
							if (z < 0 || z > 0xFFFF) continue;
							for (int y = lo_y; y <= hi_y; y++)
							{
								if (y < 0 || y > 0xFFFF) continue;
								for (int x = lo_x; x <= hi_x; x++)
								{
									if (x < 0 || x > 0xFFFF) continue;
									const auto key = (static_cast<unsigned long long>(x) << 32)
										| (static_cast<unsigned long long>(y) << 16)
										| static_cast<unsigned long long>(z);
									if (grid_samples.find(key) != grid_samples.end())
									{
										return true;
									}
								}
							}
						}
						return false;
					};
				}

				const auto volume = lightgrid_probes::build(probe_params, sample_sh, sh_ambient_scale);

				{
					ZONETOOL_INFO("GfxWorld \"%s\": probe resolve radius 0=%u 1=%u 2=%u 3=%u 4=%u, map-average fallback=%u",
						asset->name, resolve_radius_hits[0], resolve_radius_hits[1], resolve_radius_hits[2],
						resolve_radius_hits[3], resolve_radius_hits[4], resolve_radius_hits[5]);

					std::vector<float> pal_lum;
					pal_lum.reserve(grid_samples.size());
					for (const auto& kv : grid_samples)
					{
						const auto& sh = kv.second;
						pal_lum.push_back((0.2126f * sh[0]) + (0.7152f * sh[9]) + (0.0722f * sh[18]));
					}
					if (!pal_lum.empty())
					{
						std::sort(pal_lum.begin(), pal_lum.end());
						const auto at = [&](const double f)
						{
							return pal_lum[static_cast<size_t>(f * (pal_lum.size() - 1))];
						};
						ZONETOOL_INFO("GfxWorld \"%s\": source cell luminance min=%.4f p5=%.4f p50=%.4f p95=%.4f max=%.4f over %zu cells",
							asset->name, pal_lum.front(), at(0.05), at(0.50), at(0.95), pal_lum.back(), pal_lum.size());
					}
				}

				//
				//
				//
				//
				std::vector<unsigned short> voxel_leaf_light_address;
				std::vector<unsigned short> voxel_light_list;
				if (volume.valid && volume.leaf_count && converter_com_world && !grid_samples.empty()
					&& volume.leaf_size > 0.0f
					&& volume.leaf_bounds_min.size() >= static_cast<size_t>(volume.leaf_count) * 3)
				{
					constexpr float light_trace_step = 16.0f;
					constexpr float light_trace_slack = 48.0f;
					constexpr unsigned short light_list_empty_address = 2;
					constexpr size_t light_list_max_per_leaf = 16;

					//
					constexpr bool light_list_spot_only = true;

					struct local_light
					{
						unsigned short index;
						bool is_spot;
						float origin[3];
						float axis[3];
						float radius;
						float half_fov;
					};

					std::vector<local_light> locals;
					{
						const auto count = std::min<unsigned int>(new_asset->primaryLightCount,
							converter_com_world->primaryLightCount);
						for (unsigned int i = 0; i < count && i <= 0xFFFF; i++)
						{
							const auto& src = converter_com_world->primaryLights[i];
							const auto type = static_cast<unsigned char>(src.type);
							if (type != light_type_spot && type != light_type_omni)
							{
								continue;
							}
							if (light_list_spot_only && type != light_type_spot)
							{
								continue;
							}
							if (!(src.radius > 0.0f))
							{
								continue;
							}

							local_light light{};
							light.index = static_cast<unsigned short>(i);
							light.is_spot = (type == light_type_spot);
							memcpy(light.origin, src.origin, sizeof(light.origin));
							light.radius = src.radius;

							float axis[3] = { -src.dir[0], -src.dir[1], -src.dir[2] };
							const auto len = std::sqrt((axis[0] * axis[0]) + (axis[1] * axis[1])
								+ (axis[2] * axis[2]));
							if (len > 0.0f)
							{
								for (int k = 0; k < 3; k++)
								{
									light.axis[k] = axis[k] / len;
								}
							}
							else
							{
								light.axis[2] = -1.0f;
								light.is_spot = false;
							}

							light.half_fov = std::acos(std::max(-1.0f,
								std::min(1.0f, src.cosHalfFovOuter)));
							locals.push_back(light);
						}
					}

					const auto cell_open = [&grid_samples](const float p[3])
					{
						const auto x = static_cast<int>(std::floor(p[0] / 32.0f)) + 4096;
						const auto y = static_cast<int>(std::floor(p[1] / 32.0f)) + 4096;
						const auto z = static_cast<int>(std::floor(p[2] / 64.0f)) + 2048;
						if (x < 0 || x > 0xFFFF || y < 0 || y > 0xFFFF || z < 0 || z > 0xFFFF)
						{
							return false;
						}
						const auto key = (static_cast<unsigned long long>(x) << 32)
							| (static_cast<unsigned long long>(y) << 16)
							| static_cast<unsigned long long>(z);
						return grid_samples.find(key) != grid_samples.end();
					};

					const auto reaches = [&](const float from[3], const float to[3])
					{
						float dir[3] = { to[0] - from[0], to[1] - from[1], to[2] - from[2] };
						const auto dist = std::sqrt((dir[0] * dir[0]) + (dir[1] * dir[1])
							+ (dir[2] * dir[2]));
						if (dist <= light_trace_slack)
						{
							return true;
						}
						for (int k = 0; k < 3; k++)
						{
							dir[k] /= dist;
						}

						const auto stop = dist - light_trace_slack;
						for (auto t = light_trace_step; t < stop; t += light_trace_step)
						{
							const float p[3] = {
								from[0] + (dir[0] * t),
								from[1] + (dir[1] * t),
								from[2] + (dir[2] * t),
							};
							if (!cell_open(p))
							{
								return false;
							}
						}
						return true;
					};

					voxel_leaf_light_address.assign(volume.leaf_count, light_list_empty_address);
					voxel_light_list = { 16384, 1, 0 };

					std::map<std::vector<unsigned short>, unsigned short> list_address;
					std::vector<std::pair<float, unsigned short>> ranked;
					std::vector<unsigned short> hits;
					unsigned int lit_leaves = 0;
					unsigned int clamped_leaves = 0;
					unsigned int dropped_leaves = 0;

					const auto half = volume.leaf_size * 0.5f;
					const auto half_diag = half * 1.7320508f;
					const auto inset = volume.leaf_size * 0.25f;

					for (unsigned int l = 0; l < volume.leaf_count; l++)
					{
						const auto* lo = &volume.leaf_bounds_min[static_cast<size_t>(l) * 3];
						const float centre[3] = { lo[0] + half, lo[1] + half, lo[2] + half };

						ranked.clear();
						for (const auto& light : locals)
						{
							const float delta[3] = {
								centre[0] - light.origin[0],
								centre[1] - light.origin[1],
								centre[2] - light.origin[2],
							};
							const auto dist = std::sqrt((delta[0] * delta[0])
								+ (delta[1] * delta[1]) + (delta[2] * delta[2]));

							if (dist - half_diag > light.radius)
							{
								continue;
							}

							if (light.is_spot && dist > 0.001f)
							{
								const auto dot = ((delta[0] * light.axis[0])
									+ (delta[1] * light.axis[1])
									+ (delta[2] * light.axis[2])) / dist;
								const auto theta = std::acos(std::max(-1.0f, std::min(1.0f, dot)));
								const auto slack = std::asin(std::min(1.0f, half_diag / dist));
								if (theta > light.half_fov + slack)
								{
									continue;
								}
							}

							auto seen = false;
							for (int s = 0; s < 9 && !seen; s++)
							{
								float p[3];
								if (s == 0)
								{
									memcpy(p, centre, sizeof(p));
								}
								else
								{
									const auto c = s - 1;
									p[0] = lo[0] + ((c & 1) ? volume.leaf_size - inset : inset);
									p[1] = lo[1] + ((c & 2) ? volume.leaf_size - inset : inset);
									p[2] = lo[2] + ((c & 4) ? volume.leaf_size - inset : inset);
								}
								if (!cell_open(p))
								{
									continue;
								}
								seen = reaches(p, light.origin);
							}
							if (!seen)
							{
								continue;
							}

							ranked.emplace_back(dist, light.index);
						}

						if (ranked.empty())
						{
							continue;
						}

						std::sort(ranked.begin(), ranked.end());
						if (ranked.size() > light_list_max_per_leaf)
						{
							ranked.resize(light_list_max_per_leaf);
							clamped_leaves++;
						}

						hits.clear();
						for (const auto& r : ranked)
						{
							hits.push_back(r.second);
						}
						std::sort(hits.begin(), hits.end());

						const auto found = list_address.find(hits);
						if (found != list_address.end())
						{
							voxel_leaf_light_address[l] = found->second;
							lit_leaves++;
							continue;
						}

						if (voxel_light_list.size() + hits.size() + 1 > 0xFFFF)
						{
							dropped_leaves++;
							continue;
						}

						const auto address = static_cast<unsigned short>(voxel_light_list.size());
						voxel_light_list.push_back(static_cast<unsigned short>(hits.size() << 7));
						voxel_light_list.insert(voxel_light_list.end(), hits.begin(), hits.end());
						list_address.emplace(hits, address);
						voxel_leaf_light_address[l] = address;
						lit_leaves++;
					}

					{
						float ext_lo[3] = { 1e30f, 1e30f, 1e30f };
						float ext_hi[3] = { -1e30f, -1e30f, -1e30f };
						for (unsigned int l = 0; l < volume.leaf_count; l++)
						{
							const auto* lo = &volume.leaf_bounds_min[static_cast<size_t>(l) * 3];
							for (int k = 0; k < 3; k++)
							{
								ext_lo[k] = std::min(ext_lo[k], lo[k]);
								ext_hi[k] = std::max(ext_hi[k], lo[k] + volume.leaf_size);
							}
						}
						for (int k = 0; k < 3; k++)
						{
							if (ext_lo[k] < volume.bound_min[k] - 0.5f
								|| ext_hi[k] > volume.bound_max[k] + 0.5f)
							{
								ZONETOOL_WARNING("GfxWorld \"%s\": leaf boxes run outside the voxel "
									"tree bounds on axis %d (%.1f..%.1f vs %.1f..%.1f)", asset->name,
									k, ext_lo[k], ext_hi[k], volume.bound_min[k], volume.bound_max[k]);
								break;
							}
						}

						ZONETOOL_INFO("GfxWorld \"%s\": %zu local lights over %u leaves of %.0f "
							"units, spanning %.0f %.0f %.0f .. %.0f %.0f %.0f", asset->name,
							locals.size(), volume.leaf_count, volume.leaf_size,
							ext_lo[0], ext_lo[1], ext_lo[2], ext_hi[0], ext_hi[1], ext_hi[2]);
					}

					ZONETOOL_INFO("GfxWorld \"%s\": voxel light lists - %u/%u leaves lit (%.1f%%), "
						"%zu distinct lists, %zu entries", asset->name, lit_leaves, volume.leaf_count,
						volume.leaf_count ? (100.0f * lit_leaves) / volume.leaf_count : 0.0f,
						list_address.size(), voxel_light_list.size());

					if (clamped_leaves || dropped_leaves)
					{
						ZONETOOL_WARNING("GfxWorld \"%s\": %u leaves clamped to %zu lights, %u left "
							"unlit because the light list array filled up", asset->name,
							clamped_leaves, light_list_max_per_leaf, dropped_leaves);
					}

					if (!locals.empty() && !lit_leaves)
					{
						ZONETOOL_WARNING("GfxWorld \"%s\": %zu local lights reach no voxel at all - "
							"every one will be culled everywhere", asset->name, locals.size());
					}

					//
					//
					//
					{
						constexpr size_t light_list_max_per_object = 24;

						struct receiver_light
						{
							unsigned short index;
							bool directional;
							bool is_spot;
							float origin[3];
							float axis[3];
							float radius;
							float half_fov;
						};

						std::vector<receiver_light> receivers;
						{
							const auto count = std::min<unsigned int>(new_asset->primaryLightCount,
								converter_com_world->primaryLightCount);
							for (unsigned int i = 0; i < count && i <= 0xFFFF; i++)
							{
								const auto& src = converter_com_world->primaryLights[i];
								const auto type = static_cast<unsigned char>(src.type);

								receiver_light light{};
								light.index = static_cast<unsigned short>(i);

								if (type == light_type_dir)
								{
									light.directional = true;
								}
								else if (type == light_type_spot || type == light_type_omni)
								{
									if (!(src.radius > 0.0f))
									{
										continue;
									}

									light.is_spot = (type == light_type_spot);
									memcpy(light.origin, src.origin, sizeof(light.origin));
									light.radius = src.radius;

									float axis[3] = { -src.dir[0], -src.dir[1], -src.dir[2] };
									const auto len = std::sqrt((axis[0] * axis[0])
										+ (axis[1] * axis[1]) + (axis[2] * axis[2]));
									if (len > 0.0f)
									{
										for (int k = 0; k < 3; k++)
										{
											light.axis[k] = axis[k] / len;
										}
									}
									else
									{
										light.axis[2] = -1.0f;
										light.is_spot = false;
									}

									light.half_fov = std::acos(std::max(-1.0f,
										std::min(1.0f, src.cosHalfFovOuter)));
								}
								else
								{
									continue;
								}

								receivers.push_back(light);
							}
						}

						std::vector<unsigned short> hits;
						const auto list_for = [&](const Bounds& bounds)
						{
							hits.clear();

							const auto extent = std::sqrt(
								(bounds.halfSize[0] * bounds.halfSize[0])
								+ (bounds.halfSize[1] * bounds.halfSize[1])
								+ (bounds.halfSize[2] * bounds.halfSize[2]));

							for (const auto& light : receivers)
							{
								if (light.directional)
								{
									hits.push_back(light.index);
									continue;
								}

								const float delta[3] = {
									bounds.midPoint[0] - light.origin[0],
									bounds.midPoint[1] - light.origin[1],
									bounds.midPoint[2] - light.origin[2],
								};
								const auto dist = std::sqrt((delta[0] * delta[0])
									+ (delta[1] * delta[1]) + (delta[2] * delta[2]));

								if (dist - extent > light.radius)
								{
									continue;
								}

								if (light.is_spot && dist > 0.001f)
								{
									const auto dot = ((delta[0] * light.axis[0])
										+ (delta[1] * light.axis[1])
										+ (delta[2] * light.axis[2])) / dist;
									const auto theta = std::acos(std::max(-1.0f,
										std::min(1.0f, dot)));
									const auto slack = std::asin(std::min(1.0f, extent / dist));
									if (theta > light.half_fov + slack)
									{
										continue;
									}
								}

								if (!reaches(light.origin, bounds.midPoint))
								{
									continue;
								}

								hits.push_back(light.index);
							}
						};

						std::vector<unsigned short> lists;
						lists.push_back(0);
						std::map<std::vector<unsigned short>, unsigned int> list_offset;
						size_t clamped = 0;

						const auto intern = [&]() -> unsigned int
						{
							if (hits.size() > light_list_max_per_object)
							{
								hits.resize(light_list_max_per_object);
								clamped++;
							}
							if (hits.empty())
							{
								return 0;
							}

							const auto found = list_offset.find(hits);
							if (found != list_offset.end())
							{
								return found->second;
							}

							const auto offset = static_cast<unsigned int>(lists.size());
							lists.push_back(static_cast<unsigned short>(hits.size()));
							lists.insert(lists.end(), hits.begin(), hits.end());
							list_offset.emplace(hits, offset);
							return offset;
						};

						const auto surface_count = std::min(asset->dpvs.staticSurfaceCount,
							asset->surfaceCount);
						const auto smodel_count = asset->dpvs.smodelCount;

						std::vector<unsigned int> surface_offsets(surface_count, 0);
						std::vector<unsigned int> smodel_offsets(smodel_count, 0);

						if (asset->dpvs.surfacesBounds)
						{
							for (unsigned int i = 0; i < surface_count; i++)
							{
								list_for(asset->dpvs.surfacesBounds[i].bounds);
								surface_offsets[i] = intern();
							}
						}

						if (asset->dpvs.smodelInsts)
						{
							for (unsigned int i = 0; i < smodel_count; i++)
							{
								list_for(asset->dpvs.smodelInsts[i].bounds);
								smodel_offsets[i] = intern();
							}
						}

						new_asset->lightLists.surfaceListOffsetCount = surface_count;
						new_asset->lightLists.smodelListOffsetCount = smodel_count;
						new_asset->lightLists.listsSize = static_cast<unsigned int>(lists.size());

						if (surface_count)
						{
							new_asset->lightLists.surfaceListOffsets =
								allocator.allocate<unsigned int>(surface_count);
							memcpy(new_asset->lightLists.surfaceListOffsets, surface_offsets.data(),
								sizeof(unsigned int) * surface_count);
						}
						if (smodel_count)
						{
							new_asset->lightLists.smodelListOffsets =
								allocator.allocate<unsigned int>(smodel_count);
							memcpy(new_asset->lightLists.smodelListOffsets, smodel_offsets.data(),
								sizeof(unsigned int) * smodel_count);
						}
						new_asset->lightLists.lists =
							allocator.allocate<unsigned short>(lists.size());
						memcpy(new_asset->lightLists.lists, lists.data(),
							sizeof(unsigned short) * lists.size());

						size_t lit_surfaces = 0;
						for (const auto offset : surface_offsets) { lit_surfaces += (offset != 0); }
						size_t lit_smodels = 0;
						for (const auto offset : smodel_offsets) { lit_smodels += (offset != 0); }

						ZONETOOL_INFO("GfxWorld \"%s\": light lists - %zu/%u surfaces and %zu/%u "
							"static models lit by %zu lights, %zu distinct lists, %zu entries",
							asset->name, lit_surfaces, surface_count, lit_smodels, smodel_count,
							receivers.size(), list_offset.size(), lists.size());

						if (clamped)
						{
							ZONETOOL_WARNING("GfxWorld \"%s\": %zu light lists clamped to %zu "
								"entries", asset->name, clamped, light_list_max_per_object);
						}
					}
				}
				else if (volume.valid && volume.leaf_count)
				{
					ZONETOOL_WARNING("GfxWorld \"%s\": no voxel light lists (com world %s, %zu grid "
						"cells, %u leaves, %.1f unit leaves) - local lights will not be culled by "
						"geometry", asset->name, converter_com_world ? "ok" : "MISSING",
						grid_samples.size(), volume.leaf_count, volume.leaf_size);
				}

				auto& zone = *new_asset->lightGrid.probeData.zones;
				if (volume.valid)
				{
					auto& pd = new_asset->lightGrid.probeData;

					//
					//
					const auto smodel_count = asset->dpvs.smodelCount;
					const auto sample_probe_count = smodel_count * smodel_probe_samples;

					pd.gpuVisibleProbesCount = sample_probe_count;
					pd.gpuVisibleProbePositions = allocator.allocate<IW7::GfxGpuLightGridProbePosition>(
						sample_probe_count ? sample_probe_count : 1);

					pd.gpuVisibleProbesData =
						allocator.allocate<IW7::GfxSHProbeData>(sample_probe_count + 0x2000);

					for (unsigned int i = 0; i < smodel_count; i++)
					{
						const auto& placement = asset->dpvs.smodelDrawInsts[i].placement;

						//
						float position[3] = { placement.origin[0], placement.origin[1],
							placement.origin[2] };
						if (const auto* model = asset->dpvs.smodelDrawInsts[i].model)
						{
							const auto* mid = model->bounds.midPoint;
							for (int r = 0; r < 3; r++)
							{
								position[r] += placement.scale
									* ((placement.axis[0][r] * mid[0])
										+ (placement.axis[1][r] * mid[1])
										+ (placement.axis[2][r] * mid[2]));
							}
						}

						float sh[28] = {};
						sample_sh(position, sh);
						unsigned short coeffs[32];
						lightgrid_probes::encode_probe_sh(sh, coeffs);

						for (unsigned int k = 0; k < smodel_probe_samples; k++)
						{
							const auto slot = (i * smodel_probe_samples) + k;
							memcpy(pd.gpuVisibleProbePositions[slot].origin, position, sizeof(position));
							memcpy(&pd.gpuVisibleProbesData[slot], coeffs, sizeof(coeffs));
						}
					}

					pd.probeCount = volume.probe_count;
					pd.probes = allocator.allocate<IW7::GfxSHProbeData>(volume.probe_count);
					memcpy(pd.probes, volume.probes.data(), sizeof(unsigned short) * volume.probes.size());
					pd.probePositions = allocator.allocate<IW7::GfxGpuLightGridProbePosition>(volume.probe_count);
					memcpy(pd.probePositions, volume.probe_positions.data(),
						sizeof(float) * volume.probe_positions.size());

					pd.tetrahedronCount = volume.tetrahedron_count;
					pd.tetrahedrons = allocator.allocate<IW7::GfxGpuLightGridTetrahedron>(volume.tetrahedron_count);
					memcpy(pd.tetrahedrons, volume.tetrahedrons.data(),
						sizeof(unsigned int) * volume.tetrahedrons.size());
					pd.tetrahedronNeighbors =
						allocator.allocate<IW7::GfxGpuLightGridTetrahedronNeighbors>(volume.tetrahedron_count);
					memcpy(pd.tetrahedronNeighbors, volume.tetrahedron_neighbors.data(),
						sizeof(unsigned int) * volume.tetrahedron_neighbors.size());

					//
					//
					//
					//
					unsigned int visible_tets = 0;
					for (unsigned int t = 0; t < volume.tetrahedron_count; t++)
					{
						for (int k = 0; k < 4; k++)
						{
							if (volume.tetrahedrons[(t * 4) + k] & 0x80000000u)
							{
								visible_tets++;
								break;
							}
						}
					}

					pd.tetrahedronCountVisible = visible_tets;
					if (visible_tets)
					{
						pd.tetrahedronVisibility =
							allocator.allocate<IW7::GfxGpuLightGridTetrahedronVisibility>(visible_tets);
						memset(pd.tetrahedronVisibility, 0xFF,
							sizeof(IW7::GfxGpuLightGridTetrahedronVisibility) * visible_tets);
					}
					else
					{
						pd.tetrahedronVisibility = nullptr;
					}

					pd.voxelStartTetrahedronCount = static_cast<unsigned int>(volume.voxel_start_tetrahedron.size());
					pd.voxelStartTetrahedron = allocator.allocate<IW7::GfxGpuLightGridVoxelStartTetrahedron>(
						pd.voxelStartTetrahedronCount);
					memcpy(pd.voxelStartTetrahedron, volume.voxel_start_tetrahedron.data(),
						sizeof(unsigned int) * volume.voxel_start_tetrahedron.size());

					zone.numProbes = volume.zone_num_probes;
					zone.firstProbe = volume.zone_first_probe;
					zone.numTetrahedrons = volume.zone_num_tetrahedrons;
					zone.firstTetrahedron = volume.zone_first_tetrahedron;
					zone.firstVoxelTetrahedronIndex = volume.zone_first_voxel_tetrahedron_index;
					zone.numVoxelTetrahedronIndices = volume.zone_num_voxel_tetrahedron_indices;

					new_asset->voxelTreeCount = 1;
					new_asset->voxelTree = allocator.allocate<IW7::GfxVoxelTree>(1);
					auto& tree = new_asset->voxelTree[0];
					//
					for (int i = 0; i < 3; i++)
					{
						tree.zoneBound.midPoint[i] = (volume.bound_min[i] + volume.bound_max[i]) * 0.5f;
						tree.zoneBound.halfSize[i] = (volume.bound_max[i] - volume.bound_min[i]) * 0.5f;
					}
					tree.voxelTopDownViewNodeCount = static_cast<int>(volume.top_down_view_nodes.size());
					tree.voxelInternalNodeCount = static_cast<int>(volume.internal_nodes.size());
					const auto have_baked_lights =
						voxel_leaf_light_address.size() == volume.leaf_nodes.size()
						&& !voxel_light_list.empty();
					const auto& leaf_addresses =
						have_baked_lights ? voxel_leaf_light_address : volume.leaf_nodes;
					const auto& light_list =
						have_baked_lights ? voxel_light_list : volume.light_list;

					tree.voxelLeafNodeCount = static_cast<int>(leaf_addresses.size());
					tree.lightListArraySize = static_cast<int>(light_list.size());

					tree.voxelTreeHeader = allocator.allocate<IW7::GfxVoxelTreeHeader>();
					memcpy(tree.voxelTreeHeader->rootNodeDimension, volume.root_node_dimension, sizeof(int[4]));
					memcpy(tree.voxelTreeHeader->nodeCoordBitShift, volume.node_coord_bit_shift, sizeof(int[4]));
					memcpy(&tree.voxelTreeHeader->boundMin, volume.bound_min, sizeof(float[4]));
					memcpy(&tree.voxelTreeHeader->boundMax, volume.bound_max, sizeof(float[4]));

					tree.voxelTopDownViewNodeArray = allocator.allocate<IW7::GfxVoxelTopDownViewNode>(
						tree.voxelTopDownViewNodeCount);
					memcpy(tree.voxelTopDownViewNodeArray, volume.top_down_view_nodes.data(),
						sizeof(IW7::GfxVoxelTopDownViewNode) * tree.voxelTopDownViewNodeCount);
					tree.voxelInternalNodeArray = allocator.allocate<IW7::GfxVoxelInternalNode>(
						tree.voxelInternalNodeCount);
					memcpy(tree.voxelInternalNodeArray, volume.internal_nodes.data(),
						sizeof(IW7::GfxVoxelInternalNode) * tree.voxelInternalNodeCount);
					tree.voxelLeafNodeArray = allocator.allocate<IW7::GfxVoxelLeafNode>(tree.voxelLeafNodeCount);
					memcpy(tree.voxelLeafNodeArray, leaf_addresses.data(),
						sizeof(unsigned short) * leaf_addresses.size());
					tree.lightListArray = allocator.allocate<unsigned short>(tree.lightListArraySize);
					memcpy(tree.lightListArray, light_list.data(),
						sizeof(unsigned short) * light_list.size());
					tree.voxelInternalNodeDynamicLightList =
						allocator.allocate<unsigned int>(2 * tree.voxelInternalNodeCount); // runtime
				}

				if (volume.valid)
				{
					memcpy(zone.fallbackProbeData.coeffs, volume.zone_fallback_coeffs,
						sizeof(zone.fallbackProbeData.coeffs));
				}
				else
				{
					ZONETOOL_WARNING("GfxWorld \"%s\": light grid probe volume could not be built; "
						"falling back to a flat ambient probe", asset->name);

					float fallback_sh[28] = {};
					lightgrid_probes::constant_sh(ambient, sh_ambient_scale, fallback_sh);
					fallback_sh[27] = 1.0f;
					unsigned short fallback[32];
					lightgrid_probes::encode_probe_sh(fallback_sh, fallback);
					memcpy(zone.fallbackProbeData.coeffs, fallback,
						sizeof(zone.fallbackProbeData.coeffs));
				}
				memset(zone.fallbackProbeData.pad, 0, sizeof(zone.fallbackProbeData.pad));

				constexpr bool debug_probe_paint = false;
				if (debug_probe_paint)
				{
					constexpr float paint_level = 0.35f;
					const float magenta[3] = { paint_level, 0.0f, paint_level };
					const float green[3] = { 0.0f, paint_level, 0.0f };

					float sh[27];
					unsigned short coeffs[32];

					lightgrid_probes::constant_sh(magenta, sh_ambient_scale, sh);
					lightgrid_probes::encode_probe_sh(sh, coeffs);
					memcpy(zone.fallbackProbeData.coeffs, coeffs,
						sizeof(zone.fallbackProbeData.coeffs));

					if (new_asset->lightGrid.probeData.gpuVisibleProbesData
						&& new_asset->lightGrid.probeData.gpuVisibleProbesCount)
					{
						lightgrid_probes::constant_sh(green, sh_ambient_scale, sh);
						lightgrid_probes::encode_probe_sh(sh, coeffs);
						memcpy(&new_asset->lightGrid.probeData.gpuVisibleProbesData[0], coeffs,
							sizeof(coeffs));
					}
				}
			}

			new_asset->frustumLights = allocator.allocate<IW7::GfxFrustumLights>(new_asset->primaryLightCount);

			new_asset->lightViewFrustums = allocator.allocate<IW7::GfxLightViewFrustum>(new_asset->primaryLightCount);

			//
			//
			//
			{
				constexpr auto light_view_frustum_near_frac = 0.01f;

				const auto count = converter_com_world
					? std::min<unsigned int>(new_asset->primaryLightCount,
						converter_com_world->primaryLightCount)
					: 0u;

				unsigned int built = 0;
				for (unsigned int i = 0; i < count; i++)
				{
					const auto& src = converter_com_world->primaryLights[i];

					if (static_cast<unsigned char>(src.type) != light_type_spot
						|| !src.canUseShadowMap
						|| !(src.radius > 0.0f)
						|| !(src.cosHalfFovOuter > 0.0f && src.cosHalfFovOuter < 1.0f))
					{
						continue;
					}

					float axis[3] = { -src.dir[0], -src.dir[1], -src.dir[2] };
					const auto axis_len = std::sqrt((axis[0] * axis[0]) + (axis[1] * axis[1])
						+ (axis[2] * axis[2]));
					if (!(axis_len > 1e-4f))
					{
						continue;
					}
					for (int k = 0; k < 3; k++)
					{
						axis[k] /= axis_len;
					}

					const auto axial = std::abs(axis[2]) > 0.9f;
					const float helper[3] = { axial ? 1.0f : 0.0f, 0.0f, axial ? 0.0f : 1.0f };
					const auto helper_dot = (helper[0] * axis[0]) + (helper[1] * axis[1])
						+ (helper[2] * axis[2]);

					float right[3];
					for (int k = 0; k < 3; k++)
					{
						right[k] = helper[k] - (axis[k] * helper_dot);
					}
					const auto right_len = std::sqrt((right[0] * right[0]) + (right[1] * right[1])
						+ (right[2] * right[2]));
					if (!(right_len > 1e-4f))
					{
						continue;
					}
					for (int k = 0; k < 3; k++)
					{
						right[k] /= right_len;
					}

					const float up[3] = {
						(axis[1] * right[2]) - (axis[2] * right[1]),
						(axis[2] * right[0]) - (axis[0] * right[2]),
						(axis[0] * right[1]) - (axis[1] * right[0]),
					};

					const auto cos_outer = std::max(0.017452f, src.cosHalfFovOuter);
					const auto tan_half = std::sqrt(std::max(0.0f,
						1.0f - (cos_outer * cos_outer))) / cos_outer;

					const auto near_dist = std::max(1.0f, src.radius * light_view_frustum_near_frac);
					const auto far_dist = std::max(near_dist + 1.0f, src.radius);

					float verts[8][3];
					for (int slice = 0; slice < 2; slice++)
					{
						const auto depth = slice ? far_dist : near_dist;
						const auto extent = depth * tan_half;
						for (int corner = 0; corner < 4; corner++)
						{
							const auto sx = (corner == 0 || corner == 3) ? -extent : extent;
							const auto sy = (corner < 2) ? -extent : extent;
							for (int k = 0; k < 3; k++)
							{
								verts[(slice * 4) + corner][k] = src.origin[k] + (axis[k] * depth)
									+ (right[k] * sx) + (up[k] * sy);
							}
						}
					}

					static const unsigned short quads[6][4] = {
						{ 0, 1, 2, 3 },
						{ 4, 5, 6, 7 },
						{ 0, 1, 5, 4 },
						{ 1, 2, 6, 5 },
						{ 2, 3, 7, 6 },
						{ 3, 0, 4, 7 },
					};

					std::vector<unsigned short> indices;
					indices.reserve(36);
					for (const auto& quad : quads)
					{
						indices.push_back(quad[0]);
						indices.push_back(quad[1]);
						indices.push_back(quad[2]);
						indices.push_back(quad[0]);
						indices.push_back(quad[2]);
						indices.push_back(quad[3]);
					}

					auto signed_volume = 0.0f;
					for (size_t t = 0; t + 2 < indices.size(); t += 3)
					{
						const auto* a = verts[indices[t]];
						const auto* b = verts[indices[t + 1]];
						const auto* c = verts[indices[t + 2]];
						signed_volume += (a[0] * ((b[1] * c[2]) - (b[2] * c[1])))
							- (a[1] * ((b[0] * c[2]) - (b[2] * c[0])))
							+ (a[2] * ((b[0] * c[1]) - (b[1] * c[0])));
					}
					if (signed_volume < 0.0f)
					{
						for (size_t t = 0; t + 2 < indices.size(); t += 3)
						{
							std::swap(indices[t + 1], indices[t + 2]);
						}
					}

					float centre[3] = { 0.0f, 0.0f, 0.0f };
					for (const auto& vertex : verts)
					{
						for (int k = 0; k < 3; k++)
						{
							centre[k] += vertex[k] * 0.125f;
						}
					}

					auto& dest = new_asset->lightViewFrustums[i];
					dest.vertexCount = 8;
					dest.vertices = allocator.allocate<IW7::vec3_t>(8);
					memcpy(dest.vertices, verts, sizeof(verts));

					dest.indexCount = static_cast<unsigned int>(indices.size());
					dest.indices = allocator.allocate<unsigned short>(indices.size());
					memcpy(dest.indices, indices.data(),
						sizeof(unsigned short) * indices.size());

					dest.planeCount = 6;
					dest.planes = allocator.allocate<IW7::vec4_t>(6);
					for (int f = 0; f < 6; f++)
					{
						const auto* a = verts[quads[f][0]];
						const auto* b = verts[quads[f][1]];
						const auto* c = verts[quads[f][2]];

						const float ab[3] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
						const float ac[3] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };
						float normal[3] = {
							(ab[1] * ac[2]) - (ab[2] * ac[1]),
							(ab[2] * ac[0]) - (ab[0] * ac[2]),
							(ab[0] * ac[1]) - (ab[1] * ac[0]),
						};
						const auto len = std::sqrt((normal[0] * normal[0])
							+ (normal[1] * normal[1]) + (normal[2] * normal[2]));
						if (!(len > 1e-8f))
						{
							continue;
						}
						for (int k = 0; k < 3; k++)
						{
							normal[k] /= len;
						}

						auto dist = -((normal[0] * a[0]) + (normal[1] * a[1]) + (normal[2] * a[2]));

						if (((normal[0] * centre[0]) + (normal[1] * centre[1])
							+ (normal[2] * centre[2])) + dist < 0.0f)
						{
							for (int k = 0; k < 3; k++)
							{
								normal[k] = -normal[k];
							}
							dist = -dist;
						}

						dest.planes[f][0] = normal[0];
						dest.planes[f][1] = normal[1];
						dest.planes[f][2] = normal[2];
						dest.planes[f][3] = dist;
					}

					built++;
				}

				ZONETOOL_INFO("GfxWorld \"%s\": %u light view frustums over %u primary lights",
					asset->name, built, new_asset->primaryLightCount);
			}

			{
				struct proxy_light
				{
					unsigned char type;
					float origin[3];
					float dir[3];
					float radius;
					float cos_half_fov_outer;
				};

				std::vector<proxy_light> lights;
				if (converter_com_world)
				{
					const auto count = std::min<unsigned int>(new_asset->primaryLightCount,
						converter_com_world->primaryLightCount);
					lights.reserve(count);
					for (unsigned int i = 0; i < count; i++)
					{
						const auto& src = converter_com_world->primaryLights[i];
						proxy_light light{};
						light.type = static_cast<unsigned char>(src.type);
						memcpy(light.origin, src.origin, sizeof(light.origin));
						memcpy(light.dir, src.dir, sizeof(light.dir));
						light.radius = src.radius;
						light.cos_half_fov_outer = src.cosHalfFovOuter;
						lights.push_back(light);
					}
				}
				else
				{
					ZONETOOL_WARNING("GfxWorld \"%s\": no ComWorld found, local lights will have no "
						"frustum proxy and may not be binned", asset->name);
				}

				{
					const auto light_count = static_cast<unsigned int>(lights.size());
					unsigned int proxy_count = 0;
					unsigned int clipped_count = 0;

					for (unsigned int i = 0; i < light_count; i++)
					{
						const auto& light = lights[i];
						if (light.radius <= 0.0f)
						{
							continue;
						}

						float axis[3] = { -light.dir[0], -light.dir[1], -light.dir[2] };
						normalize_proxy_axis(axis);

						proxy_mesh mesh{};
						const auto cos_outer = std::max(-1.0f, std::min(1.0f, light.cos_half_fov_outer));
						const auto half_angle = std::acos(cos_outer);

						if (light.type != light_type_spot && light.type != light_type_omni)
						{
							continue;
						}

						if (light_proxy_use_sphere)
						{
							build_omni_proxy(mesh, light.origin, light.radius * light_proxy_sphere_scale);
						}
						else if (light.type == light_type_spot && half_angle < light_proxy_wide_spot_cutoff)
						{
							build_spot_proxy(mesh, light.origin, axis, half_angle, light.radius);
						}
						else
						{
							build_omni_proxy(mesh, light.origin, light.radius);
						}
						//
						//
						//
						{
							const auto found = light_boxes.find(i);
							if (found != light_boxes.end() && found->second.cells)
							{
								const auto& box = found->second;
								//
								constexpr float cell_margin[3] = { 32.0f, 32.0f, 64.0f };

								for (size_t v = 0; v + 2 < mesh.vertices.size(); v += 3)
								{
									for (int k = 0; k < 3; k++)
									{
										mesh.vertices[v + k] = std::max(box.lo[k] - cell_margin[k],
											std::min(box.hi[k] + cell_margin[k], mesh.vertices[v + k]));
									}
								}
								clipped_count++;
							}
							else if (light.type == light_type_spot || light.type == light_type_omni)
							{
								ZONETOOL_WARNING("GfxWorld \"%s\": light %u has no light grid cells, "
									"so its proxy hull is unclipped and may light through walls",
									asset->name, i);
							}
						}

						auto& dest = new_asset->frustumLights[i];

						dest.vertexCount = static_cast<unsigned int>(mesh.vertices.size() / 3);
						dest.vertices = allocator.allocate<char>(32 * dest.vertexCount);
						for (unsigned int v = 0; v < dest.vertexCount; v++)
						{
							memcpy(&dest.vertices[32 * v], &mesh.vertices[3ull * v], sizeof(float[3]));
						}

						dest.indexCount = static_cast<unsigned int>(mesh.indices.size());
						dest.indices = allocator.allocate<unsigned short>(dest.indexCount);
						memcpy(dest.indices, mesh.indices.data(), sizeof(unsigned short) * dest.indexCount);
						proxy_count++;
					}

					ZONETOOL_INFO("GfxWorld \"%s\": %u frustum light proxies over %u primary lights, "
						"%u clipped to their light grid cells",
						asset->name, proxy_count, new_asset->primaryLightCount, clipped_count);
				}
			}

			if (!new_asset->voxelTree)
			{
				new_asset->voxelTreeCount = new_asset->skyCount;
				new_asset->voxelTree = allocator.allocate<IW7::GfxVoxelTree>(new_asset->voxelTreeCount);
				for (auto i = 0; i < new_asset->skyCount; i++)
				{
					//
					//
					//
					//
					const auto get_sky_bounds = [](const GfxSky& sky, const GfxWorld* world) -> Bounds
					{
						float lo[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
						float hi[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
						unsigned int seen = 0;

						for (int j = 0; j < sky.skySurfCount; j++)
						{
							const auto sorted = sky.skyStartSurfs[j];
							if (sorted < 0 || static_cast<unsigned int>(sorted) >= world->dpvs.staticSurfaceCount)
							{
								continue;
							}
							const auto index = world->dpvs.sortedSurfIndex[sorted];
							if (index >= world->surfaceCount)
							{
								continue;
							}
							const auto& b = world->dpvs.surfacesBounds[index].bounds;
							for (int k = 0; k < 3; k++)
							{
								lo[k] = std::min(lo[k], b.midPoint[k] - b.halfSize[k]);
								hi[k] = std::max(hi[k], b.midPoint[k] + b.halfSize[k]);
							}
							seen++;
						}

						Bounds bounds{};
						if (!seen)
						{
							return bounds;
						}
						for (int k = 0; k < 3; k++)
						{
							bounds.midPoint[k] = (lo[k] + hi[k]) * 0.5f;
							bounds.halfSize[k] = (hi[k] - lo[k]) * 0.5f;
						}
						return bounds;
					};

					auto sky_bounds = get_sky_bounds(asset->skies[i], asset);
					memcpy(&new_asset->voxelTree[i].zoneBound, &sky_bounds, sizeof(Bounds));

					new_asset->voxelTree[i].voxelTopDownViewNodeCount = 1;
					new_asset->voxelTree[i].voxelInternalNodeCount = 1;
					new_asset->voxelTree[i].voxelLeafNodeCount = 1;
					new_asset->voxelTree[i].lightListArraySize = 1;

					new_asset->voxelTree[i].voxelTreeHeader = allocator.allocate<IW7::GfxVoxelTreeHeader>();
					memset(&new_asset->voxelTree[i].voxelTreeHeader->rootNodeDimension, 0, sizeof(int[4]));
					memset(&new_asset->voxelTree[i].voxelTreeHeader->nodeCoordBitShift, 0, sizeof(int[4]));
					memset(&new_asset->voxelTree[i].voxelTreeHeader->boundMin, 0, sizeof(float[4]));
					memset(&new_asset->voxelTree[i].voxelTreeHeader->boundMax, 0, sizeof(float[4]));

					new_asset->voxelTree[i].voxelTopDownViewNodeArray = allocator.allocate<IW7::GfxVoxelTopDownViewNode>(new_asset->voxelTree[i].voxelTopDownViewNodeCount);
					new_asset->voxelTree[i].voxelTopDownViewNodeArray->firstNodeIndex = -1;
					new_asset->voxelTree[i].voxelTopDownViewNodeArray->zMin = 2147483647;
					new_asset->voxelTree[i].voxelTopDownViewNodeArray->zMax = -2147483648;

					new_asset->voxelTree[i].voxelInternalNodeArray = allocator.allocate<IW7::GfxVoxelInternalNode>(new_asset->voxelTree[i].voxelInternalNodeCount);
					new_asset->voxelTree[i].voxelInternalNodeArray->firstNodeIndex[0] = 0;
					new_asset->voxelTree[i].voxelInternalNodeArray->firstNodeIndex[1] = 0;
					new_asset->voxelTree[i].voxelInternalNodeArray->childNodeMask[0] = 0;
					new_asset->voxelTree[i].voxelInternalNodeArray->childNodeMask[1] = 0;

					new_asset->voxelTree[i].voxelLeafNodeArray = allocator.allocate<IW7::GfxVoxelLeafNode>(new_asset->voxelTree[i].voxelLeafNodeCount);
					new_asset->voxelTree[i].voxelLeafNodeArray->lightListAddress = 0;

					new_asset->voxelTree[i].lightListArray = allocator.allocate<unsigned short>(new_asset->voxelTree[i].lightListArraySize);
					new_asset->voxelTree[i].lightListArray[0] = 0;

					new_asset->voxelTree[i].voxelInternalNodeDynamicLightList = allocator.allocate<unsigned int>(2 * new_asset->voxelTree[i].voxelInternalNodeCount);
					new_asset->voxelTree[i].voxelInternalNodeDynamicLightList[0] = 0;
					new_asset->voxelTree[i].voxelInternalNodeDynamicLightList[1] = 0;
				}
			}

			// todo...
			new_asset->heightfieldCount = 0;
			new_asset->heightfields = nullptr;

			if (!new_asset->lightLists.lists)
			{
				new_asset->lightLists.surfaceListOffsetCount = 0;
				new_asset->lightLists.surfaceListOffsets = nullptr;
				new_asset->lightLists.smodelListOffsetCount = 0;
				new_asset->lightLists.smodelListOffsets = nullptr;
				new_asset->lightLists.listsSize = 0;
				ZONETOOL_WARNING("GfxWorld \"%s\": no per-surface light lists", asset->name);
			}

			COPY_VALUE(modelCount);
			new_asset->models = allocator.allocate<IW7::GfxBrushModel>(asset->modelCount);
			for (int i = 0; i < asset->modelCount; i++)
			{
				COPY_ARR(models[i].bounds);
				COPY_VALUE(models[i].radius);
				COPY_VALUE_CAST(models[i].startSurfIndex);
				COPY_VALUE(models[i].surfaceCount);
			}

			std::memcpy(&new_asset->bounds, &asset->bounds, sizeof(Bounds));
			
			COPY_VALUE(checksum);

			COPY_VALUE(materialMemoryCount);
			new_asset->materialMemory = allocator.allocate<IW7::MaterialMemory>(new_asset->materialMemoryCount);
			for (int i = 0; i < new_asset->materialMemoryCount; i++)
			{
				new_asset->materialMemory[i].material = reinterpret_cast<IW7::Material PTR64>(asset->materialMemory[i].material);
				new_asset->materialMemory[i].memory = asset->materialMemory[i].memory;
			}

			COPY_VALUE(sun.hasValidData);
			COPY_ASSET(sun.spriteMaterial);
			COPY_ASSET(sun.flareMaterial);
			COPY_VALUE(sun.spriteSize);
			COPY_VALUE(sun.flareMinSize);
			COPY_VALUE(sun.flareMinDot);
			COPY_VALUE(sun.flareMaxSize);
			COPY_VALUE(sun.flareMaxDot);
			COPY_VALUE(sun.flareMaxAlpha);
			COPY_VALUE(sun.flareFadeInTime);
			COPY_VALUE(sun.flareFadeOutTime);
			COPY_VALUE(sun.blindMinDot);
			COPY_VALUE(sun.blindMaxDot);
			COPY_VALUE(sun.blindMaxDarken);
			COPY_VALUE(sun.blindFadeInTime);
			COPY_VALUE(sun.blindFadeOutTime);
			COPY_VALUE(sun.glareMinDot);
			COPY_VALUE(sun.glareMaxDot);
			COPY_VALUE(sun.glareMaxLighten);
			COPY_VALUE(sun.glareFadeInTime);
			COPY_VALUE(sun.glareFadeOutTime);
			COPY_ARR(sun.sunFxPosition);

			COPY_ARR(outdoorLookupMatrix);
			COPY_ASSET(outdoorImage);
			new_asset->dustMaterial = nullptr;
			new_asset->materialLod0SizeThreshold = 0.5f;

			//
			//
			//
			{
				ZONETOOL_INFO("GfxWorld \"%s\": lastSunPrimaryLightIndex=%u, source shadowGeom=%s",
					asset->name, new_asset->lastSunPrimaryLightIndex,
					asset->shadowGeom ? "present" : "NULL");

				new_asset->shadowGeomOptimized =
					allocator.allocate<IW7::GfxShadowGeometry>(new_asset->primaryLightCount);

				const auto light_count = converter_com_world
					? std::min<unsigned int>(new_asset->primaryLightCount,
						converter_com_world->primaryLightCount)
					: 0u;

				std::vector<unsigned int> caster_surfaces;
				std::vector<unsigned short> caster_smodels;

				for (unsigned int i = 0; i < light_count; i++)
				{
					if (i <= new_asset->lastSunPrimaryLightIndex)
					{
						continue;
					}

					const auto& light = converter_com_world->primaryLights[i];
					const auto type = static_cast<unsigned char>(light.type);
					if (type != light_type_spot && type != light_type_omni)
					{
						continue;
					}
					if (!(light.radius > 0.0f))
					{
						continue;
					}

					float axis[3] = { -light.dir[0], -light.dir[1], -light.dir[2] };
					const auto axis_len = std::sqrt((axis[0] * axis[0]) + (axis[1] * axis[1])
						+ (axis[2] * axis[2]));
					const auto is_spot = (type == light_type_spot) && (axis_len > 0.0f);
					if (axis_len > 0.0f)
					{
						for (int k = 0; k < 3; k++)
						{
							axis[k] /= axis_len;
						}
					}
					const auto half_fov = std::acos(std::max(-1.0f,
						std::min(1.0f, light.cosHalfFovOuter)));

					const auto reaches = [&](const Bounds& bounds)
					{
						const auto radius = std::sqrt(
							(bounds.halfSize[0] * bounds.halfSize[0])
							+ (bounds.halfSize[1] * bounds.halfSize[1])
							+ (bounds.halfSize[2] * bounds.halfSize[2]));

						const float delta[3] = {
							bounds.midPoint[0] - light.origin[0],
							bounds.midPoint[1] - light.origin[1],
							bounds.midPoint[2] - light.origin[2],
						};
						const auto dist = std::sqrt((delta[0] * delta[0]) + (delta[1] * delta[1])
							+ (delta[2] * delta[2]));

						if (dist - radius > light.radius)
						{
							return false;
						}

						if (is_spot && dist > 0.001f)
						{
							const auto dot = ((delta[0] * axis[0]) + (delta[1] * axis[1])
								+ (delta[2] * axis[2])) / dist;
							const auto theta = std::acos(std::max(-1.0f, std::min(1.0f, dot)));
							const auto slack = std::asin(std::min(1.0f, radius / dist));
							if (theta > half_fov + slack)
							{
								return false;
							}
						}
						return true;
					};

					caster_surfaces.clear();
					caster_smodels.clear();

					if (asset->dpvs.surfacesBounds)
					{
						for (unsigned int sf = 0; sf < asset->surfaceCount; sf++)
						{
							if (reaches(asset->dpvs.surfacesBounds[sf].bounds))
							{
								caster_surfaces.push_back(sf);
							}
						}
					}

					if (asset->dpvs.smodelInsts)
					{
						for (unsigned int sm = 0; sm < asset->dpvs.smodelCount && sm <= 0xFFFF; sm++)
						{
							if (reaches(asset->dpvs.smodelInsts[sm].bounds))
							{
								caster_smodels.push_back(static_cast<unsigned short>(sm));
							}
						}
					}

					if (caster_surfaces.size() > 0xFFFF)
					{
						caster_surfaces.resize(0xFFFF);
					}
					if (caster_smodels.size() > 0xFFFF)
					{
						caster_smodels.resize(0xFFFF);
					}

					auto& dest = new_asset->shadowGeomOptimized[i];
					dest.surfaceCount = static_cast<unsigned short>(caster_surfaces.size());
					dest.smodelCount = static_cast<unsigned short>(caster_smodels.size());

					if (dest.surfaceCount)
					{
						dest.sortedSurfIndex = allocator.allocate<unsigned int>(dest.surfaceCount);
						memcpy(dest.sortedSurfIndex, caster_surfaces.data(),
							sizeof(unsigned int) * dest.surfaceCount);
					}
					if (dest.smodelCount)
					{
						dest.smodelIndex = allocator.allocate<unsigned short>(dest.smodelCount);
						memcpy(dest.smodelIndex, caster_smodels.data(),
							sizeof(unsigned short) * dest.smodelCount);
					}

					ZONETOOL_INFO("GfxWorld \"%s\": light %u shadow casters - %u surfaces, %u "
						"smodels (was %u / %u from the source)", asset->name, i,
						dest.surfaceCount, dest.smodelCount,
						asset->shadowGeom && i < asset->primaryLightCount
							? asset->shadowGeom[i].surfaceCount : 0,
						asset->shadowGeom && i < asset->primaryLightCount
							? asset->shadowGeom[i].smodelCount : 0);
				}
			}

			new_asset->lightRegion = allocator.allocate<IW7::GfxLightRegion>(new_asset->primaryLightCount);
			for (unsigned int i = 0; i < new_asset->primaryLightCount; i++)
			{
				const auto region_source = i;

				if (region_source >= asset->primaryLightCount)
				{
					new_asset->lightRegion[i].hullCount = 0;
					new_asset->lightRegion[i].hulls = nullptr;
					continue;
				}

				const auto& src_region = asset->lightRegion[region_source];
				new_asset->lightRegion[i].hullCount = src_region.hullCount;
				new_asset->lightRegion[i].hulls = allocator.allocate<IW7::GfxLightRegionHull>(new_asset->lightRegion[i].hullCount);
				for (unsigned int j = 0; j < new_asset->lightRegion[i].hullCount; j++)
				{
					memcpy(&new_asset->lightRegion[i].hulls[j].kdopMidPoint, &src_region.hulls[j].kdopMidPoint, sizeof(float[9]));
					memcpy(&new_asset->lightRegion[i].hulls[j].kdopHalfSize, &src_region.hulls[j].kdopHalfSize, sizeof(float[9]));

					new_asset->lightRegion[i].hulls[j].axisCount = src_region.hulls[j].axisCount;
					REINTERPRET_CAST_SAFE_TO_FROM(new_asset->lightRegion[i].hulls[j].axis, src_region.hulls[j].axis);
				}
			}

			// todo?...
			new_asset->lightAABB.nodeCount = 0;
			new_asset->lightAABB.lightCount = 0;
			new_asset->lightAABB.nodeArray = nullptr;
			new_asset->lightAABB.lightArray = nullptr;

			// dpvs
			{
				COPY_VALUE(dpvs.smodelCount);
				COPY_VALUE(dpvs.staticSurfaceCount);
				COPY_VALUE(dpvs.litOpaqueSurfsBegin);
				COPY_VALUE(dpvs.litOpaqueSurfsEnd);
				new_asset->dpvs.litDecalSurfsBegin = new_asset->dpvs.litOpaqueSurfsEnd; // skip
				new_asset->dpvs.litDecalSurfsEnd = new_asset->dpvs.litOpaqueSurfsEnd; // skip
				COPY_VALUE(dpvs.litTransSurfsBegin);
				COPY_VALUE(dpvs.litTransSurfsEnd);
				COPY_VALUE(dpvs.emissiveSurfsBegin);
				COPY_VALUE(dpvs.emissiveSurfsEnd);
				new_asset->dpvs.smodelVisDataCount = (new_asset->dpvs.smodelCount + 0x1F) >> 5;
				new_asset->dpvs.surfaceVisDataCount = (new_asset->surfaceCount + 0x1F) >> 5;
				new_asset->dpvs.primaryLightVisDataCount = (new_asset->primaryLightCount + 0x1F) >> 5;
				new_asset->dpvs.reflectionProbeVisDataCount = (new_asset->draw.reflectionProbeData.reflectionProbeInstanceCount + 0x1F) >> 5;
				new_asset->dpvs.volumetricVisDataCount = (new_asset->draw.volumetrics.volumetricCount + 0x1F) >> 5;
				new_asset->dpvs.decalVisDataCount = (new_asset->draw.decalVolumeCollectionCount + 0x1F) >> 5;
				new_asset->dpvs.lodData = allocator.allocate<unsigned int>(new_asset->dpvs.smodelCount + 1);
				for (unsigned int i = 0; i < new_asset->dpvs.smodelCount; i++)
				{
					new_asset->dpvs.lodData[i + 1] = i;
				}
				new_asset->dpvs.sortedSurfIndex = allocator.allocate<unsigned int>(new_asset->dpvs.staticSurfaceCount);
				for (unsigned int i = 0; i < new_asset->dpvs.staticSurfaceCount; i++)
				{
					new_asset->dpvs.sortedSurfIndex[i] = asset->dpvs.sortedSurfIndex[i];
				}
				REINTERPRET_CAST_SAFE(dpvs.smodelInsts);

				//
				//
				//
				//
				const auto sun_light_count =
					std::min<unsigned int>(new_asset->lastSunPrimaryLightIndex, 5);
				const auto sun_light_mask = static_cast<unsigned char>((1 << sun_light_count) - 1);

				new_asset->dpvs.surfaces = allocator.allocate<IW7::GfxSurface>(asset->surfaceCount);
				for (unsigned int i = 0; i < asset->surfaceCount; i++)
				{
					COPY_VALUE(dpvs.surfaces[i].tris.vertexLayerData);
					COPY_VALUE(dpvs.surfaces[i].tris.firstVertex);
					new_asset->dpvs.surfaces[i].tris.maxEdgeLength = 0;
					COPY_VALUE(dpvs.surfaces[i].tris.vertexCount);
					COPY_VALUE(dpvs.surfaces[i].tris.triCount);
					COPY_VALUE(dpvs.surfaces[i].tris.baseIndex);
					new_asset->dpvs.surfaces[i].material = reinterpret_cast<IW7::Material PTR64>(asset->dpvs.surfaces[i].material);
					new_asset->dpvs.surfaces[i].lightmapIndex = asset->dpvs.surfaces[i].laf.fields.lightmapIndex;

					const auto casts_sun_shadow = (asset->dpvs.surfaces[i].laf.fields.flags & 1) != 0;
					new_asset->dpvs.surfaces[i].flags = casts_sun_shadow
						? static_cast<unsigned char>(1 | (sun_light_mask << 3))
						: 0;

					new_asset->dpvs.surfaces[i].unk1 = 0;
					new_asset->dpvs.surfaces[i].unk2 = 0;
					new_asset->dpvs.surfaces[i].unk3 = 0;
					new_asset->dpvs.surfaces[i].unk4 = 0;

					new_asset->dpvs.surfaces[i].transientZone = 0;
				}

				new_asset->dpvs.surfacesBounds = allocator.allocate<IW7::GfxSurfaceBounds>(asset->surfaceCount);
				for (unsigned int i = 0; i < asset->surfaceCount; i++)
				{
					COPY_ARR(dpvs.surfacesBounds[i].bounds);
				}

				new_asset->dpvs.smodelDrawInsts = allocator.allocate<IW7::GfxStaticModelDrawInst>(asset->dpvs.smodelCount);
				for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
				{
					COPY_ARR(dpvs.smodelDrawInsts[i].placement);

					new_asset->dpvs.smodelDrawInsts[i].model =
						reinterpret_cast<IW7::XModel PTR64>(asset->dpvs.smodelDrawInsts[i].model);

					auto& src_draw_inst = asset->dpvs.smodelDrawInsts[i];

					new_asset->dpvs.smodelDrawInsts[i].modelLightmapInfo.lightmapIndex = -1;

					new_asset->dpvs.smodelDrawInsts[i].lightingHandle = asset->dpvs.smodelDrawInsts[i].lightingHandle;
					new_asset->dpvs.smodelDrawInsts[i].cullDist = asset->dpvs.smodelDrawInsts[i].cullDist;
					new_asset->dpvs.smodelDrawInsts[i].flags = asset->dpvs.smodelDrawInsts[i].flags;
					//
					//
					new_asset->dpvs.smodelDrawInsts[i].primaryLightEnvIndex = 0;
					new_asset->dpvs.smodelDrawInsts[i].reflectionProbeIndex = 0;
					new_asset->dpvs.smodelDrawInsts[i].firstMtlSkinIndex = asset->dpvs.smodelDrawInsts[i].firstMtlSkinIndex;
					//
					//
					new_asset->dpvs.smodelDrawInsts[i].sunShadowFlags = sun_light_mask;
					new_asset->dpvs.smodelDrawInsts[i].transientZone = 0;

					const auto probe_slice_first = i * smodel_probe_samples;
					new_asset->dpvs.smodelDrawInsts[i].unk0 =
						static_cast<unsigned short>(probe_slice_first & 0xFFFF);
					new_asset->dpvs.smodelDrawInsts[i].unk1 =
						static_cast<unsigned short>(probe_slice_first >> 16);
					new_asset->dpvs.smodelDrawInsts[i].unk2 = 0;
					new_asset->dpvs.smodelDrawInsts[i].unk3 =
						static_cast<unsigned short>(smodel_probe_samples);

					auto& iw7_draw_inst = new_asset->dpvs.smodelDrawInsts[i];
					auto& draw_inst = asset->dpvs.smodelDrawInsts[i];

					// g_lodDistIndexToScale
					iw7_draw_inst.flags |= IW7::StaticModelFlag::STATIC_MODEL_FLAG_SCALE_9; // 1.0f

					// casts no shadows
					auto no_shadows = (draw_inst.flags & 0x10) != 0;
					if (no_shadows)
					{
						iw7_draw_inst.flags |= IW7::StaticModelFlag::STATIC_MODEL_FLAG_NO_CAST_SHADOW;
					}

					// ground lighting
					auto ground_lighting = (draw_inst.flags & 0x20) != 0;
					if (ground_lighting)
					{
						iw7_draw_inst.flags |= IW7::StaticModelFlag::STATIC_MODEL_FLAG_GROUND_LIGHTING;
					}

					// regular lighting
					iw7_draw_inst.flags |= IW7::StaticModelFlag::STATIC_MODEL_FLAG_LIGHTGRID_LIGHTING;
				}

				new_asset->dpvs.surfaceMaterials = allocator.allocate<IW7::GfxDrawSurf>(new_asset->surfaceCount);
				memset(new_asset->dpvs.surfaceMaterials, 0, 
					sizeof(IW7::GfxDrawSurf) * new_asset->surfaceCount); // zero data, runtime

				//
				//
				//
				new_asset->dpvs.sunShadowOptCount =
					std::min<unsigned int>(new_asset->lastSunPrimaryLightIndex, 5);
				new_asset->dpvs.sunSurfVisDataCount =
					(new_asset->dpvs.surfaceVisDataCount + 31) & ~31u;//
				new_asset->dpvs.surfaceCastsSunShadowOpt = nullptr;
				new_asset->dpvs.surfaceCastsSunShadow = asset->dpvs.surfaceCastsSunShadow;

				new_asset->dpvs.sortedSmodelIndices = allocator.allocate<unsigned short>(asset->dpvs.smodelCount);
				for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
				{
					new_asset->dpvs.sortedSmodelIndices[i] = static_cast<unsigned short>(i);
				}

				// todo...
				new_asset->dpvs.constantBuffers = nullptr;

				COPY_VALUE(dpvs.usageCount);
			}

			COPY_ARR(dpvsDyn.dynEntClientWordCount);
			COPY_ARR(dpvsDyn.dynEntClientCount);

			{
				new_asset->dpvsDyn.dynEntClientCount[0] += 64; // reserve_dynents
				new_asset->dpvsDyn.dynEntClientWordCount[0] += 2; // reserve_dynents ( 64 >> 5 )

				new_asset->dpvsDyn.dynEntCellBits[0] = allocator.allocate<unsigned int>(new_asset->dpvsDyn.dynEntClientCount[0] * new_asset->dpvsPlanes.cellCount); // runtime
				new_asset->dpvsDyn.dynEntCellBits[1] = allocator.allocate<unsigned int>(new_asset->dpvsDyn.dynEntClientCount[1] * new_asset->dpvsPlanes.cellCount); // runtime

				// 0 - 3 are valid.
				new_asset->dpvsDyn.dynEntVisData[0][0] = allocator.allocate<unsigned char>(32 * new_asset->dpvsDyn.dynEntClientWordCount[0]); // runtime
				new_asset->dpvsDyn.dynEntVisData[0][1] = allocator.allocate<unsigned char>(32 * new_asset->dpvsDyn.dynEntClientWordCount[0]); // runtime
				new_asset->dpvsDyn.dynEntVisData[0][2] = allocator.allocate<unsigned char>(32 * new_asset->dpvsDyn.dynEntClientWordCount[0]); // runtime

				new_asset->dpvsDyn.dynEntVisData[1][0] = allocator.allocate<unsigned char>(32 * new_asset->dpvsDyn.dynEntClientWordCount[1]); // runtime
				new_asset->dpvsDyn.dynEntVisData[1][1] = allocator.allocate<unsigned char>(32 * new_asset->dpvsDyn.dynEntClientWordCount[1]); // runtime
				new_asset->dpvsDyn.dynEntVisData[1][2] = allocator.allocate<unsigned char>(32 * new_asset->dpvsDyn.dynEntClientWordCount[1]); // runtime
			}

			COPY_VALUE(mapVtxChecksum);
			COPY_VALUE(heroOnlyLightCount);
			REINTERPRET_CAST_SAFE(heroOnlyLights);

			generate_umbra_tome(asset, new_asset, allocator);

			// the second tome is the gate tome, and gates are a T7/IW7 authoring concept
			// with no IW5 equivalent. It is only consulted by the gate-state queries, not
			// by the static visibility path that decides what gets drawn, so a converted
			// map does not need one.
			new_asset->numUmbraGates2 = 0;
			new_asset->umbraGates2 = nullptr;
			new_asset->umbraTomeSize2 = 0;
			new_asset->umbraTomeData2 = nullptr;
			new_asset->umbraTomePtr2 = nullptr;

			// 4 bytes holding a float (2400.0 in shipped maps). Consumer not identified,
			// and shipped content is happy to have none of it.
			new_asset->umbraUnkSize = 0;
			new_asset->umbraUnkData = nullptr;

			{
				// re-calculate values
				auto AlignUp = [](auto value, auto alignment)
				{
					return (value + (alignment - 1)) & ~(alignment - 1);
				};

				const auto lights = new_asset->primaryLightCount
					- new_asset->lastSunPrimaryLightIndex
					- new_asset->movingScriptablePrimaryLightCount
					- 1;

				new_asset->staticSpotOmniPrimaryLightCountAligned = AlignUp(lights, 32);

				new_asset->primaryLightMotionDetectBitsEntries = new_asset->staticSpotOmniPrimaryLightCountAligned >> 4;;
				new_asset->primaryLightMotionDetectBits = allocator.allocate<unsigned int>(new_asset->primaryLightMotionDetectBitsEntries); // runtime

				new_asset->entityMotionBitsEntries = 134; // idk (seems to always be 134)
				new_asset->entityMotionBits = allocator.allocate<unsigned int>(new_asset->entityMotionBitsEntries); // runtime

				new_asset->numPrimaryLightEntityShadowVisEntries = new_asset->staticSpotOmniPrimaryLightCountAligned * 0x86;
				new_asset->primaryLightEntityShadowVis = allocator.allocate<unsigned int>(new_asset->numPrimaryLightEntityShadowVisEntries); // runtime

				new_asset->dynEntMotionBitsEntries[0] =
					((new_asset->dpvsDyn.dynEntClientCount[0] + 31) >> 5) * 2;
				new_asset->dynEntMotionBits[0] = allocator.allocate<unsigned int>(new_asset->dynEntMotionBitsEntries[0]); // runtime
				new_asset->dynEntMotionBitsEntries[1] =
					((new_asset->dpvsDyn.dynEntClientCount[1] + 31) >> 5) * 2;
				new_asset->dynEntMotionBits[1] = allocator.allocate<unsigned int>(new_asset->dynEntMotionBitsEntries[1]); // runtime

				new_asset->numPrimaryLightDynEntShadowVisEntries[0] =
					(new_asset->staticSpotOmniPrimaryLightCountAligned * new_asset->dpvsDyn.dynEntClientCount[0]) >> 4;
				new_asset->primaryLightDynEntShadowVis[0] = allocator.allocate<unsigned int>(new_asset->numPrimaryLightDynEntShadowVisEntries[0]); // runtime
				new_asset->numPrimaryLightDynEntShadowVisEntries[1] =
					(new_asset->staticSpotOmniPrimaryLightCountAligned * new_asset->dpvsDyn.dynEntClientCount[1]) >> 4;
				new_asset->primaryLightDynEntShadowVis[1] = allocator.allocate<unsigned int>(new_asset->numPrimaryLightDynEntShadowVisEntries[1]); // runtime
			}
			

			return new_asset;
		}

		IW7::GfxWorld* convert(GfxWorld* asset, allocator& allocator)
		{
			// generate IW7 gfxworld
			return GenerateIW7GfxWorld(asset, allocator);
		}
	}
}