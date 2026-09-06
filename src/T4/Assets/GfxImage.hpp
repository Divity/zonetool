#pragma once

namespace ZoneTool
{
	namespace T4
	{
		class IGfxImage
		{
		public:
			static IW4::GfxImage* generate_iw4_image(GfxImage* asset, ZoneMemory* mem);
			static void dump(GfxImage* asset, ZoneMemory* mem);
		};
	}
}
