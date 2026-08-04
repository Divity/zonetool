// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

namespace ZoneTool
{
	namespace T4
	{
		union XAssetHeader;

		static Function<XAssetHeader(std::int32_t, const char*)> DB_FindXAssetHeader = 0x4B9F70;
		static Function<void(XZoneInfo*, std::uint32_t, std::uint32_t)> DB_LoadXAssets = 0x5CA950;

		typedef int (__cdecl * DB_GetXAssetSizeHandler_t)();
		static DB_GetXAssetSizeHandler_t* DB_GetXAssetSizeHandlers = (DB_GetXAssetSizeHandler_t*)0x4B9C50;

		static const char* SL_ConvertToString(std::uint16_t index)
		{
			return reinterpret_cast<const char*>(*reinterpret_cast<char**>(0xF66B3B8) + 12 * index + 4);
		}

		static short SL_AllocString(const std::string& string)
		{
			// TODO
		}
	}
}
