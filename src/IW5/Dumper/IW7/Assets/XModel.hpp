#pragma once

namespace ZoneTool::IW5
{
	namespace IW7Dumper
	{
		void dump(XModel* asset, const std::function<const char* (uint16_t)>& convertToString);
	}
}