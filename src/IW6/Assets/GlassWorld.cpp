// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void IGlassWorld::dump(GlassWorld* asset)
		{
			const auto path = asset->name + ".glassmap"s;

			AssetDumper write;
			if (!write.open(path))
			{
				return;
			}

			write.dump_single(asset);
			write.dump_string(asset->name);

			write.dump_single(asset->g_glassData);

			if (asset->g_glassData)
			{
				write.dump_array(asset->g_glassData->glassPieces, asset->g_glassData->pieceCount);
				write.dump_array(asset->g_glassData->glassNames, asset->g_glassData->glassNameCount);

				for (unsigned int i = 0; i < asset->g_glassData->glassNameCount; i++)
				{
					write.dump_string(asset->g_glassData->glassNames[i].nameStr);
					write.dump_array(asset->g_glassData->glassNames[i].pieceIndices,
						asset->g_glassData->glassNames[i].pieceCount);
				}
			}

			write.close();
		}
	}
}