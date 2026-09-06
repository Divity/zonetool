#include "stdafx.hpp"

namespace ZoneTool
{
	namespace T4
	{
		namespace
		{
			bool is_fourcc(const char* data, const char* fourcc)
			{
				return !strncmp(data, fourcc, 4);
			}
		}

		void ILoadedSound::dump(LoadedSound* asset, ZoneMemory* mem)
		{
			if (!asset || !asset->name || !asset->sound.data || asset->sound.data_size <= 0)
			{
				return;
			}

			if (asset->sound.data_size < 12 || !is_fourcc(asset->sound.data, "RIFF"))
			{
				ZONETOOL_ERROR("Loaded sound \"%s\" is not a RIFF container, skipping.", asset->name);
				return;
			}

			if (!is_fourcc(&asset->sound.data[8], "WAVE"))
			{
				static bool reported = false;
				if (!reported)
				{
					reported = true;
					ZONETOOL_WARNING("Loaded sound \"%s\" is not PCM WAVE (first seen); IW4 cannot use it.", asset->name);
				}
			}

			auto* file = FileSystem::FileOpen("loaded_sound\\"s + asset->name, "wb");
			if (!file)
			{
				return;
			}

			fwrite(asset->sound.data, asset->sound.data_size, 1, file);
			FileSystem::FileClose(file);
		}
	}
}
