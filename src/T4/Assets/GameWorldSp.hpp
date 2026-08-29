// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

#include "../IW4/Assets/GameWorldMp.hpp"

namespace ZoneTool
{
	namespace T4
	{
		class IGameWorldSp : public IAsset
		{
		public:
			static void dump(GameWorldSp* asset, ZoneMemory* mem);
		};
	}
}
