#include "stdafx.hpp"
#include "../IW4/Assets/FxEffectDef.hpp"

namespace ZoneTool
{
	namespace T4
	{
		namespace
		{
			IW4::FxEffectDefRef* convert_effect_ref(const FxEffectDefRef& source, ZoneMemory* mem)
			{
				if (!source.handle)
				{
					return nullptr;
				}

				if (!source.handle->name)
				{
					return nullptr;
				}

				auto* ref = mem->Alloc<IW4::FxEffectDefRef>();
				ref->name = source.handle->name;

				return ref;
			}

			void convert_elem(FxElemDef* source, IW4::FxElemDef* dest, ZoneMemory* mem)
			{
				memcpy(dest, source, offsetof(IW4::FxElemDef, elemType));

				dest->elemType = source->elemType + (source->elemType >= FX_ELEM_TYPE_MODEL ? 1 : 0);
				dest->visualCount = source->visualCount;
				dest->velIntervalCount = source->velIntervalCount;
				dest->visStateIntervalCount = source->visStateIntervalCount;

				dest->velSamples = reinterpret_cast<IW4::FxElemVelStateSample*>(source->velSamples);
				dest->visSamples = reinterpret_cast<IW4::FxElemVisStateSample*>(source->visSamples);

				memcpy(&dest->visuals, &source->visuals, sizeof IW4::FxElemDefVisuals);

				dest->collBounds.compute(source->collMins, source->collMaxs);

				dest->effectOnImpact = convert_effect_ref(source->effectOnImpact, mem);
				dest->effectOnDeath = convert_effect_ref(source->effectOnDeath, mem);
				dest->effectEmitted = convert_effect_ref(source->effectEmitted, mem);

				memcpy(&dest->emitDist, &source->emitDist, sizeof IW4::FxFloatRange);
				memcpy(&dest->emitDistVariance, &source->emitDistVariance, sizeof IW4::FxFloatRange);

				if (dest->elemType == IW4::FX_ELEM_TYPE_TRAIL)
				{
					auto* trail = mem->Alloc<IW4::FxTrailDef>();

					if (source->trailDef)
					{
						trail->scrollTimeMsec = source->trailDef->scrollTimeMsec;
						trail->repeatDist = source->trailDef->repeatDist;
						trail->vertCount = source->trailDef->vertCount;
						trail->verts = reinterpret_cast<IW4::FxTrailVertex*>(source->trailDef->verts);
						trail->indCount = source->trailDef->indCount;
						trail->inds = source->trailDef->inds;

						const auto split_dist = static_cast<float>(source->trailDef->splitDist);
						trail->invSplitDist = split_dist > 0.0f ? 1.0f / split_dist : 0.0f;
					}

					trail->invSplitArcDist = 0.0f;
					trail->invSplitTime = 0.0f;

					dest->extended.trailDef = trail;
				}
				else
				{
					dest->extended.trailDef = nullptr;
				}

				dest->sortOrder = source->sortOrder;
				dest->lightingFrac = source->lightingFrac;
				dest->useItemClip = source->useItemClip;
				dest->fadeInfo = 0;
			}
		}

		void IFxEffectDef::dump(FxEffectDef* asset, ZoneMemory* mem)
		{
			if (!asset || !asset->name)
			{
				return;
			}

			auto* iw4_fx = mem->Alloc<IW4::FxEffectDef>();

			iw4_fx->name = asset->name;
			iw4_fx->flags = asset->flags;
			iw4_fx->totalSize = asset->totalSize;
			iw4_fx->msecLoopingLife = asset->msecLoopingLife;
			iw4_fx->elemDefCountLooping = asset->elemDefCountLooping;
			iw4_fx->elemDefCountOneShot = asset->elemDefCountOneShot;
			iw4_fx->elemDefCountEmission = asset->elemDefCountEmission;

			const auto elem_count = asset->elemDefCountLooping + asset->elemDefCountOneShot
				+ asset->elemDefCountEmission;

			if (elem_count > 0 && asset->elemDefs)
			{
				iw4_fx->elemDefs = mem->Alloc<IW4::FxElemDef>(elem_count);

				for (auto i = 0; i < elem_count; i++)
				{
					convert_elem(&asset->elemDefs[i], &iw4_fx->elemDefs[i], mem);
				}
			}

			IW4::IFxEffectDef::dump(iw4_fx);
		}
	}
}
