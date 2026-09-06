#include "stdafx.hpp"

namespace ZoneTool
{
	namespace T4
	{
		void IPhysPreset::dump(PhysPreset* asset, ZoneMemory* mem)
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

			nlohmann::json presetdata;

			presetdata["name"] = asset->name;
			presetdata["type"] = asset->type;
			presetdata["mass"] = asset->mass;
			presetdata["bounce"] = asset->bounce;
			presetdata["friction"] = asset->friction;
			presetdata["bulletForceScale"] = asset->bulletForceScale;
			presetdata["explosiveForceScale"] = asset->explosiveForceScale;
			presetdata["sndAliasPrefix"] = asset->sndAliasPrefix ? asset->sndAliasPrefix : "";
			presetdata["piecesSpreadFraction"] = asset->piecesSpreadFraction;
			presetdata["piecesUpwardVelocity"] = asset->piecesUpwardVelocity;
			presetdata["canFloat"] = asset->canFloat;
			presetdata["gravityScale"] = asset->gravityScale;

			const auto assetData = presetdata.dump(4);

			fwrite(assetData.data(), assetData.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}
