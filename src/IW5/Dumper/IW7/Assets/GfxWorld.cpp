#include "stdafx.hpp"

#include "GfxWorld.hpp"
#include "Converter/IW7/Assets/GfxWorld.hpp"
#include "Converter/IW7/Assets/GfxImage.hpp"
#include "GfxImage.hpp"
#include "IW7/Assets/GfxWorld.hpp"
#include "IW7/Assets/GfxWorldTr.hpp"
#include "IW7/Assets/GfxLightMap.hpp"
#include "IW7/Assets/GfxImage.hpp"

namespace ZoneTool::IW5::IW7Dumper
{
	void dump(GfxWorld* asset)
	{
		// generate IW7 gfxworld
		allocator allocator;
		auto* iw7_asset = IW7Converter::convert(asset, allocator);

		// dump IW7 gfxworld
		IW7::IGfxWorld::dump(iw7_asset);

		// dump IW7 gfxworld_tr
		IW7::IGfxWorldTr::dump(iw7_asset->draw.transientZones[0]);

		{
			auto probes = reflection_probes();
			probes.resize(asset->draw.reflectionProbeCount, nullptr);

			const auto first = IW7Converter::first_reflection_probe(asset->draw.reflectionProbeCount);
			probes.erase(probes.begin(), probes.begin() + first);

			if (auto* probe_array = IW7Converter::GenerateReflectionProbeArray(probes, allocator))
			{
				IW7::IGfxImage::dump(probe_array);
			}
		}
		clear_reflection_probes();

		auto* ies = iw7_asset->draw.iesLookupTexture;
		if (ies && ies->pixelData)
		{
			IW7::IGfxImage::dump(ies);
		}

		// dump IW7 gfxlightmaps
		for (int i = 0; i < asset->draw.lightmapCount; i++)
		{
			IW7::IGfxLightMap::dump(iw7_asset->draw.lightMaps[i]);

			const auto* source = asset->draw.lightmaps[i].primary
				? asset->draw.lightmaps[i].primary
				: asset->draw.lightmaps[i].secondary;
			if (source)
			{
				ZONETOOL_INFO("lightmap %d: primary %s %ux%u, secondary %s %ux%u -> secondunorm %ux%u",
					i,
					asset->draw.lightmaps[i].primary ? asset->draw.lightmaps[i].primary->name : "(none)",
					asset->draw.lightmaps[i].primary ? asset->draw.lightmaps[i].primary->width : 0,
					asset->draw.lightmaps[i].primary ? asset->draw.lightmaps[i].primary->height : 0,
					asset->draw.lightmaps[i].secondary ? asset->draw.lightmaps[i].secondary->name : "(none)",
					asset->draw.lightmaps[i].secondary ? asset->draw.lightmaps[i].secondary->width : 0,
					asset->draw.lightmaps[i].secondary ? asset->draw.lightmaps[i].secondary->height : 0,
					source->width, source->height);

				IW7::IGfxImage::dump(IW7Converter::GenerateLightmapSecondUnorm(
					va("*lightmap%d_secondunorm", i).data(), source->width, source->height, allocator));
			}
			else
			{
				ZONETOOL_WARNING("lightmap %d has no primary or secondary texture, "
					"*lightmap%d_secondunorm not emitted", i, i);
			}
		}

		clear_lightmap_images();
	}
}