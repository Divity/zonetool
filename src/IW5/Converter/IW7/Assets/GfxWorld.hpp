#pragma once

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		IW7::GfxWorld* convert(GfxWorld* asset, allocator& allocator);

		unsigned int first_reflection_probe(unsigned int reflection_probe_count);
	}
}