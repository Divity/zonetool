#include "stdafx.hpp"
#include "../IW4/Assets/Material.hpp"

#include <unordered_set>

namespace ZoneTool
{
	namespace T4
	{
		namespace
		{
			std::string clean_material_name(const std::string& name)
			{
				return IW4::IMaterial::clean_name(name);
			}

			const std::unordered_map<unsigned char, unsigned char> sortkey_map =
			{
				{0, 43}, {1, 1}, {2, 1}, {3, 0}, {4, 1}, {5, 2},
				{6, 3}, {7, 3}, {8, 3},
				{9, 6}, {10, 7}, {11, 8}, {12, 9},
				{13, 10}, {14, 11}, {15, 12},
				{16, 47}, {17, 47},
				{24, 13},
				{29, 12}, {30, 12}, {31, 12},
				{32, 47}, {33, 47}, {34, 1}, {35, 47}, {36, 47}, {37, 47},
				{38, 24}, {39, 25},
				{40, 47}, {41, 47}, {42, 47}, {43, 47},
				{48, 48},
				{56, 49}, {57, 50}, {58, 51}, {59, 53},
			};

			const std::unordered_set<unsigned char> unlit_only_sortkeys =
			{
				34, 43, 47, 48, 49, 50, 51, 53
			};

			constexpr auto SORTKEY_LIT_TRANSLUCENT = 33;

			bool techset_starts_with(const std::string& name, const std::string& prefix)
			{
				return name.compare(0, prefix.size(), prefix) == 0;
			}

			unsigned char compute_sortkey(const Material* mat)
			{
				const std::string techset = (mat->techniqueSet && mat->techniqueSet->name)
					                            ? mat->techniqueSet->name
					                            : "";

				unsigned char key;

				if (techset == "2d" || techset_starts_with(techset, "2d_"))
				{
					key = 47;
				}
				else if (techset.find("shadowcaster") != std::string::npos ||
					techset.find("tools") != std::string::npos)
				{
					key = 34;
				}
				else if (techset_starts_with(techset, "distortion"))
				{
					key = 43;
				}
				else if (techset_starts_with(techset, "effect"))
				{
					key = 48;
				}
				else if (techset_starts_with(techset, "particle_cloud"))
				{
					key = 47;
				}
				else if (techset.find("ambient") != std::string::npos)
				{
					key = 0;
				}
				else if (techset.find("sky") != std::string::npos)
				{
					key = 2;
				}
				else
				{
					const auto itr = sortkey_map.find(mat->info.sortKey);
					if (itr == sortkey_map.end())
					{
						ZONETOOL_WARNING("[%s]: sortKey %u is not mapped!", mat->info.name, mat->info.sortKey);
						return mat->info.sortKey;
					}
					key = itr->second;
				}

				const auto has_lit = mat->techniqueSet && mat->techniqueSet->techniques[TECHNIQUE_LIT];

				if (has_lit && unlit_only_sortkeys.count(key))
				{
					key = SORTKEY_LIT_TRANSLUCENT;
				}

				return key;
			}
		}

		unsigned char IMaterial::convert_sortkey(const Material* mat)
		{
			return compute_sortkey(mat);
		}

		void IMaterial::dump(Material* mat, ZoneMemory* mem)
		{
			if (!mat || !mat->info.name)
			{
				return;
			}

			const auto path = "materials\\"s + clean_material_name(mat->info.name);

			auto* file = FileSystem::FileOpen(path, "wb");
			if (!file)
			{
				return;
			}

			nlohmann::json matdata;

			matdata["name"] = std::string(mat->info.name);

			if (mat->techniqueSet && mat->techniqueSet->name)
			{
				const auto techset_name = "t4/"s + mat->techniqueSet->name;

				matdata["techniqueSet->name"] = techset_name;
				ITechset::dump_statebits(techset_name, mat->stateBitsEntry);
			}

			matdata["gameFlags"] = mat->info.gameFlags;
			matdata["animationX"] = mat->info.textureAtlasRowCount;
			matdata["animationY"] = mat->info.textureAtlasColumnCount;
			matdata["sortKey"] = compute_sortkey(mat);
			matdata["unknown"] = 0;
			matdata["surfaceTypeBits"] = mat->info.surfaceTypeBits;
			matdata["stateFlags"] = mat->stateFlags;
			matdata["cameraRegion"] = mat->cameraRegion;

			nlohmann::json constant_table;
			for (auto i = 0; i < mat->constantCount; i++)
			{
				nlohmann::json constant;

				std::string name = mat->constantTable[i].name;
				name.resize(12);

				constant["name"] = name.data();
				constant["nameHash"] = mat->constantTable[i].nameHash;
				constant["literal"][0] = mat->constantTable[i].literal.v[0];
				constant["literal"][1] = mat->constantTable[i].literal.v[1];
				constant["literal"][2] = mat->constantTable[i].literal.v[2];
				constant["literal"][3] = mat->constantTable[i].literal.v[3];

				constant_table[i] = constant;
			}
			matdata["constantTable"] = constant_table;

			nlohmann::json state_map;
			for (auto i = 0; i < mat->stateBitsCount; i++)
			{
				nlohmann::json entry;
				entry[0] = mat->stateBitsTable[i].loadBits.raw[0];
				entry[1] = mat->stateBitsTable[i].loadBits.raw[1];
				state_map[i] = entry;
			}
			matdata["stateMap"] = state_map;

			nlohmann::json material_images;
			for (auto i = 0; i < mat->textureCount; i++)
			{
				nlohmann::json image;

				auto& texture = mat->textureTable[i];

				if (texture.semantic == 11)
				{
					auto* waterData = texture.u.water;

					if (waterData && waterData->image)
					{
						image["image"] = waterData->image->name;
					}

					nlohmann::json waterdata;
					waterdata["floatTime"] = waterData->writable.floatTime;
					waterdata["codeConstant"][0] = waterData->codeConstant[0];
					waterdata["codeConstant"][1] = waterData->codeConstant[1];
					waterdata["codeConstant"][2] = waterData->codeConstant[2];
					waterdata["codeConstant"][3] = waterData->codeConstant[3];
					waterdata["M"] = waterData->M;
					waterdata["N"] = waterData->N;
					waterdata["Lx"] = waterData->Lx;
					waterdata["Lz"] = waterData->Lz;
					waterdata["gravity"] = waterData->gravity;
					waterdata["windvel"] = waterData->windvel;
					waterdata["winddir"][0] = waterData->winddir[0];
					waterdata["winddir"][1] = waterData->winddir[1];
					waterdata["amplitude"] = waterData->amplitude;

					nlohmann::json complexData;
					nlohmann::json wTerm;

					for (auto j = 0; j < waterData->M * waterData->N; j++)
					{
						complexData[j]["real"] = waterData->H0[j].real;
						complexData[j]["imag"] = waterData->H0[j].imag;
						wTerm[j] = waterData->wTerm[j];
					}

					waterdata["complex"] = complexData;
					waterdata["wTerm"] = wTerm;

					image["waterinfo"] = waterdata;
				}
				else if (texture.u.image && texture.u.image->name)
				{
					image["image"] = texture.u.image->name;
				}

				image["semantic"] = texture.semantic;
				image["sampleState"] = *reinterpret_cast<const unsigned char*>(&texture.samplerState);
				image["lastCharacter"] = texture.nameEnd;
				image["firstCharacter"] = texture.nameStart;
				image["typeHash"] = texture.nameHash;

				material_images[i] = image;
			}
			matdata["maps"] = material_images;

			const auto assetData = matdata.dump(4);

			fwrite(assetData.data(), assetData.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}
