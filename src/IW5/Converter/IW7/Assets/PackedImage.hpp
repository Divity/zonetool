#pragma once

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		struct decoded_image
		{
			unsigned short width = 0;
			unsigned short height = 0;
			std::vector<std::vector<std::uint8_t>> mips;
		};

		bool decode_source(GfxImage* asset, decoded_image& out);

		IW7::GfxImage* build_packed_cs(const char* name, const decoded_image& colour,
			const decoded_image* spec, allocator& mem);

		IW7::GfxImage* build_packed_ng(const char* name, const decoded_image& normal,
			const decoded_image* spec, allocator& mem);

		IW7::GfxImage* build_packed_a(const char* name, const decoded_image& colour,
			allocator& mem);
	}
}
