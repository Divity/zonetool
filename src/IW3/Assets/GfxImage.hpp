#pragma once

namespace ZoneTool
{
	namespace IW3
	{
		class IGfxImage
		{
		public:
			static IW4::GfxImage* GenerateIW4Image(GfxImage* image, allocator& allocator);
			static void dump(GfxImage* asset);
		};
	}
}