#pragma once

namespace ZoneTool
{
	namespace T4
	{
		class IMaterial
		{
		public:
			static void dump(Material* asset, ZoneMemory* mem);
			static unsigned char convert_sortkey(const Material* mat);
		};
	}
}
