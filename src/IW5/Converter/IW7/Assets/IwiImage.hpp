#pragma once

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		struct source_image
		{
			std::uint8_t format = 0;
			unsigned short width = 0;
			unsigned short height = 0;
			std::string storage;
			std::vector<std::pair<const std::uint8_t*, std::size_t>> levels;
		};

		bool load_source(GfxImage* asset, source_image& out);

		IW7::GfxImage* convert_iwi(const char* name, std::uint8_t iw5_semantic, allocator& mem);

		IW7::GfxImage* convert_resident(GfxImage* asset, allocator& mem);
	}
}
