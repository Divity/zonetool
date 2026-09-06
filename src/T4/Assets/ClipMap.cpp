#include "stdafx.hpp"
#include "../IW4/Assets/ClipMap.hpp"

namespace ZoneTool
{
	namespace T4
	{
		void IClipMap::dump(clipMap_t* asset, ZoneMemory* mem)
		{
			if (!asset)
			{
				return;
			}

			auto* iw4_clipmap = mem->Alloc<IW4::clipMap_t>();
			memset(iw4_clipmap, 0, sizeof IW4::clipMap_t);

			iw4_clipmap->name = asset->name;
			iw4_clipmap->isInUse = asset->isInUse;

			iw4_clipmap->numCPlanes = asset->planeCount;
			iw4_clipmap->cPlanes = reinterpret_cast<IW4::cplane_s*>(asset->planes);

			iw4_clipmap->numStaticModels = static_cast<int>(asset->numStaticModels);
			iw4_clipmap->staticModelList = mem->Alloc<IW4::cStaticModel_s>(iw4_clipmap->numStaticModels);
			for (auto i = 0u; i < asset->numStaticModels; i++)
			{
				memcpy(&iw4_clipmap->staticModelList[i], &asset->staticModelList[i].xmodel,
					sizeof IW4::cStaticModel_s);
				iw4_clipmap->staticModelList[i].absBounds.compute();
			}

			iw4_clipmap->numMaterials = static_cast<int>(asset->numMaterials);
			iw4_clipmap->materials = mem->Alloc<IW4::dmaterial_t>(iw4_clipmap->numMaterials);
			for (auto i = 0; i < iw4_clipmap->numMaterials; i++)
			{
				iw4_clipmap->materials[i].material = mem->StrDup(asset->materials[i].material);
				iw4_clipmap->materials[i].contentFlags = asset->materials[i].contentFlags;
				iw4_clipmap->materials[i].surfaceFlags = asset->materials[i].surfaceFlags;
			}

			iw4_clipmap->numCBrushSides = static_cast<int>(asset->numBrushSides);
			iw4_clipmap->cBrushSides = mem->Alloc<IW4::cbrushside_t>(iw4_clipmap->numCBrushSides);

			std::unordered_map<cbrushside_t*, IW4::cbrushside_t*> mapped_brush_sides;

			for (auto i = 0u; i < asset->numBrushSides; i++)
			{
				mapped_brush_sides[&asset->brushsides[i]] = &iw4_clipmap->cBrushSides[i];

				iw4_clipmap->cBrushSides[i].plane = reinterpret_cast<IW4::cplane_s*>(asset->brushsides[i].plane);
				iw4_clipmap->cBrushSides[i].materialNum = static_cast<unsigned short>(asset->brushsides[i].materialNum);
				iw4_clipmap->cBrushSides[i].firstAdjacentSideOffset =
					static_cast<char>(asset->brushsides[i].firstAdjacentSideOffset);
				iw4_clipmap->cBrushSides[i].edgeCount = asset->brushsides[i].edgeCount;
			}

			iw4_clipmap->numCBrushEdges = static_cast<int>(asset->numBrushEdges);
			iw4_clipmap->cBrushEdges = reinterpret_cast<IW4::cbrushedge_t*>(asset->brushEdges);

			iw4_clipmap->numCNodes = static_cast<int>(asset->numNodes);
			iw4_clipmap->cNodes = reinterpret_cast<IW4::cNode_t*>(asset->nodes);

			iw4_clipmap->numCLeaf = static_cast<int>(asset->numLeafs);
			iw4_clipmap->cLeaf = mem->Alloc<IW4::cLeaf_t>(iw4_clipmap->numCLeaf);
			for (auto i = 0u; i < asset->numLeafs; i++)
			{
				memcpy(&iw4_clipmap->cLeaf[i], &asset->leafs[i], sizeof IW4::cLeaf_t);
				iw4_clipmap->cLeaf[i].bounds.compute();
			}

			iw4_clipmap->numCLeafBrushNodes = static_cast<int>(asset->leafbrushNodesCount);
			iw4_clipmap->cLeafBrushNodes = reinterpret_cast<IW4::cLeafBrushNode_s*>(asset->leafbrushNodes);

			iw4_clipmap->numLeafBrushes = static_cast<int>(asset->numLeafBrushes);
			iw4_clipmap->leafBrushes = reinterpret_cast<short*>(asset->leafbrushes);

			iw4_clipmap->numLeafSurfaces = static_cast<int>(asset->numLeafSurfaces);
			iw4_clipmap->leafSurfaces = reinterpret_cast<int*>(asset->leafsurfaces);

			iw4_clipmap->numVerts = static_cast<int>(asset->vertCount);
			iw4_clipmap->verts = reinterpret_cast<IW4::VecInternal<3>*>(asset->verts);

			iw4_clipmap->numTriIndices = asset->triCount;
			iw4_clipmap->triIndices = reinterpret_cast<short*>(asset->triIndices);
			iw4_clipmap->triEdgeIsWalkable = asset->triEdgeIsWalkable;

			iw4_clipmap->numCollisionBorders = asset->borderCount;
			iw4_clipmap->collisionBorders = reinterpret_cast<IW4::CollisionBorder*>(asset->borders);

			iw4_clipmap->numCollisionPartitions = asset->partitionCount;
			iw4_clipmap->collisionPartitions = mem->Alloc<IW4::CollisionPartition>(asset->partitionCount);
			for (auto i = 0; i < asset->partitionCount; i++)
			{
				iw4_clipmap->collisionPartitions[i].triCount = asset->partitions[i].triCount;
				iw4_clipmap->collisionPartitions[i].borderCount = asset->partitions[i].borderCount;
				iw4_clipmap->collisionPartitions[i].firstTri = asset->partitions[i].firstTri;
				iw4_clipmap->collisionPartitions[i].borders =
					reinterpret_cast<IW4::CollisionBorder*>(asset->partitions[i].borders);
			}

			iw4_clipmap->numCollisionAABBTrees = asset->aabbTreeCount;
			iw4_clipmap->collisionAABBTrees = mem->Alloc<IW4::CollisionAabbTree>(iw4_clipmap->numCollisionAABBTrees);
			for (auto i = 0; i < asset->aabbTreeCount; i++)
			{
				memcpy(&iw4_clipmap->collisionAABBTrees[i].origin, &asset->aabbTrees[i].origin, 12);
				memcpy(&iw4_clipmap->collisionAABBTrees[i].halfSize, &asset->aabbTrees[i].halfSize, 12);
				iw4_clipmap->collisionAABBTrees[i].materialIndex = asset->aabbTrees[i].materialIndex;
				iw4_clipmap->collisionAABBTrees[i].childCount = asset->aabbTrees[i].childCount;
				iw4_clipmap->collisionAABBTrees[i].u.firstChildIndex = asset->aabbTrees[i].u.firstChildIndex;
			}

			iw4_clipmap->numCModels = static_cast<int>(asset->numSubModels);
			iw4_clipmap->cModels = mem->Alloc<IW4::cmodel_t>(iw4_clipmap->numCModels);
			for (auto i = 0u; i < asset->numSubModels; i++)
			{
				memcpy(&iw4_clipmap->cModels[i], &asset->cmodels[i], sizeof IW4::cmodel_t);
				iw4_clipmap->cModels[i].bounds.compute();
				iw4_clipmap->cModels[i].leaf.bounds.compute();
			}

			iw4_clipmap->numBrushes = static_cast<short>(asset->numBrushes);
			iw4_clipmap->brushes = mem->Alloc<IW4::cbrush_t>(iw4_clipmap->numBrushes);
			iw4_clipmap->brushBounds = mem->Alloc<IW4::Bounds>(iw4_clipmap->numBrushes);
			iw4_clipmap->brushContents = mem->Alloc<int>(iw4_clipmap->numBrushes);
			for (auto i = 0u; i < asset->numBrushes; i++)
			{
				memcpy(&iw4_clipmap->brushes[i].axialMaterialNum, &asset->brushes[i].axialMaterialNum,
					sizeof iw4_clipmap->brushes[i].axialMaterialNum);
				memcpy(&iw4_clipmap->brushes[i].edgeCount, &asset->brushes[i].edgeCount,
					sizeof iw4_clipmap->brushes[i].edgeCount);

				for (auto axis = 0; axis < 2; axis++)
				{
					for (auto side = 0; side < 3; side++)
					{
						iw4_clipmap->brushes[i].firstAdjacentSideOffsets[axis][side] =
							static_cast<char>(asset->brushes[i].firstAdjacentSideOffsets[axis][side]);
					}
				}

				iw4_clipmap->brushes[i].numsides = static_cast<unsigned short>(asset->brushes[i].numsides);
				if (asset->brushes[i].sides)
				{
					iw4_clipmap->brushes[i].sides = mapped_brush_sides.find(asset->brushes[i].sides)->second;
				}
				iw4_clipmap->brushes[i].edge = reinterpret_cast<IW4::cbrushedge_t*>(asset->brushes[i].baseAdjacentSide);

				iw4_clipmap->brushBounds[i].compute(asset->brushes[i].mins, asset->brushes[i].maxs);
				iw4_clipmap->brushContents[i] = asset->brushes[i].contents;
			}

			iw4_clipmap->smodelNodeCount = 1;
			iw4_clipmap->smodelNodes = mem->Alloc<IW4::SModelAabbNode>();
			if (asset->numStaticModels == 0)
			{
				iw4_clipmap->smodelNodes[0].bounds.halfSize[0] = -131072.000f;
				iw4_clipmap->smodelNodes[0].bounds.halfSize[1] = -131072.000f;
				iw4_clipmap->smodelNodes[0].bounds.halfSize[2] = -131072.000f;
			}
			else
			{
				float maxs[3];
				float mins[3];

				memcpy(maxs, asset->staticModelList[0].absmax, sizeof maxs);
				memcpy(mins, asset->staticModelList[0].absmin, sizeof mins);

				for (auto i = 1u; i < asset->numStaticModels; i++)
				{
					for (auto axis = 0; axis < 3; axis++)
					{
						maxs[axis] = max(maxs[axis], asset->staticModelList[i].absmax[axis]);
						mins[axis] = min(mins[axis], asset->staticModelList[i].absmin[axis]);
					}
				}

				iw4_clipmap->smodelNodes[0].bounds.compute(mins, maxs);
				iw4_clipmap->smodelNodes[0].childCount = static_cast<short>(asset->numStaticModels);
				iw4_clipmap->smodelNodes[0].firstChild = 0;
			}

			iw4_clipmap->mapEnts = mem->Alloc<IW4::MapEnts>();
			iw4_clipmap->mapEnts->name = asset->mapEnts->name;

			auto* iw4_mapEnts = iw4_clipmap->mapEnts;

			if (asset->cmodels)
			{
				iw4_mapEnts->trigger.modelCount = asset->numSubModels;
				iw4_mapEnts->trigger.hullCount = asset->numSubModels;

				iw4_mapEnts->trigger.models = mem->Alloc<IW4::TriggerModel>(asset->numSubModels);
				iw4_mapEnts->trigger.hulls = mem->Alloc<IW4::TriggerHull>(asset->numSubModels);

				std::vector<IW4::TriggerSlab> slabs;

				for (auto i = 0u; i < asset->numSubModels; i++)
				{
					auto* trigHull = &iw4_mapEnts->trigger.hulls[i];

					trigHull->bounds.compute(asset->cmodels[i].mins, asset->cmodels[i].maxs);
					trigHull->contents = asset->cmodels[i].leaf.brushContents | asset->cmodels[i].leaf.terrainContents;

					auto* trigMod = &iw4_mapEnts->trigger.models[i];
					trigMod->hullCount = 1;
					trigMod->firstHull = i;
					trigMod->contents = trigHull->contents;

					auto* node = &asset->leafbrushNodes[asset->cmodels[i].leaf.leafBrushNode];
					if (node->leafBrushCount)
					{
						for (short j = 0; j < node->leafBrushCount; j++)
						{
							auto* brush = &asset->brushes[node->data.leaf.brushes[j]];

							const auto baseSlab = slabs.size();
							for (auto k = 0u; k < brush->numsides; k++)
							{
								IW4::TriggerSlab curSlab;
								curSlab.dir[0] = brush->sides[k].plane->normal[0];
								curSlab.dir[1] = brush->sides[k].plane->normal[1];
								curSlab.dir[2] = brush->sides[k].plane->normal[2];
								curSlab.halfSize = brush->sides[k].plane->dist;
								curSlab.midPoint = 0.0f;

								slabs.push_back(curSlab);
							}

							trigHull->firstSlab = static_cast<unsigned short>(baseSlab);
							trigHull->slabCount = static_cast<unsigned short>(i - baseSlab);
						}
					}
				}

				iw4_mapEnts->trigger.slabCount = static_cast<int>(slabs.size());
				iw4_mapEnts->trigger.slabs = mem->Alloc<IW4::TriggerSlab>(slabs.size());
				for (auto i = 0u; i < slabs.size(); i++)
				{
					memcpy(&iw4_mapEnts->trigger.slabs[i], &slabs[i], sizeof IW4::TriggerSlab);
				}
			}

			AssetDumper trigger_dumper;
			if (trigger_dumper.open(iw4_mapEnts->name + ".ents.triggers"s))
			{
				trigger_dumper.dump_int(iw4_mapEnts->trigger.modelCount);
				trigger_dumper.dump_array<IW4::TriggerModel>(iw4_mapEnts->trigger.models, iw4_mapEnts->trigger.modelCount);

				trigger_dumper.dump_int(iw4_mapEnts->trigger.hullCount);
				trigger_dumper.dump_array<IW4::TriggerHull>(iw4_mapEnts->trigger.hulls, iw4_mapEnts->trigger.hullCount);

				trigger_dumper.dump_int(iw4_mapEnts->trigger.slabCount);
				trigger_dumper.dump_array<IW4::TriggerSlab>(iw4_mapEnts->trigger.slabs, iw4_mapEnts->trigger.slabCount);

				trigger_dumper.close();
			}

			for (auto i = 0; i < 2; i++)
			{
				iw4_clipmap->dynEntCount[i] = asset->dynEntCount[i];

				if (iw4_clipmap->dynEntCount[i] <= 0)
				{
					continue;
				}

				iw4_clipmap->dynEntDefList[i] = mem->Alloc<IW4::DynEntityDef>(iw4_clipmap->dynEntCount[i]);
				iw4_clipmap->dynEntPoseList[i] = mem->Alloc<IW4::DynEntityPose>(iw4_clipmap->dynEntCount[i]);
				iw4_clipmap->dynEntClientList[i] = mem->Alloc<IW4::DynEntityClient>(iw4_clipmap->dynEntCount[i]);
				iw4_clipmap->dynEntCollList[i] = mem->Alloc<IW4::DynEntityColl>(iw4_clipmap->dynEntCount[i]);

				for (auto j = 0; j < iw4_clipmap->dynEntCount[i]; j++)
				{
					iw4_clipmap->dynEntDefList[i][j].type =
						static_cast<IW4::DynEntityType>(asset->dynEntDefList[i][j].type);
					memcpy(&iw4_clipmap->dynEntDefList[i][j].pose, &asset->dynEntDefList[i][j].pose,
						sizeof IW4::DynEntityPose);
					iw4_clipmap->dynEntDefList[i][j].xModel =
						reinterpret_cast<IW4::XModel*>(asset->dynEntDefList[i][j].xModel);
					iw4_clipmap->dynEntDefList[i][j].brushModel = asset->dynEntDefList[i][j].brushModel;
					iw4_clipmap->dynEntDefList[i][j].physicsBrushModel = asset->dynEntDefList[i][j].physicsBrushModel;
					iw4_clipmap->dynEntDefList[i][j].destroyFx =
						reinterpret_cast<IW4::FxEffectDef*>(asset->dynEntDefList[i][j].destroyFx);
					iw4_clipmap->dynEntDefList[i][j].physPreset =
						reinterpret_cast<IW4::PhysPreset*>(asset->dynEntDefList[i][j].physPreset);
					iw4_clipmap->dynEntDefList[i][j].health = asset->dynEntDefList[i][j].health;
					memcpy(&iw4_clipmap->dynEntDefList[i][j].mass, &asset->dynEntDefList[i][j].mass,
						sizeof IW4::PhysMass);
					iw4_clipmap->dynEntDefList[i][j].contents = asset->dynEntDefList[i][j].contents;

					memcpy(&iw4_clipmap->dynEntPoseList[i][j], &asset->dynEntPoseList[i][j], sizeof IW4::DynEntityPose);
					memcpy(&iw4_clipmap->dynEntClientList[i][j], &asset->dynEntClientList[i][j],
						sizeof IW4::DynEntityClient);
					memcpy(&iw4_clipmap->dynEntCollList[i][j], &asset->dynEntCollList[i][j], sizeof IW4::DynEntityColl);
				}
			}

			iw4_clipmap->checksum = asset->checksum;

			IW4::IClipMap::dump(iw4_clipmap);
		}
	}
}
