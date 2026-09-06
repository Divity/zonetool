// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		PhysPreset* IPhysPreset::parse(const std::string& name, ZoneMemory* mem)
		{
			const auto path = "physpreset\\"s + name + ".json"s;
			if (!FileSystem::FileExists(path))
			{
				return nullptr;
			}

			ZONETOOL_INFO("Parsing physpreset \"%s\"...", name.c_str());

			auto* file = FileSystem::FileOpen(path, "rb");
			const auto size = FileSystem::FileSize(file);
			auto bytes = FileSystem::ReadBytes(file, size);
			FileSystem::FileClose(file);

			auto data = nlohmann::json::parse(bytes);

			auto* asset = mem->Alloc<PhysPreset>();

			asset->name = mem->StrDup(data["name"].get<std::string>());
			asset->type = data["type"].get<int>();
			asset->mass = data["mass"].get<float>();
			asset->bounce = data["bounce"].get<float>();
			asset->friction = data["friction"].get<float>();
			asset->bulletForceScale = data["bulletForceScale"].get<float>();
			asset->explosiveForceScale = data["explosiveForceScale"].get<float>();
			asset->piecesSpreadFraction = data["piecesSpreadFraction"].get<float>();
			asset->piecesUpwardVelocity = data["piecesUpwardVelocity"].get<float>();

			const auto prefix = data["sndAliasPrefix"].get<std::string>();
			asset->sndAliasPrefix = mem->StrDup(prefix);

			if (data.contains("tempDefaultToCylinder"))
			{
				asset->tempDefaultToCylinder = data["tempDefaultToCylinder"].get<bool>();
			}

			return asset;
		}

		void IPhysPreset::init(const std::string& name, ZoneMemory* mem)
		{
			this->name_ = name;
			this->asset_ = this->parse(name, mem);

			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader(this->type(), this->name().data()).physpreset;
			}
		}

		void IPhysPreset::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		void IPhysPreset::load_depending(IZone* zone)
		{
		}

		std::string IPhysPreset::name()
		{
			return this->name_;
		}

		std::int32_t IPhysPreset::type()
		{
			return physpreset;
		}

		void IPhysPreset::write(IZone* zone, ZoneBuffer* buf)
		{
			auto* data = this->asset_;
			auto* dest = buf->write(data);
			
			buf->push_stream(3);

			dest->name = buf->write_str(this->name());

			if (data->sndAliasPrefix)
			{
				dest->sndAliasPrefix = buf->write_str(data->sndAliasPrefix);
			}

			buf->pop_stream();
		}

		void IPhysPreset::dump(PhysPreset* asset)
		{
			if (!asset || !asset->name)
			{
				return;
			}

			auto* file = FileSystem::FileOpen("physpreset\\"s + asset->name + ".json"s, "wb");
			if (!file)
			{
				return;
			}

			nlohmann::json data;

			data["name"] = asset->name;
			data["type"] = asset->type;
			data["mass"] = asset->mass;
			data["bounce"] = asset->bounce;
			data["friction"] = asset->friction;
			data["bulletForceScale"] = asset->bulletForceScale;
			data["explosiveForceScale"] = asset->explosiveForceScale;
			data["sndAliasPrefix"] = asset->sndAliasPrefix ? asset->sndAliasPrefix : "";
			data["piecesSpreadFraction"] = asset->piecesSpreadFraction;
			data["piecesUpwardVelocity"] = asset->piecesUpwardVelocity;
			data["tempDefaultToCylinder"] = asset->tempDefaultToCylinder;

			const auto assetData = data.dump(4);

			fwrite(assetData.data(), assetData.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}
