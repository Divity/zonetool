#pragma once

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		IW7::XModel* convert(XModel* asset, allocator& allocator);

		void request_dynamic_box(const std::string& model, float mass);
		bool wants_dynamic_box(const std::string& model, float* mass);

		int convert_surf_flags(int flags);
	}
}