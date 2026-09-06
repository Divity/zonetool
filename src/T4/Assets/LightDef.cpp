#include "stdafx.hpp"
#include "../IW4/Assets/LightDef.hpp"

namespace ZoneTool
{
	namespace T4
	{
		void ILightDef::dump(GfxLightDef* asset, ZoneMemory* mem)
		{
			if (!asset || !asset->name)
			{
				return;
			}

			auto* iw4_lightdef = mem->Alloc<IW4::GfxLightDef>();

			iw4_lightdef->name = asset->name;
			iw4_lightdef->lmapLookupStart = asset->lmapLookupStart;
			iw4_lightdef->attenuation.samplerState = asset->attenuation.samplerState;

			if (asset->attenuation.image)
			{
				IGfxImage::dump(asset->attenuation.image, mem);

				auto* image = IGfxImage::generate_iw4_image(asset->attenuation.image, mem);
				if (!image)
				{
					image = mem->Alloc<IW4::GfxImage>();
					image->name = const_cast<char*>(asset->attenuation.image->name);
				}

				iw4_lightdef->attenuation.image = image;
			}

			IW4::ILightDef::dump(iw4_lightdef);
		}
	}
}
