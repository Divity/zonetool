#pragma once

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		IW7::GfxImage* convert(GfxImage* asset, allocator& allocator);

		IW7::GfxImage* GenerateLightmapSecondUnorm(const char* name, unsigned short width,
			unsigned short height, allocator& mem);

		IW7::GfxImage* GenerateIesLookup(allocator& mem);

		IW7::GfxImage* GenerateReflectionProbeArray(const std::vector<IW7::GfxImage*>& probes,
			allocator& mem);
	}
}