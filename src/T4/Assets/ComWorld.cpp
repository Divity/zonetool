#include "stdafx.hpp"
#include "IW4/Assets/ComWorld.hpp"

namespace ZoneTool::T4
{
    void IComWorld::dump(ComWorld* asset, ZoneMemory* mem)
    {
        if (!asset)
        {
            return;
        }

        ZONETOOL_INFO(
            "dumping ComWorld %s",
            asset->name ? asset->name : "<null>"
        );

        auto* iw4_world = mem->Alloc<IW4::ComWorld>();

        iw4_world->name = asset->name;
        iw4_world->isInUse = asset->isInUse;
        iw4_world->primaryLightCount = asset->primaryLightCount;

        if (asset->primaryLightCount && asset->primaryLights)
        {
            iw4_world->primaryLights =
                mem->Alloc<IW4::ComPrimaryLight>(
                    asset->primaryLightCount
                );

            for (unsigned int i = 0;
                i < asset->primaryLightCount;
                ++i)
            {
                auto& src = asset->primaryLights[i];
                auto& dst = iw4_world->primaryLights[i];

                dst.type =
                    src.type;

                dst.canUseShadowMap =
                    src.canUseShadowMap;

                dst.exponent =
                    src.exponent;

                std::memcpy(
                    dst.color,
                    src.color,
                    sizeof(dst.color)
                );

                std::memcpy(
                    dst.dir,
                    src.dir,
                    sizeof(dst.dir)
                );

                std::memcpy(
                    dst.origin,
                    src.origin,
                    sizeof(dst.origin)
                );

                dst.radius =
                    src.radius;

                dst.cosHalfFovOuter =
                    src.cosHalfFovOuter;

                dst.cosHalfFovInner =
                    src.cosHalfFovInner;

                dst.cosHalfFovExpanded =
                    src.cosHalfFovExpanded;

                dst.rotationLimit =
                    src.rotationLimit;

                dst.translationLimit =
                    src.translationLimit;

                dst.defName =
                    src.defName;
            }
        }

        ZONETOOL_INFO(
            "T4 IComWorld::dump: calling IW4::IComWorld::dump"
        );

        IW4::IComWorld::dump(iw4_world);
    }
}