// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "../IW4/Assets/XAnimParts.hpp"

namespace ZoneTool
{
	namespace T4
	{
		void IXAnimParts::dump(XAnimParts* anim, ZoneMemory* mem)
		{
			if (anim)
			{
				auto asset = mem->Alloc<IW4::XAnimParts>();

#define XAE_CopyElement(name) asset->name = anim->name

				asset->name = (char*)anim->name;
				XAE_CopyElement(dataByteCount);
				XAE_CopyElement(dataShortCount);
				XAE_CopyElement(dataIntCount);
				XAE_CopyElement(randomDataByteCount);
				XAE_CopyElement(randomDataIntCount);
				asset->framecount = anim->numframes;

				asset->flags = 0;
				if (anim->bLoop)
				{
					asset->flags |= IW4::ANIM_LOOP;
				}
				if (anim->bDelta)
				{
					asset->flags |= IW4::ANIM_DELTA;
				}

				for (auto i = 0; i < 10; i++)
				{
					XAE_CopyElement(boneCount[i]);
				}

				XAE_CopyElement(notifyCount);
				XAE_CopyElement(assetType);
				XAE_CopyElement(isDefault);
				XAE_CopyElement(randomDataShortCount);
				asset->indexcount = anim->indexCount;
				XAE_CopyElement(framerate);
				XAE_CopyElement(frequency);
				asset->tagnames = anim->names;
				asset->dataByte = (char*)anim->dataByte;
				XAE_CopyElement(dataShort);
				XAE_CopyElement(dataInt);
				XAE_CopyElement(randomDataShort);
				asset->randomDataByte = (char*)anim->randomDataByte;
				XAE_CopyElement(randomDataInt);
				XAE_CopyElement(indices.data);
				asset->notify = reinterpret_cast<IW4::XAnimNotifyInfo*>(anim->notify);

				if (anim->deltaPart)
				{
					asset->delta = mem->Alloc<IW4::XAnimDeltaPart>();
					asset->delta->quat = reinterpret_cast<IW4::XAnimDeltaPartQuat*>(anim->deltaPart->quat);
					asset->delta->trans = reinterpret_cast<IW4::XAnimPartTrans*>(anim->deltaPart->trans);
				}

				// dump asset
				IW4::IXAnimParts::dump(asset, SL_ConvertToString);
			}
		}
	}
}
