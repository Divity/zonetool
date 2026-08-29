// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "IW4/Assets/GameWorldMp.hpp"
#include "IW4/Assets/FxWorld.hpp"

namespace ZoneTool
{
	namespace T4
	{
		void IGameWorldSp::dump(GameWorldSp* asset, ZoneMemory* mem)
		{
			// lol, GameWorldMp contains no data in IW3
			auto* iw4_gameworld = mem->Alloc<IW4::GameWorldMp>();
			memset(iw4_gameworld, 0, sizeof IW4::GameWorldMp);

			iw4_gameworld->g_glassData = mem->Alloc<IW4::G_GlassData>();
			memset(iw4_gameworld->g_glassData, 0, sizeof IW4::G_GlassData);

			iw4_gameworld->name = asset->name;

			IW4::IGameWorldMp::dump(iw4_gameworld);

			// dump fx_map here too
			auto* iw4_fxworld = mem->Alloc<IW4::FxWorld>();
			memset(iw4_fxworld, 0, sizeof IW4::FxWorld);

			iw4_fxworld->name = asset->name;
			IW4::IFxWorld::dump(iw4_fxworld);
		}
	}
}
