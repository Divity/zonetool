#include "stdafx.hpp"
#include "IW6/Assets/XSurface.hpp"

namespace ZoneTool
{
	namespace PackedShit
	{
		using namespace IW5;

#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)

		PackedTexCoords Vec2PackTexCoords(float* in) // ghosts func
		{
			int v2; // eax
			int v3; // esi
			int v4; // eax
			int v5; // ecx
			PackedTexCoords result; // eax
			int v7; // [esp+8h] [ebp+8h]
			int v8; // [esp+8h] [ebp+8h]

			v7 = LODWORD(in[0]);
			v2 = (int)((2 * v7) ^ 0x80003FFF) >> 14;
			if (v2 < 0x3FFF)
			{
				if (v2 <= -16384)
					LOWORD(v2) = -16384;
			}
			else
			{
				LOWORD(v2) = 0x3FFF;
			}
			v3 = (v7 >> 16) & 0xC000 | v2 & 0x3FFF;
			v8 = LODWORD(in[1]);
			v4 = (int)((2 * v8) ^ 0x80003FFF) >> 14;
			v5 = (v8 >> 16) & 0xC000;
			if (v4 < 0x3FFF)
			{
				if (v4 <= -16384)
					LOWORD(v4) = -16384;
				result.packed = v3 + ((v5 | v4 & 0x3FFF) << 16);
			}
			else
			{
				result.packed = v3 + ((v5 | 0x3FFF) << 16);
			}
			return result;
		}

		void Vec2UnpackTexCoords(const PackedTexCoords in, float* out) // iw5 func
		{
			unsigned int val;

			if (LOWORD(in.packed))
				val = ((LOWORD(in.packed) & 0x8000) << 16) | (((((in.packed & 0x3FFF) << 14) - (~(LOWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
			else
				val = 0;

			out[0] = *reinterpret_cast<float*>(&val);

			if (HIWORD(in.packed))
				val = ((HIWORD(in.packed) & 0x8000) << 16) | (((((HIWORD(in.packed) & 0x3FFF) << 14)
					- (~(HIWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
			else
				val = 0;

			out[1] = *reinterpret_cast<float*>(&val);
		}

		PackedUnitVec __fastcall Vec3PackUnitVec(float* unitVec) // h1 func
		{
			unsigned int v5; // ebx
			int v6; // ebx

			v5 = ((int)floor((float)((float)((float)((float)(fmaxf(1023.0f, fminf(1.0f, unitVec[2])) + 1.0f)
				* 0.5f)
				* 1023.0f)
				+ 0.5f)) | 0xFFFFFC00) << 10;
			v6 = ((int)floor((float)((float)((float)((float)(fmaxf(-1.0f, fminf(1.0f, unitVec[1])) + 1.0f) * 0.5f) * 1023.0f)
				+ 0.5f)) | v5) << 10;
			return (PackedUnitVec)(v6 | (unsigned int)(int)floor((float)((float)((float)((float)(fmaxf(-1.0f, fminf(1.0f, unitVec[0])) + 1.0f) * 0.5f)
				* 1023.0f)
				+ 0.5f)));
		}

#define COERCE_FLOAT float

		void Vec3UnpackUnitVec(PackedUnitVec in, float* out) // iw5 func
		{
			double v2; // st6
			float v3; // [esp+0h] [ebp-4h]

			v3 = ((double)HIBYTE(in.packed) - -192.0) / 32385.0;
			v2 = 127.0;
			*out = ((double)LOBYTE(in.packed) - 127.0) * v3;
			out[1] = ((double)BYTE1(in.packed) - v2) * v3;
			out[2] = v3 * ((double)BYTE2(in.packed) - v2);
		}
	}

	namespace IW5
	{
		void GenerateIW6BlendVertsShit(IW6::XSurface* surf)
		{
			unsigned short a = 0;
			unsigned short b = 0;
			unsigned short index = 1;
			for (short s = 0; s < (surf->blendVertCounts[0]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = 0;
				surf->blendVertsTable[a].b[2] = 0;
				surf->blendVertsTable[a].b[3] = 0;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = 0;
				surf->blendVertsTable[a].b[9] = 0;
				surf->blendVertsTable[a].b[10] = 0;
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 1;
			}
			index++;

			for (short s = 0; s < (surf->blendVertCounts[1]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = surf->blendVerts[b + 1] / 64;
				surf->blendVertsTable[a].b[2] = 0;
				surf->blendVertsTable[a].b[3] = 0;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = surf->blendVerts[b + 2];
				surf->blendVertsTable[a].b[9] = 0;
				surf->blendVertsTable[a].b[10] = 0;
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 3;
			}
			index++;

			for (short s = 0; s < (surf->blendVertCounts[2]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = surf->blendVerts[b + 1] / 64;
				surf->blendVertsTable[a].b[2] = surf->blendVerts[b + 3] / 64;
				surf->blendVertsTable[a].b[3] = 0;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = surf->blendVerts[b + 2];
				surf->blendVertsTable[a].b[9] = surf->blendVerts[b + 4];
				surf->blendVertsTable[a].b[10] = 0;
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 5;
			}
			index++;

			for (short s = 0; s < (surf->blendVertCounts[3]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = surf->blendVerts[b + 1] / 64;
				surf->blendVertsTable[a].b[2] = surf->blendVerts[b + 3] / 64;
				surf->blendVertsTable[a].b[3] = surf->blendVerts[b + 5] / 64;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = surf->blendVerts[b + 2];
				surf->blendVertsTable[a].b[9] = surf->blendVerts[b + 4];
				surf->blendVertsTable[a].b[10] = surf->blendVerts[b + 6];
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 7;
			}
			index++;
		}

		void GenerateIW6XSurface(IW6::XSurface* iw6_asset, XSurface* asset, ZoneMemory* mem)
		{
			iw6_asset->flags = 0;
			iw6_asset->flags |= ((asset->deformed & IW5::SURF_FLAG_VERTCOL_GREY) != 0) ? IW6::SURF_FLAG_VERTCOL_GREY : 0;
			iw6_asset->flags |= ((asset->deformed & IW5::SURF_FLAG_VERTCOL_NONE) != 0) ? IW6::SURF_FLAG_VERTCOL_NONE : 0;
			//iw6_asset->flags |= ((asset->deformed & IW5::SURF_FLAG_QUANTIZED) != 0) ? IW6::SURF_FLAG_QUANTIZED : 0;
			iw6_asset->flags |= ((asset->deformed & IW5::SURF_FLAG_SKINNED) != 0) ? IW6::SURF_FLAG_SKINNED : 0;

			iw6_asset->flags |= ((iw6_asset->flags & IW6::SURF_FLAG_VERTCOL_GREY) == 0) ? IW6::SURF_FLAG_VERTCOL_NONE : 0;

			iw6_asset->vertCount = asset->vertCount;
			iw6_asset->triCount = asset->triCount;
			iw6_asset->rigidVertListCount = asset->vertListCount;

			// blend verts
			memcpy(&iw6_asset->blendVertCounts, &asset->vertexInfo.vertCount, sizeof(asset->vertexInfo.vertCount));
			iw6_asset->blendVerts = reinterpret_cast<unsigned short* __ptr64>(asset->vertexInfo.vertsBlend);

			iw6_asset->blendVertsTable = mem->Alloc<IW6::BlendVertsUnknown>(asset->vertCount);
			GenerateIW6BlendVertsShit(iw6_asset);

			// triIndices
			iw6_asset->triIndices = reinterpret_cast<IW6::Face* __ptr64>(asset->triIndices);

			// verts
			//iw6_asset->verts0.packedVerts0 = reinterpret_cast<IW6::GfxPackedVertex* __ptr64>(asset->verticies);
			iw6_asset->verts0.packedVerts0 = mem->Alloc<IW6::GfxPackedVertex>(asset->vertCount);
			for (unsigned short i = 0; i < asset->vertCount; i++)
			{
				memcpy(&iw6_asset->verts0.packedVerts0[i], &asset->verticies[i], sizeof(IW5::GfxPackedVertex));

				float texCoord_unpacked[2];
				PackedShit::Vec2UnpackTexCoords(asset->verticies[i].texCoord, texCoord_unpacked);
				std::swap(texCoord_unpacked[0], texCoord_unpacked[1]); // these are inverted...
				iw6_asset->verts0.packedVerts0[i].texCoord.packed = PackedShit::Vec2PackTexCoords(texCoord_unpacked).packed;

				// re-calculate these...
				float normal_unpacked[3];
				PackedShit::Vec3UnpackUnitVec(asset->verticies[i].normal, normal_unpacked);
				iw6_asset->verts0.packedVerts0[i].normal.packed = PackedShit::Vec3PackUnitVec(normal_unpacked).packed;

				float tangent_unpacked[3];
				PackedShit::Vec3UnpackUnitVec(asset->verticies[i].normal, tangent_unpacked);
				iw6_asset->verts0.packedVerts0[i].tangent.packed = PackedShit::Vec3PackUnitVec(tangent_unpacked).packed;
			}

			// rigidVertLists
			iw6_asset->rigidVertLists = mem->Alloc<IW6::XRigidVertList>(asset->vertListCount);
			for (int i = 0; i < asset->vertListCount; i++)
			{
				iw6_asset->rigidVertLists[i].boneOffset = asset->rigidVertLists[i].boneOffset;
				iw6_asset->rigidVertLists[i].vertCount = asset->rigidVertLists[i].vertCount;
				iw6_asset->rigidVertLists[i].triOffset = asset->rigidVertLists[i].triOffset;
				iw6_asset->rigidVertLists[i].triCount = asset->rigidVertLists[i].triCount;

				if (asset->rigidVertLists[i].collisionTree)
				{
					iw6_asset->rigidVertLists[i].collisionTree = mem->Alloc<IW6::XSurfaceCollisionTree>();
					memcpy(&iw6_asset->rigidVertLists[i].collisionTree->trans, &asset->rigidVertLists[i].collisionTree->trans,
						sizeof(asset->rigidVertLists[i].collisionTree->trans));
					memcpy(&iw6_asset->rigidVertLists[i].collisionTree->scale, &asset->rigidVertLists[i].collisionTree->scale,
						sizeof(asset->rigidVertLists[i].collisionTree->scale));

					iw6_asset->rigidVertLists[i].collisionTree->nodeCount = asset->rigidVertLists[i].collisionTree->nodeCount;
					iw6_asset->rigidVertLists[i].collisionTree->nodes = mem->Alloc<IW6::XSurfaceCollisionNode>(
						asset->rigidVertLists[i].collisionTree->nodeCount);
					for (int j = 0; j < asset->rigidVertLists[i].collisionTree->nodeCount; j++)
					{
						memcpy(&iw6_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							&asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							sizeof(asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins));
						memcpy(&iw6_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							&asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							sizeof(asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs));

						iw6_asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex =
							asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex;
						iw6_asset->rigidVertLists[i].collisionTree->nodes[j].childCount =
							asset->rigidVertLists[i].collisionTree->nodes[j].childCount;
					}

					iw6_asset->rigidVertLists[i].collisionTree->leafCount = asset->rigidVertLists[i].collisionTree->leafCount;
					iw6_asset->rigidVertLists[i].collisionTree->leafs = mem->Alloc<IW6::XSurfaceCollisionLeaf>(
						asset->rigidVertLists[i].collisionTree->leafCount);
					for (int j = 0; j < asset->rigidVertLists[i].collisionTree->leafCount; j++)
					{
						iw6_asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex =
							asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex;
					}
				}
			}

			// partBits
			memcpy(&iw6_asset->partBits, &asset->partBits, sizeof(asset->partBits));
		}

		IW6::XModelSurfs* GenerateIW6XModelSurfs(ModelSurface* asset, ZoneMemory* mem)
		{
			// allocate IW6 XModelSurfs structure
			const auto iw6_asset = mem->Alloc<IW6::XModelSurfs>();

			iw6_asset->name = mem->StrDup(asset->name);
			iw6_asset->numsurfs = asset->xSurficiesCount;
			memcpy(&iw6_asset->partBits, &asset->partBits, sizeof(asset->partBits));

			iw6_asset->surfs = mem->Alloc<IW6::XSurface>(asset->xSurficiesCount);
			for (int i = 0; i < asset->xSurficiesCount; i++)
			{
				GenerateIW6XSurface(&iw6_asset->surfs[i], &asset->xSurficies[i], mem);
			}

			return iw6_asset;
		}

		void IXSurface::dump(ModelSurface* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::XSurface) == 232);

			// generate iw6 xsurface
			auto iw6_asset = GenerateIW6XModelSurfs(asset, mem);

			// dump iw6 xsurface
			IW6::IXSurface::dump(iw6_asset);
		}
	}
}