#pragma once

namespace ZoneTool
{
	namespace T4
	{
		class ISound
		{
		public:
			static void dump(snd_alias_list_t* asset, ZoneMemory* mem);
			static void set_driver_globals(SndDriverGlobals* globals);
		};
	}
}
