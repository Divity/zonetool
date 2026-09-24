#include "stdafx.hpp"

#include "Vision.hpp"

#include <filesystem>
#include <fstream>

namespace ZoneTool::IW5::IW7Dumper
{
	namespace
	{
		struct vision_key
		{
			const char* key;
			const char* value;
		};

		const vision_key iw7_schema[] =
		{
			{"colorizationSetCurveLowMin", "0"},
			{"colorizationSetCurveLowMax", "1"},
			{"colorizationSetCurveHighMin", "1"},
			{"colorizationSetCurveHighMax", "0"},
			{"colorizationSetCurveMidMidpoint", "0.5"},
			{"colorizationSetCurveMidRange", "0"},
			{"colorizationSetCurveMidFalloff", "0.5"},
			{"lmhLowScale", "1 1 1"},
			{"lmhLowBalance", "0 0 0"},
			{"lmhLowSaturation", "0"},
			{"lmhMidScale", "1 1 1"},
			{"lmhMidBalance", "0 0 0"},
			{"lmhMidSaturation", "0"},
			{"lmhHighScale", "1 1 1"},
			{"lmhHighBalance", "0 0 0"},
			{"lmhHighSaturation", "0"},
			{"lmhBalancePreserveLum", "1"},
			{"levelsInMin", "0"},
			{"levelsInGamma", "1"},
			{"levelsInMax", "255"},
			{"levelsOutMin", "0"},
			{"levelsOutMax", "255"},
			{"r_primaryLightTweakDiffuseStrength", "1"},
			{"r_primaryLightTweakSpecularStrength", "1"},
			{"r_charLightAmbient", "1 1 1"},
			{"r_volumeLightScatter", "0"},
			{"r_volumeLightScatterLinearAtten", "1"},
			{"r_volumeLightScatterQuadraticAtten", "0"},
			{"r_volumeLightScatterAngularAtten", "0.25"},
			{"r_volumeLightScatterDepthAttenNear", "0"},
			{"r_volumeLightScatterDepthAttenFar", "0"},
			{"r_volumeLightScatterBackgroundDistance", "100000"},
			{"r_volumeLightScatterColor", "0.2 0.2 0.2"},
			{"r_ssaoStrength", "1"},
			{"r_mdaoCullDistance", "1000"},
			{"r_mdaoFadeoutDistance", "900"},
			{"r_mdaoBoneSizeThreshold", "150"},
			{"r_glare_normalStart", "0.125"},
			{"r_glare_normalEnd", "0.75"},
			{"r_glare_normalPower", "1"},
			{"r_glare_normalAmount", "0"},
			{"r_glare_mirrorStart", "0.125"},
			{"r_glare_mirrorEnd", "0.75"},
			{"r_glare_mirrorPower", "1"},
			{"r_glare_mirrorAmount", "0"},
			{"r_rimLightScale", "8"},
			{"r_rimLightStartDistance", "100"},
			{"r_rimLightDistance", "900"},
			{"r_rimLightFill", "2"},
			{"r_EVCompBounds", "0"},
			{"r_EVCompGrayReference", "0.18"},
			{"r_hdrSkyIntensity", "1"},
			{"r_hdrSkyColorTint", "1 1 1"},
			{"r_skyBlendAmount", "0"},
			{"r_skyBlendFeather", "0.001"},
			{"fogDensity", "50000"},
			{"fogStartDist", "0"},
			{"fogColorIntensity", "1"},
			{"fogColor", "1 1 1"},
			{"fogMaxOpacity", "0"},
			{"fogSunDensity", "50000"},
			{"fogSunColorIntensity", "0"},
			{"fogSunColor", "1 1 1"},
			{"fogSunBeginFadeAngle", "0"},
			{"fogSunEndFadeAngle", "55"},
			{"fogSunDir", "0 0 -1"},
			{"fogSkyIntensity", "0"},
			{"fogSkyMinAngle", "0"},
			{"fogSkyMaxAngle", "90"},
			{"tonemapMode", "2"},
			{"tonemapAuto", "1"},
			{"tonemapAutoExposureAdjustCurve", "0"},
			{"tonemapExposure", "10"},
			{"tonemapAutoExposureAdjust", "0"},
			{"tonemapMaxExposure", "9.75"},
			{"tonemapExposureAdjust", "-0.5"},
			{"tonemapAdaptSpeed", "0.05"},
			{"tonemapBlackPoint", "0"},
			{"tonemapWhitePoint", "512.0"},
			{"tonemapCrossover", "2"},
			{"tonemapShoulder", "0.96"},
			{"tonemapToe", "0"},
			{"tonemapDarkEv", "2.84"},
			{"tonemapMidEv", "7.823"},
			{"tonemapLightEv", "12.81"},
			{"tonemapDarkExposureAdjust", "-3.17"},
			{"tonemapMidExposureAdjust", "-0.651"},
			{"tonemapLightExposureAdjust", "1.47"},
			{"tonemapMinExposureAdjust", "-3.17"},
			{"tonemapMaxExposureAdjust", "2.3"},
			{"tonemapGrainStrength", "0.07"},
			{"chromaRadius", "0"},
			{"chromaStrength", "0"},
			{"chromaAberration", "0"},
			{"r_dustHeading", "0"},
			{"r_dustPitch", "-90"},
			{"r_dustTiling", "0.1"},
			{"r_dustIntensity", "0"},
			{"r_dustPowerCurv", "1"},
			{"r_dustSmoothMin", "0.5"},
			{"r_dustSmoothMax", "1"},
			{"analogRewindAmount", "0"},
			{"analogInterferenceAmount", "0"},
			{"analogCrtEffectAmount", "0"},
			{"analogRollEffectAmount", "0"},
			{"analogChromaSeparationEffectAmount", "0"},
			{"toneWhitePoint", "1 1 1"},
			{"veilStrength", "0.06"},
			{"volumetricAirDensity", "0.02"},
			{"volumetricAbsorption", "0"},
			{"volumetricAlbedo", "1 1 1"},
			{"volumetricSunBrightness", "0"},
			{"volumetricSpotBrightness", "0"},
			{"volumetricAmbientBrightness", "0"},
			{"volumetricSunAnisotropy", "0.8"},
			{"sunshadowTransmissiveTint", "0 0 0"},
			{"sunshadowSoftness", "0"},
			{"sunshadowSampleSizeNear", "0.99"},
			{"cloudShadowScale", "1"},
			{"cloudShadowScrollRate", "0"},
			{"cloudShadowScrollHeading", "0"},
			{"cloudShadowOpacity", "0"},
			{"cloudShadowLowThreshold", "0"},
			{"cloudShadowHighThreshold", "1"},
		};

		using key_values = std::vector<std::pair<std::string, std::string>>;

		bool same_key(const std::string& a, const char* b)
		{
			return _stricmp(a.data(), b) == 0;
		}

		key_values parse(const std::string& text)
		{
			key_values out;
			std::size_t pos = 0;
			while (pos < text.size())
			{
				auto end = text.find('\n', pos);
				if (end == std::string::npos)
				{
					end = text.size();
				}
				auto line = text.substr(pos, end - pos);
				pos = end + 1;

				if (!line.empty() && line.back() == '\r')
				{
					line.pop_back();
				}

				auto i = line.find_first_not_of(" \t");
				if (i == std::string::npos || line.compare(i, 2, "//") == 0)
				{
					continue;
				}

				const auto key_end = line.find_first_of(" \t", i);
				if (key_end == std::string::npos)
				{
					continue;
				}
				const auto key = line.substr(i, key_end - i);

				i = line.find_first_not_of(" \t", key_end);
				if (i == std::string::npos)
				{
					continue;
				}

				std::string value;
				if (line[i] == '"')
				{
					const auto close = line.find('"', i + 1);
					value = line.substr(i + 1, close == std::string::npos ? std::string::npos : close - i - 1);
				}
				else
				{
					const auto value_end = line.find_first_of(" \t", i);
					value = line.substr(i, value_end == std::string::npos ? std::string::npos : value_end - i);
				}

				out.emplace_back(key, value);
			}
			return out;
		}

		const std::string* find(const key_values& values, const char* key)
		{
			for (const auto& [k, v] : values)
			{
				if (same_key(k, key))
				{
					return &v;
				}
			}
			return nullptr;
		}

		void set(key_values& values, const char* key, const std::string& value)
		{
			for (auto& [k, v] : values)
			{
				if (same_key(k, key))
				{
					v = value;
					return;
				}
			}
		}

		float to_float(const std::string& s, float fallback)
		{
			char* end = nullptr;
			const auto f = std::strtof(s.data(), &end);
			return end == s.data() ? fallback : f;
		}

		std::string saturation_from_desaturation(const std::string& desaturation)
		{
			return va("%g", std::clamp(-100.0f * to_float(desaturation, 0.0f), -100.0f, 100.0f));
		}

		void map_film(const key_values& src, key_values& out)
		{
			const auto* enable = find(src, "r_filmEnable");
			if (!enable || to_float(*enable, 0.0f) == 0.0f)
			{
				return;
			}

			if (const auto* tint = find(src, "r_filmDarkTint"))
			{
				set(out, "lmhLowScale", *tint);
			}
			if (const auto* tint = find(src, "r_filmMediumTint"))
			{
				set(out, "lmhMidScale", *tint);
			}
			if (const auto* tint = find(src, "r_filmLightTint"))
			{
				set(out, "lmhHighScale", *tint);
			}

			if (const auto* desaturation = find(src, "r_filmDesaturation"))
			{
				const auto saturation = saturation_from_desaturation(*desaturation);
				set(out, "lmhLowSaturation", saturation);
				set(out, "lmhMidSaturation", saturation);
				set(out, "lmhHighSaturation", saturation);
			}
			if (const auto* desaturation = find(src, "r_filmDesaturationDark"))
			{
				set(out, "lmhLowSaturation", saturation_from_desaturation(*desaturation));
			}
		}

		bool in_schema(const std::string& key)
		{
			for (const auto& entry : iw7_schema)
			{
				if (same_key(key, entry.key))
				{
					return true;
				}
			}
			return false;
		}

		bool starts_with(const std::string& key, const char* prefix)
		{
			return _strnicmp(key.data(), prefix, std::strlen(prefix)) == 0;
		}

		void convert_vision(const std::filesystem::path& path)
		{
			std::string text;
			{
				std::ifstream in(path, std::ios::binary);
				if (!in)
				{
					return;
				}
				text.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
			}

			const auto src = parse(text);

			key_values out;
			out.reserve(std::size(iw7_schema));
			for (const auto& entry : iw7_schema)
			{
				out.emplace_back(entry.key, entry.value);
			}

			map_film(src, out);

			const auto* use_tweaks = find(src, "r_primaryLightUseTweaks");
			const auto tweaks_enabled = !use_tweaks || to_float(*use_tweaks, 1.0f) != 0.0f;

			std::string dropped;
			for (const auto& [key, value] : src)
			{
				if (in_schema(key))
				{
					if (tweaks_enabled || !starts_with(key, "r_primaryLightTweak"))
					{
						set(out, key.data(), value);
					}
				}
				else if (!starts_with(key, "r_film") && !same_key(key, "r_primaryLightUseTweaks"))
				{
					dropped += (dropped.empty() ? "" : ", ") + key;
				}
			}

			std::string result;
			for (const auto& [key, value] : out)
			{
				result += key + " \"" + value + "\"\r\n";
			}

			{
				std::ofstream file(path, std::ios::binary | std::ios::trunc);
				file.write(result.data(), static_cast<std::streamsize>(result.size()));
			}

			ZONETOOL_INFO("vision %s: %zu source keys -> %zu IW7 keys%s%s",
				path.filename().string().data(), src.size(), out.size(),
				dropped.empty() ? "" : "; dropped: ", dropped.data());
		}
	}

	void convert_visions(const std::string& zone)
	{
		if (zonetool::dumping_target != zonetool::dump_target::iw7)
		{
			return;
		}

		const auto dir = std::filesystem::path("dump") / zone / "vision";
		std::error_code ec;
		if (!std::filesystem::is_directory(dir, ec))
		{
			return;
		}

		for (const auto& entry : std::filesystem::directory_iterator(dir, ec))
		{
			if (entry.is_regular_file() && _stricmp(entry.path().extension().string().data(), ".vision") == 0)
			{
				convert_vision(entry.path());
			}
		}
	}
}
