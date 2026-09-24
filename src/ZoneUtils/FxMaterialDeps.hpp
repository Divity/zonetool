#pragma once

#include <string>
#include <unordered_set>

namespace ZoneTool
{
	template <typename TFxEffectDef, typename TMaterial>
	void dump_fx_materials_first(TFxEffectDef* asset, int last_material_elem_type, int decal_elem_type, void (*dump_material)(TMaterial*))
	{
		static std::unordered_set<std::string> dumped;
		const auto dump = [&](TMaterial* material)
		{
			if (material && material->name && dumped.emplace(material->name).second)
			{
				dump_material(material);
			}
		};

		const auto elem_count = asset->elemDefCountLooping + asset->elemDefCountOneShot + asset->elemDefCountEmission;
		for (auto i = 0; i < elem_count; i++)
		{
			const auto* elem = &asset->elemDefs[i];
			if (!elem->visualCount)
			{
				continue;
			}

			const auto type = static_cast<int>(elem->elemType);
			if (type == decal_elem_type)
			{
				for (auto j = 0; elem->visuals.markArray && j < elem->visualCount; j++)
				{
					dump(elem->visuals.markArray[j].materials[0]);
					dump(elem->visuals.markArray[j].materials[1]);
				}
			}
			else if (type <= last_material_elem_type)
			{
				for (auto j = 0; j < elem->visualCount; j++)
				{
					dump(elem->visualCount > 1 ? elem->visuals.array[j].material : elem->visuals.instance.material);
				}
			}
		}
	}
}
