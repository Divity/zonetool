#pragma once

namespace ZoneTool::IW5
{
	namespace IW6Dumper
	{
		void dump(XModel* asset, ZoneMemory* mem, const std::function<const char* (uint16_t)>& convertToString);
	}
}