#include "stdafx.hpp"

#include <cstdarg>
#include <share.h>

namespace ZoneTool
{
	namespace
	{
		std::string build_log_path()
		{
			char exe[MAX_PATH]{};
			if (GetModuleFileNameA(nullptr, exe, MAX_PATH))
			{
				std::string path(exe);
				const auto slash = path.find_last_of("\\/");
				if (slash != std::string::npos)
				{
					return path.substr(0, slash + 1) + "zonetool.log";
				}
			}

			return "zonetool.log";
		}

		FILE* log_file()
		{
			static FILE* fp = _fsopen(log_path().data(), "w", _SH_DENYWR);
			return fp;
		}
	}

	const std::string& log_path()
	{
		static const std::string path = build_log_path();
		return path;
	}

	void log_print(const char* fmt, ...)
	{
		va_list args;

		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);

		auto* fp = log_file();
		if (!fp)
		{
			return;
		}

		va_start(args, fmt);
		vfprintf(fp, fmt, args);
		va_end(args);

		fflush(fp);
	}
}
