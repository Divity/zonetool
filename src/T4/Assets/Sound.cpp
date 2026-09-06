#include "stdafx.hpp"
#include "../IW4/Assets/Sound.hpp"
#include "../IW4/Assets/SoundCurve.hpp"

#include <unordered_set>

namespace ZoneTool
{
	namespace T4
	{
		namespace
		{
			SndDriverGlobals* driver_globals = nullptr;

			SndDriverGlobals* sound_globals()
			{
				return driver_globals;
			}

			IW4::SndCurve* convert_curve(unsigned int index, ZoneMemory* mem)
			{
				auto* globals = sound_globals();
				if (!globals || index >= 32)
				{
					return nullptr;
				}

				auto& source = globals->curves[index];
				if (!source.name[0] || source.pointCount <= 0)
				{
					return nullptr;
				}

				auto* curve = mem->Alloc<IW4::SndCurve>();
				curve->filename = mem->StrDup(source.name);
				curve->knotCount = static_cast<unsigned short>(source.pointCount);

				const auto points = min(source.pointCount, 8);
				for (auto i = 0; i < points; i++)
				{
					curve->knots[i][0] = source.points[i][0];
					curve->knots[i][1] = source.points[i][1];
				}

				static std::unordered_set<std::string> dumped;
				if (dumped.insert(source.name).second)
				{
					IW4::ISoundCurve::dump(curve);
				}

				return curve;
			}

			void dump_driver_globals_table()
			{
				static bool dumped = false;
				if (dumped)
				{
					return;
				}
				dumped = true;

				auto* globals = sound_globals();
				if (!globals)
				{
					ZONETOOL_WARNING("SndDriverGlobals is not loaded; falloff curves and speaker maps cannot be resolved.");
					return;
				}

				nlohmann::json data;
				data["name"] = globals->name ? globals->name : "";

				for (auto i = 0; i < 32; i++)
				{
					auto& curve = globals->curves[i];
					if (!curve.name[0]) continue;

					nlohmann::json entry;
					entry["index"] = i;
					entry["name"] = std::string(curve.name, strnlen(curve.name, 32));
					entry["pointCount"] = curve.pointCount;
					for (auto p = 0; p < 8; p++)
					{
						entry["points"][p] = {curve.points[p][0], curve.points[p][1]};
					}
					data["curves"].push_back(entry);
				}

				for (auto i = 0; i < 32; i++)
				{
					auto& set = globals->speakerMaps[i];
					if (!set.name[0]) continue;

					nlohmann::json entry;
					entry["index"] = i;
					entry["name"] = std::string(set.name, strnlen(set.name, 32));

					for (auto m = 0; m < 4; m++)
					{
						nlohmann::json map;
						map["input_channel_count"] = set.channelMaps[m].input_channel_count;
						map["output_channel_count"] = set.channelMaps[m].output_channel_count;
						for (auto v = 0; v < 16; v++)
						{
							map["volumes"][v] = set.channelMaps[m].volumes[v];
						}
						entry["channelMaps"][m] = map;
					}
					data["speakerMaps"].push_back(entry);
				}

				auto* file = FileSystem::FileOpen("sound\\snddriverglobals.json"s, "wb");
				if (file)
				{
					const auto json = data.dump(4);
					fwrite(json.data(), json.size(), 1, file);
					FileSystem::FileClose(file);
					ZONETOOL_INFO("Dumped SndDriverGlobals curve/speakermap tables.");
				}
			}

			IW4::SpeakerMap* convert_speaker_map(unsigned int index, ZoneMemory* mem)
			{
				auto* globals = sound_globals();
				if (!globals || index >= 32)
				{
					return nullptr;
				}

				auto& source = globals->speakerMaps[index];
				if (!source.name[0])
				{
					return nullptr;
				}

				auto* map = mem->Alloc<IW4::SpeakerMap>();
				map->name = mem->StrDup(source.name);
				map->isDefault = !strcmp(source.name, "default");

				for (auto m = 0; m < 4; m++)
				{
					auto& src = source.channelMaps[m];
					auto& dst = map->channelMaps[m / 2][m % 2];

					const auto outputs = min(src.output_channel_count, 6);
					const auto inputs = min(src.input_channel_count, 2);

					dst.entryCount = outputs;

					for (auto speaker = 0; speaker < outputs; speaker++)
					{
						dst.speakers[speaker].speaker = speaker;
						dst.speakers[speaker].numLevels = inputs;

						for (auto channel = 0; channel < inputs; channel++)
						{
							dst.speakers[speaker].levels[channel] =
								src.volumes[channel * src.output_channel_count + speaker];
						}
					}
				}

				return map;
			}

			IW4::SoundFile* convert_sound_file(SoundFile* source, ZoneMemory* mem)
			{
				if (!source)
				{
					return nullptr;
				}

				auto* file = mem->Alloc<IW4::SoundFile>();
				file->type = source->type;
				file->exists = source->exists;

				if (source->type == SAT_LOADED)
				{
					if (source->u.loadSnd && source->u.loadSnd->name)
					{
						auto* loaded = mem->Alloc<IW4::LoadedSound>();
						loaded->name = source->u.loadSnd->name;
						file->sound.loadSnd = loaded;
					}
				}
				else
				{
					auto* streamed = mem->Alloc<IW4::StreamedSound>();
					streamed->dir = source->u.streamSnd.filename.dir;
					streamed->name = source->u.streamSnd.filename.name;
					file->sound.streamSnd = *streamed;
				}

				return file;
			}
		}

		void ISound::set_driver_globals(SndDriverGlobals* globals)
		{
			if (!globals || driver_globals)
			{
				return;
			}

			driver_globals = globals;

			ZONETOOL_INFO("Captured snddriverglobals \"%s\".", globals->name ? globals->name : "<unnamed>");
		}

		void ISound::dump(snd_alias_list_t* asset, ZoneMemory* mem)
		{
			if (!asset || !asset->aliasName)
			{
				return;
			}

			dump_driver_globals_table();

			auto* iw4_sound = mem->Alloc<IW4::snd_alias_list_t>();
			iw4_sound->name = asset->aliasName;
			iw4_sound->count = asset->count;
			iw4_sound->head = mem->Alloc<IW4::snd_alias_t>(asset->count);

			for (auto i = 0; asset->head && i < asset->count; i++)
			{
				auto* source = &asset->head[i];
				auto* alias = &iw4_sound->head[i];

				alias->aliasName = source->aliasName;
				alias->subtitle = source->subtitle;
				alias->secondaryAliasName = source->secondaryAliasName;
				alias->chainAliasName = source->chainAliasName;
				alias->mixerGroup = nullptr;
				alias->soundFile = convert_sound_file(source->soundFile, mem);
				alias->sequence = source->sequence;
				alias->volMin = source->volMin;
				alias->volMax = source->volMax;
				alias->pitchMin = source->pitchMin;
				alias->pitchMax = source->pitchMax;
				alias->distMin = source->distMin;
				alias->distMax = source->distMax;
				alias->velocityMin = 0.0f;
				alias->flags = source->flags;
				alias->___u15.slavePercentage = source->slavePercentage;
				alias->probability = source->probability;
				alias->lfePercentage = source->lfePercentage;
				alias->centerPercentage = source->centerPercentage;
				alias->startDelay = static_cast<int>(source->startDelay);
				alias->volumeFalloffCurve = convert_curve(source->volumeFalloffCurve, mem);
				alias->envelopMin = source->envelopMin;
				alias->envelopMax = source->envelopMax;
				alias->envelopPercentage = source->envelopPercentage;
				alias->speakerMap = convert_speaker_map(source->speakerMap, mem);
			}

			IW4::ISound::dump(iw4_sound);
		}
	}
}
