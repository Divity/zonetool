#pragma once

namespace ZoneTool::IW5
{
	namespace H1Dumper
	{
		void dump(XAnimParts* asset, const std::function<const char* (uint16_t)>& convertToString);
	}
}