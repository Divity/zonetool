#pragma once

namespace ZoneTool
{
	namespace IW6
	{
		class IXModel
		{
		public:
			static void dump(XModel* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
		};
	}
}