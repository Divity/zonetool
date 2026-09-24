#include "stdafx.hpp"
#include "IW4/Assets/GameWorldMp.hpp"
#include "IW4/Assets/FxWorld.hpp"

namespace ZoneTool
{
	namespace IW3
	{
		void IGameWorldMp::dump(GameWorldMp* asset)
		{
			allocator allocator;

			// lol, GameWorldMp contains no data in IW3
			auto* iw4_gameworld = allocator.allocate<IW4::GameWorldMp>();
			memset(iw4_gameworld, 0, sizeof(IW4::GameWorldMp));

			iw4_gameworld->g_glassData = allocator.allocate<IW4::G_GlassData>();
			memset(iw4_gameworld->g_glassData, 0, sizeof(IW4::G_GlassData));

			iw4_gameworld->name = asset->name;

			IW4::IGameWorldMp::dump(iw4_gameworld);

			// dump fx_map here too
			auto* h1_fxworld = allocator.allocate<IW4::FxWorld>();
			memset(h1_fxworld, 0, sizeof(IW4::FxWorld));

			h1_fxworld->name = asset->name;
			IW4::IFxWorld::dump(h1_fxworld);

			zonetool::filesystem::csv_buffer_line("glass_map", asset->name);
			zonetool::filesystem::csv_buffer_line("fx_map", asset->name);
		}
	}
}