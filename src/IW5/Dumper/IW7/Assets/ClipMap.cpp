#include "stdafx.hpp"

#include "ClipMap.hpp"
#include "Converter/IW7/Assets/ClipMap.hpp"
#include "IW7/Assets/ClipMap.hpp"
#include "IW7/Assets/MapEnts.hpp"
#include "IW7/Assets/PhysicsAsset.hpp"
#include "IW7/Assets/ScriptableDef.hpp"

#include <algorithm>

namespace ZoneTool::IW5::IW7Dumper
{
	void dump(clipMap_t* asset)
	{
		allocator allocator;

		auto* iw7_asset = IW7Converter::convert(asset, allocator);

		// dump iw7 clipmap
		IW7::IClipMap::dump(iw7_asset);

		for (const auto* ncs : {
			"ncs_acl_level", "ncs_anm_level", "ncs_efx_level", "ncs_ges_level",
			"ncs_hic_level", "ncs_hnt_level", "ncs_loc_level", "ncs_lui_level",
			"ncs_mat_level", "ncs_mdl_level", "ncs_mic_level", "ncs_nps_level",
			"ncs_rmb_level", "ncs_rmg_level", "ncs_shk_level", "ncs_sic_level",
			"ncs_sut_level", "ncs_tag_level", "ncs_tgt_level", "ncs_veh_level",
			"ncs_vfx_level", "ncs_vsn_level", "ncs_wep_level" })
		{
			zonetool::filesystem::csv_buffer_line("netconststrings", ncs);
		}

		auto* iw7_mapents = iw7_asset->mapEnts;
		if (!iw7_mapents)
		{
			return;
		}

		// dump iw7 mapents
		IW7::IMapEnts::dump(iw7_mapents);

		// dump spawns
		mapents2spawns::dump_spawns(filesystem::get_dump_path() + asset->name + ".ents.spawnList.json"s, 
			iw7_mapents->entityString);

		std::vector<IW7::PhysicsAsset*> dumped;
		const auto dump_physics = [&](IW7::PhysicsAsset* physics)
		{
			if (!physics || std::find(dumped.begin(), dumped.end(), physics) != dumped.end())
			{
				return;
			}

			dumped.emplace_back(physics);
			IW7::IPhysicsAsset::dump(physics);
		};

		for (unsigned int i = 0; i < iw7_mapents->numSubModels; i++)
		{
			dump_physics(iw7_mapents->cmodels[i].physicsAsset);
		}

		for (unsigned int i = 0; i < iw7_mapents->trigger.count; i++)
		{
			dump_physics(iw7_mapents->trigger.models[i].physicsAsset);
		}

		for (unsigned int i = 0; i < iw7_mapents->scriptableMapEnts.totalInstanceCount; i++)
		{
			if (iw7_mapents->scriptableMapEnts.instances[i].contextHeader.context.def)
			{
				IW7::IScriptableDef::dump(iw7_mapents->scriptableMapEnts.instances[i].contextHeader.context.def);
			}
		}
	}
}
