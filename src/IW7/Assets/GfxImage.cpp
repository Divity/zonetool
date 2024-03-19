#include "stdafx.hpp"

namespace ZoneTool::IW7
{
	namespace
	{
		std::string clean_name(const std::string& name)
		{
			auto new_name = name;

			for (auto i = 0u; i < name.size(); i++)
			{
				switch (new_name[i])
				{
				case '*':
					new_name[i] = '_';
					break;
				}
			}

			return new_name;
		}
	}

	void IGfxImage::dump(GfxImage* asset)
	{
		auto path = "images\\"s + clean_name(asset->name) + ".iw7Image"s;
		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);

		if (asset->pixelData)
		{
			write.dump_array(asset->pixelData, asset->dataLen1);
		}

		if (asset->streamed)
		{
			throw std::runtime_error("streamed image?");
			__debugbreak();
		}
		write.close();
	}
}