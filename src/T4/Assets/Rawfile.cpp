// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "RawFile.hpp"

namespace ZoneTool
{
	namespace T4
	{
		void IRawFile::dump(RawFile* asset, ZoneMemory* mem)
		{
			auto fp = FileSystem::FileOpen(asset->name, "wb");

			if (fp)
			{
				if (asset->len > 0)
				{
					fwrite(asset->buffer, asset->len, 1, fp);
				}
			}

			FileSystem::FileClose(fp);
		}
	}
}