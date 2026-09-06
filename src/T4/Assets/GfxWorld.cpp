#include "stdafx.hpp"
#include "../IW4/Assets/GfxWorld.hpp"
#include "Material.hpp"

#include <cmath>

namespace ZoneTool
{
	namespace T4
	{
		static_assert(sizeof(GfxAabbTree) == 40);
		static_assert(sizeof(IW4::GfxAabbTree) == 44);

		void IGfxWorld::dump(GfxWorld* world, ZoneMemory* mem)
		{
			if (!world)
			{
				return;
			}

			IW4::GfxSky sky;
			IW4::GfxWorld map;
			ZeroMemory(&sky, sizeof sky);
			ZeroMemory(&map, sizeof map);

			map.name = world->name;
			map.baseName = world->baseName;
			map.planeCount = world->planeCount;
			map.nodeCount = world->nodeCount;
			map.surfaceCount = world->surfaceCount;

			map.skyCount = 1;
			map.skies = &sky;

			sky.skyImage = IGfxImage::generate_iw4_image(world->skyImage, mem);
			sky.skySamplerState = world->skySamplerState & 0xFF;
			sky.skyStartSurfs = reinterpret_cast<std::uint32_t*>(world->skyStartSurfs);
			sky.skySurfCount = world->skySurfCount;

			map.sunPrimaryLightIndex = world->sunPrimaryLightIndex;
			map.primaryLightCount = world->primaryLightCount;

			memcpy(&map.dpvsPlanes, &world->dpvsPlanes, sizeof world->dpvsPlanes);

			if (world->cells)
			{
				map.aabbTreeCounts = mem->Alloc<IW4::GfxCellTreeCount>(world->dpvsPlanes.cellCount);
				map.aabbTree = mem->Alloc<IW4::GfxCellTree>(world->dpvsPlanes.cellCount);
				map.cells = mem->Alloc<IW4::GfxCell>(world->dpvsPlanes.cellCount);

				for (auto i = 0; i < world->dpvsPlanes.cellCount; i++)
				{
					map.aabbTreeCounts[i].aabbTreeCount = world->cells[i].aabbTreeCount;

					map.cells[i].bounds.compute(world->cells[i].mins, world->cells[i].maxs);
					map.cells[i].portalCount = world->cells[i].portalCount;
					map.cells[i].reflectionProbeCount = world->cells[i].reflectionProbeCount;
					map.cells[i].reflectionProbes = world->cells[i].reflectionProbes;

					if (world->cells[i].aabbTree)
					{
						map.aabbTree[i].aabbtree = mem->Alloc<IW4::GfxAabbTree>(world->cells[i].aabbTreeCount);

						for (auto j = 0; j < world->cells[i].aabbTreeCount; j++)
						{
							auto* src = &world->cells[i].aabbTree[j];
							auto* dst = &map.aabbTree[i].aabbtree[j];

							dst->bounds.compute(src->mins, src->maxs);
							dst->childCount = src->childCount;
							dst->surfaceCount = src->surfaceCount;
							dst->startSurfIndex = src->startSurfIndex;
							dst->surfaceCountNoDecal = src->surfaceCount;
							dst->startSurfIndexNoDecal = src->startSurfIndex;
							dst->smodelIndexCount = src->smodelIndexCount;
							dst->smodelIndexes = src->smodelIndexes;
							dst->childrenOffset = (src->childrenOffset / sizeof(GfxAabbTree))
								* sizeof(IW4::GfxAabbTree);
						}
					}

					if (world->cells[i].portals)
					{
						map.cells[i].portals = mem->Alloc<IW4::GfxPortal>(world->cells[i].portalCount);

						std::unordered_map<GfxPortal*, IW4::GfxPortal*> portalMap = {{nullptr, nullptr}};
						for (auto j = 0; j < world->cells[i].portalCount; j++)
						{
							portalMap[&world->cells[i].portals[j]] = &map.cells[i].portals[j];
						}

						for (auto j = 0; j < world->cells[i].portalCount; j++)
						{
							auto* portal = &world->cells[i].portals[j];
							auto* destPortal = &map.cells[i].portals[j];

							destPortal->cellIndex = static_cast<unsigned short>(portal->cell - world->cells);
							if (destPortal->cellIndex >= static_cast<unsigned short>(world->dpvsPlanes.cellCount))
							{
								ZONETOOL_FATAL("Unable to calculate cell index. This should not happen!\n");
								destPortal->cellIndex = 0;
							}

							destPortal->vertices = reinterpret_cast<float(*)[3]>(portal->vertices);
							destPortal->vertexCount = portal->vertexCount;

							destPortal->writable.isQueued = portal->writable.isQueued;
							destPortal->writable.isAncestor = portal->writable.isAncestor;
							destPortal->writable.recursionDepth = portal->writable.recursionDepth;
							destPortal->writable.hullPointCount = portal->writable.hullPointCount;
							destPortal->writable.hullPoints = portal->writable.hullPoints;

							if (portalMap.find(portal->writable.queuedParent) != portalMap.end())
							{
								destPortal->writable.queuedParent = portalMap[portal->writable.queuedParent];
							}
							else
							{
								if (portal->writable.queuedParent)
								{
									ZONETOOL_ERROR("Unmapped portal. This shouldn't happen. Nulling it...\n");
								}
								destPortal->writable.queuedParent = nullptr;
							}

							memcpy(destPortal->plane.coeffs, portal->plane.coeffs, sizeof destPortal->plane.coeffs);
							memcpy(destPortal->hullAxis, portal->hullAxis, sizeof destPortal->hullAxis);
						}
					}
				}
			}

			map.draw.reflectionProbeCount = world->reflectionProbeCount;
			map.draw.reflectionProbeTextures = reinterpret_cast<IW4::GfxTexture*>(world->reflectionProbeTextures);
			map.draw.lightmapCount = world->lightmapCount;
			map.draw.lightmaps = mem->Alloc<IW4::GfxLightmapArray>(world->lightmapCount);

			for (auto i = 0; i < world->lightmapCount; i++)
			{
				if (world->lightmaps[i].primary)
				{
					IGfxImage::dump(world->lightmaps[i].primary, mem);
					map.draw.lightmaps[i].primary = IGfxImage::generate_iw4_image(world->lightmaps[i].primary, mem);
				}

				if (world->lightmaps[i].secondary)
				{
					IGfxImage::dump(world->lightmaps[i].secondary, mem);
					map.draw.lightmaps[i].secondary = IGfxImage::generate_iw4_image(world->lightmaps[i].secondary, mem);
				}
			}

			map.draw.lightmapPrimaryTextures = reinterpret_cast<IW4::GfxTexture*>(world->lightmapPrimaryTextures);
			map.draw.lightmapSecondaryTextures = reinterpret_cast<IW4::GfxTexture*>(world->lightmapSecondaryTextures);
			map.draw.skyImage = sky.skyImage;
			map.draw.outdoorImage = IGfxImage::generate_iw4_image(world->outdoorImage, mem);
			map.draw.vertexCount = world->vertexCount;
			memcpy(&map.draw.vd, &world->vd, sizeof world->vd);
			map.draw.vertexLayerDataSize = 0;
			memset(&map.draw.vld, 0, sizeof map.draw.vld);
			map.draw.indexCount = world->indexCount;
			map.draw.indices = world->indices;

			if (world->reflectionProbes)
			{
				map.draw.reflectionImages = mem->Alloc<IW4::GfxImage*>(world->reflectionProbeCount);
				map.draw.reflectionProbes = mem->Alloc<IW4::GfxReflectionProbe>(world->reflectionProbeCount);

				for (auto i = 0u; i < world->reflectionProbeCount; i++)
				{
					IGfxImage::dump(world->reflectionProbes[i].reflectionImage, mem);
					map.draw.reflectionImages[i] = IGfxImage::generate_iw4_image(
						world->reflectionProbes[i].reflectionImage, mem);

					memcpy(map.draw.reflectionProbes[i].offset, world->reflectionProbes[i].origin,
						sizeof map.draw.reflectionProbes[i].offset);
				}
			}

			memcpy(&map.lightGrid, &world->lightGrid, sizeof world->lightGrid);

			map.modelCount = world->modelCount;
			if (world->models)
			{
				map.models = mem->Alloc<IW4::GfxBrushModel>(world->modelCount);

				for (auto i = 0; i < world->modelCount; i++)
				{
					map.models[i].writable.bounds.compute(world->models[i].writable.mins, world->models[i].writable.maxs);
					map.models[i].bounds.compute(world->models[i].bounds[0], world->models[i].bounds[1]);

					auto* halfSize = map.models[i].bounds.halfSize;
					map.models[i].radius = std::sqrt(
						halfSize[0] * halfSize[0] + halfSize[1] * halfSize[1] + halfSize[2] * halfSize[2]);

					map.models[i].surfaceCount = world->models[i].surfaceCount;
					map.models[i].startSurfIndex = world->models[i].startSurfIndex;
					map.models[i].surfaceCountNoDecal = world->models[i].surfaceCount;
				}
			}

			map.bounds.compute(world->mins, world->maxs);

			map.materialMemoryCount = world->materialMemoryCount;
			map.materialMemory = reinterpret_cast<IW4::MaterialMemory*>(world->materialMemory);
			memcpy(&map.sun, &world->sun, sizeof world->sun);

			memcpy(map.outdoorLookupMatrix, world->outdoorLookupMatrix, sizeof map.outdoorLookupMatrix);
			map.outdoorImage = map.draw.outdoorImage;

			IGfxImage::dump(world->outdoorImage, mem);

			map.cellCasterBits[0] = world->cellCasterBits;
			map.cellCasterBits[1] = world->cellCasterBits;

			map.sceneDynModel = reinterpret_cast<IW4::GfxSceneDynModel*>(world->sceneDynModel);
			map.sceneDynBrush = reinterpret_cast<IW4::GfxSceneDynBrush*>(world->sceneDynBrush);

			map.primaryLightEntityShadowVis = reinterpret_cast<unsigned char*>(world->primaryLightEntityShadowVis);
			map.primaryLightDynEntShadowVis[0] = world->primaryLightDynEntShadowVis[0];
			map.primaryLightDynEntShadowVis[1] = world->primaryLightDynEntShadowVis[1];
			map.primaryLightForModelDynEnt = world->nonSunPrimaryLightForModelDynEnt;

			map.shadowGeom = reinterpret_cast<IW4::GfxShadowGeometry*>(world->shadowGeom);
			map.lightRegion = reinterpret_cast<IW4::GfxLightRegion*>(world->lightRegion);

			map.dpvs.smodelCount = world->dpvs.smodelCount;
			map.dpvs.staticSurfaceCount = world->dpvs.staticSurfaceCount;

			map.dpvs.litOpaqueSurfsBegin = world->dpvs.litSurfsBegin;
			map.dpvs.litOpaqueSurfsEnd = world->dpvs.litSurfsEnd;

			map.dpvs.litTransSurfsBegin = world->dpvs.decalSurfsBegin;
			map.dpvs.litTransSurfsEnd = world->dpvs.decalSurfsEnd;

			map.dpvs.shadowCasterSurfsBegin = world->dpvs.decalSurfsEnd;
			map.dpvs.shadowCasterSurfsEnd = world->dpvs.decalSurfsEnd;

			map.dpvs.emissiveSurfsBegin = world->dpvs.emissiveSurfsBegin;
			map.dpvs.emissiveSurfsEnd = world->dpvs.emissiveSurfsEnd;
			map.dpvs.smodelVisDataCount = world->dpvs.smodelVisDataCount;
			map.dpvs.surfaceVisDataCount = world->dpvs.surfaceVisDataCount;

			memcpy(map.dpvs.smodelVisData, world->dpvs.smodelVisData, sizeof map.dpvs.smodelVisData);
			memcpy(map.dpvs.surfaceVisData, world->dpvs.surfaceVisData, sizeof map.dpvs.surfaceVisData);

			if (world->dpvs.sortedSurfIndex)
			{
				const auto static_count = world->dpvs.staticSurfaceCount;

				auto* sorted = mem->Alloc<unsigned short>(static_count * 2);
				memcpy(sorted, world->dpvs.sortedSurfIndex, sizeof(unsigned short) * static_count);
				memcpy(sorted + static_count, world->dpvs.sortedSurfIndex, sizeof(unsigned short) * static_count);

				map.dpvs.staticSurfaceCountNoDecal = static_count;
				map.dpvs.sortedSurfIndex = sorted;
			}

			if (world->dpvs.smodelInsts)
			{
				map.dpvs.smodelInsts = mem->Alloc<IW4::GfxStaticModelInst>(world->dpvs.smodelCount);

				for (auto i = 0u; i < world->dpvs.smodelCount; i++)
				{
					map.dpvs.smodelInsts[i].bounds.compute(world->dpvs.smodelInsts[i].mins,
						world->dpvs.smodelInsts[i].maxs);

					map.dpvs.smodelInsts[i].lightingOrigin[0] = map.dpvs.smodelInsts[i].bounds.midPoint[0];
					map.dpvs.smodelInsts[i].lightingOrigin[1] = map.dpvs.smodelInsts[i].bounds.midPoint[1];
					map.dpvs.smodelInsts[i].lightingOrigin[2] = map.dpvs.smodelInsts[i].bounds.midPoint[2];
				}
			}

			if (world->dpvs.surfaces)
			{
				map.dpvs.surfaces = mem->Alloc<IW4::GfxSurface>(world->surfaceCount);
				map.dpvs.surfacesBounds = mem->Alloc<IW4::GfxSurfaceBounds>(world->surfaceCount);

				for (auto i = 0; i < world->surfaceCount; i++)
				{
					memcpy(&map.dpvs.surfaces[i].tris, &world->dpvs.surfaces[i].tris, sizeof IW4::srfTriangles_t);
					map.dpvs.surfaces[i].tris.vertexLayerData = 0;
					map.dpvs.surfaces[i].material = reinterpret_cast<IW4::Material*>(world->dpvs.surfaces[i].material);
					map.dpvs.surfaces[i].lightmapIndex = world->dpvs.surfaces[i].lightmapIndex;
					map.dpvs.surfaces[i].reflectionProbeIndex = world->dpvs.surfaces[i].reflectionProbeIndex;
					map.dpvs.surfaces[i].primaryLightIndex = world->dpvs.surfaces[i].primaryLightIndex;
					map.dpvs.surfaces[i].flags = world->dpvs.surfaces[i].flags;

					map.dpvs.surfacesBounds[i].bounds.compute(world->dpvs.surfaces[i].bounds[0],
						world->dpvs.surfaces[i].bounds[1]);
				}
			}

			if (world->dpvs.smodelDrawInsts)
			{
				map.dpvs.smodelDrawInsts = mem->Alloc<IW4::GfxStaticModelDrawInst>(world->dpvs.smodelCount);

				for (auto i = 0u; i < world->dpvs.smodelCount; i++)
				{
					memcpy(&map.dpvs.smodelDrawInsts[i].placement, &world->dpvs.smodelDrawInsts[i].placement,
						sizeof GfxPackedPlacement);
					memset(map.dpvs.smodelDrawInsts[i].cacheId, 0,
						sizeof map.dpvs.smodelDrawInsts[i].cacheId);

					map.dpvs.smodelDrawInsts[i].model = reinterpret_cast<IW4::XModel*>(
						world->dpvs.smodelDrawInsts[i].model);
					map.dpvs.smodelDrawInsts[i].cullDist = static_cast<unsigned short>(
						world->dpvs.smodelDrawInsts[i].cullDist);
					map.dpvs.smodelDrawInsts[i].reflectionProbeIndex = world->dpvs.smodelDrawInsts[i].reflectionProbeIndex;
					map.dpvs.smodelDrawInsts[i].primaryLightIndex = world->dpvs.smodelDrawInsts[i].primaryLightIndex;
					map.dpvs.smodelDrawInsts[i].lightingHandle = 0;
					map.dpvs.smodelDrawInsts[i].flags = world->dpvs.smodelDrawInsts[i].flags;

					if (world->dpvs.smodelInsts)
					{
						map.dpvs.smodelDrawInsts[i].groundLighting.packed =
							world->dpvs.smodelInsts[i].groundLighting.packed;
					}
				}
			}

			if (world->dpvs.surfaceMaterials && world->dpvs.surfaces)
			{
				map.dpvs.surfaceMaterials = mem->Alloc<IW4::GfxDrawSurf>(world->surfaceCount);

				for (auto i = 0; i < world->surfaceCount; i++)
				{
					const auto& src = world->dpvs.surfaceMaterials[i].fields;
					auto& dst = map.dpvs.surfaceMaterials[i].fields;

					dst.objectId = src.objectId;
					dst.reflectionProbeIndex = src.reflectionProbeIndex;
					dst.hasGfxEntIndex = 0;
					dst.customIndex = src.customIndex;
					dst.materialSortedIndex = src.materialSortedIndex;
					dst.prepass = src.prepass;
					dst.useHeroLighting = 0;
					dst.sceneLightIndex = src.primaryLightIndex;
					dst.surfType = src.surfType;
					dst.primarySortKey = world->dpvs.surfaces[i].material
						                     ? IMaterial::convert_sortkey(world->dpvs.surfaces[i].material)
						                     : src.primarySortKey;
					dst.unused = 0;
				}
			}
			map.dpvs.surfaceCastsSunShadow = reinterpret_cast<unsigned int*>(world->dpvs.surfaceCastsSunShadow);
			map.dpvs.usageCount = world->dpvs.usageCount;

			memcpy(&map.dpvsDyn, &world->dpvsDyn, sizeof world->dpvsDyn);

			map.fogTypesAllowed = 0x1;

			map.sortKeyLitDecal = 0x6;
			map.sortKeyEffectDecal = 0x27;
			map.sortKeyEffectAuto = 0x30;
			map.sortKeyDistortion = 0x2b;

			auto tri_index = 0;
			map.draw.indices = mem->Alloc<unsigned short>(map.draw.indexCount);

			for (auto i = 0; i < map.surfaceCount; i++)
			{
				auto* surface = &map.dpvs.surfaces[i];

				memcpy(&map.draw.indices[tri_index], &world->indices[surface->tris.baseIndex],
					surface->tris.triCount * 6);
				surface->tris.baseIndex = tri_index;
				tri_index += surface->tris.triCount * 3;
			}

			if (tri_index != map.draw.indexCount)
			{
				ZONETOOL_WARNING("Warning: Didn't sort all indicies for draw");
			}

			map.checksum = 0xDEADBEEF;

			IW4::IGfxWorld::dump(&map);
		}
	}
}
