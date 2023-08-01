// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "IW5/Assets/FontDef.hpp"

namespace ZoneTool
{
	namespace IW3
	{
		void IFontDef::init(const std::string& name, ZoneMemory* mem)
		{
			this->name_ = name;
			this->asset_ = this->parse(name, mem);

			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader(this->type(), this->name_.data()).font;
			}
		}

		void IFontDef::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		void IFontDef::load_depending(IZone* zone)
		{
			auto* data = this->asset_;

			if (data->material)
			{
				zone->add_asset_of_type(material, data->material->name);
			}

			if (data->glowMaterial)
			{
				zone->add_asset_of_type(material, data->glowMaterial->name);
			}
		}

		std::string IFontDef::name()
		{
			return this->name_;
		}

		std::int32_t IFontDef::type()
		{
			return font;
		}

		void IFontDef::write(IZone* zone, ZoneBuffer* buf)
		{
			auto* data = this->asset_;
			auto* dest = buf->write(data);

			buf->push_stream(3);
			START_LOG_STREAM;

			dest->fontName = buf->write_str(this->name());

			if (data->material)
			{
				dest->material = reinterpret_cast<Material*>(
					zone->get_asset_pointer(material, data->material->name)
				);
			}

			if (data->glowMaterial)
			{
				dest->glowMaterial = reinterpret_cast<Material*>(
					zone->get_asset_pointer(material, data->glowMaterial->name)
				);
			}

			if (data->glyphs)
			{
				buf->align(3);
				auto* dest_glyphs = buf->write(data->glyphs, data->glyphCount);
				ZoneBuffer::clear_pointer(&dest->glyphs);
			}

			END_LOG_STREAM;
			buf->pop_stream();
		}

		Font_s* IFontDef::parse(const std::string& name, ZoneMemory* mem)
		{
			return reinterpret_cast<Font_s*>(IW5::IFontDef::parse(name, mem));
		}

		void IFontDef::dump(Font_s* asset, ZoneMemory* mem)
		{
			IW5::IFontDef::dump(reinterpret_cast<IW5::Font_s*>(asset));
		}
	}
}
