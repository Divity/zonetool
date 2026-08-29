// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
// #include "ZoneTool.hpp"

namespace ZoneTool
{
	namespace T4
	{
		bool isDumping = false;
		bool isVerifying = false;
		auto currentDumpingZone = ""s;



		FILE* csvFile;

		Linker::Linker()
		{
		}

		Linker::~Linker()
		{
		}

		const char* Linker::version()
		{
			return "WaW";
		}
		bool Linker::is_used()
		{
			return !strncmp(reinterpret_cast<const char*>(0x00859B58) + 4, this->version(), 3);
		}

		typedef void * (__cdecl* Dvar_RegisterBool_t)(const char*, bool, unsigned int, const char*);
		Dvar_RegisterBool_t Dvar_RegisterBool = (Dvar_RegisterBool_t)0x5C5190; //Updated for T4

		void* Linker::Dedicated_RegisterDvarBool(const char* name, bool defaultValue, unsigned int flags,
			const char* description)
		{
			return Dvar_RegisterBool(name, true, 0x2000, description);
		}

		void** DB_XAssetPool = (void**)0x8D0958;
		unsigned int* g_poolSize = (unsigned int*)0x8D06E8;

		void* DB_FindXAssetHeader_Unsafe(const XAssetType type, const std::string& name)
		{
			const static auto DB_FindXAssetHeader_Internal = 0x4B9CA0; //Updated for T4
			const auto name_ptr = name.data();
			const auto type_int = static_cast<std::int32_t>(type);

			const XAsset* asset_header = nullptr;

			__asm
			{
				mov edi, name_ptr;
				push type_int;
				call DB_FindXAssetHeader_Internal;
				add esp, 4;
				mov asset_header, eax;
			}

			return (asset_header) ? asset_header->ptr.data : nullptr;
		}

		void* Linker::DB_AddXAsset(XAsset* asset, int unk)
		{
			auto result =
				Memory::func<void* (XAsset*, int)>(0x004BA530)(asset, unk);

			if (result)
			{
				auto* resultAsset = reinterpret_cast<XAsset*>(result);

				if (!unk)
				{
					HandleAsset(resultAsset);
				}
			}

			return result;
		}

		const char* Linker::GetAssetName(XAsset* asset)
		{
			// todo
			if (asset->type == image)
			{
				return asset->ptr.image->name;
			}
			if (asset->type == menu)
			{
				// return asset->ptr.menu->name;
			}
			else
			{
				return asset->ptr.rawfile->name;
			}

			return "";
		}

		void Linker::HandleAsset(XAsset* asset)
		{
			static std::shared_ptr<ZoneMemory> memory;
			static std::vector<std::pair<XAssetType, std::string>> referencedAssets;

			if (!memory)
			{
				memory = std::make_shared<ZoneMemory>(1024 * 1024 * 128); // 128 MB
			}

			if (!asset)
				return;

			auto xassettypes = reinterpret_cast<char**>(0x008D0B98);

			const char* typeName = "<UNKNOWN>";

			if (asset->type >= 0 && asset->type < max)
			{
				typeName = xassettypes[asset->type];
			}

			const char* assetName = GetAssetName(asset);

			ZONETOOL_INFO("Loading asset \"%s\" of type %s.", Linker::GetAssetName(asset), reinterpret_cast<char**>(
				0x008D0B98)[asset->type]);

			if (!isDumping)
				return;

			// T4 fastfile name
			auto fastfile = static_cast<std::string>(
				*(const char**)0x116936C
				);

			FileSystem::SetFastFile(fastfile);

			// Open CSV once
			if (!csvFile)
			{
				const auto csvName = FileSystem::GetFastFile() + ".csv";

				csvFile = FileSystem::FileOpen(csvName, "wb");

				if (!csvFile)
				{
					ZONETOOL_ERROR(
						"Could not open CSV file \"%s\"!",
						csvName.data()
					);

					return;
				}

				for (auto& ref : referencedAssets)
				{
					if (ref.second.length() <= 1 || ref.first == XAssetType::loaded_sound)
					{
						continue;
					}

					const auto asset_name = &ref.second[1];
					const auto ref_asset = DB_FindXAssetHeader_Unsafe(ref.first, asset_name);

					if (ref_asset == nullptr)
					{
						ZONETOOL_ERROR("Could not find referenced asset \"%s\"!", asset_name);
						continue;
					}

					XAsset asset;
					asset.type = ref.first;
					asset.ptr.data = ref_asset;

					ZONETOOL_INFO("Dumping additional asset \"%s\" because it is referenced by %s.", asset_name, currentDumpingZone.data());

					HandleAsset(&asset);
				}
			}

			// Write EVERY asset
			fprintf(
				csvFile,
				"%s,%s\n",
				typeName,
				assetName
			);

			fflush(csvFile);

			if (GetAssetName(asset)[0] == ',')
			{
				referencedAssets.push_back({ asset->type, GetAssetName(asset) });
			}
			else
			{
#define DECLARE_ASSET(__TYPE__, __ASSET__) \
if (asset->type == __TYPE__) \
{ \
	__ASSET__::dump(asset->ptr.__TYPE__, memory.get()); \
}
				try
				{
					if (asset->type == image)
					{
						ZONETOOL_INFO(
							"IMAGE: %s, mapType=%d",
							GetAssetName(asset),
							asset->ptr.image->mapType
						);
					}
					DECLARE_ASSET(xmodel, IXModel);
					//DECLARE_ASSET(material, IMaterial);
					DECLARE_ASSET(xanim, IXAnimParts);
					//DECLARE_ASSET(techset, ITechset);
					//DECLARE_ASSET(loaded_sound, ILoadedSound);
					//DECLARE_ASSET(sound, ISound);
					//DECLARE_ASSET(fx, IFxEffectDef);
					//DECLARE_ASSET(font, IFontDef);
					//DECLARE_ASSET(gfx_map, IGfxWorld);
					//DECLARE_ASSET(col_map_mp, IClipMap);
					DECLARE_ASSET(map_ents, IMapEnts);
					DECLARE_ASSET(com_map, IComWorld);
					DECLARE_ASSET(game_map_mp, IGameWorldMp);
					DECLARE_ASSET(game_map_sp, IGameWorldSp);
					//DECLARE_ASSET(weapon, IWeaponDef);
					DECLARE_ASSET(rawfile, IRawFile);
					//DECLARE_ASSET(image, IGfxImage);
				}
				catch (std::exception& ex)
				{
					ZONETOOL_FATAL("A fatal exception occured while dumping asset \"%s\", exception was: %s\n", GetAssetName(asset), ex.what());
				}
			}
		}

		void* ReallocateAssetPool(uint32_t type, unsigned int newSize)
		{
			int elSize = DB_GetXAssetSizeHandlers[type]();

			void* poolEntry = malloc(newSize * elSize);
			DB_XAssetPool[type] = poolEntry;
			g_poolSize[type] = newSize;

			return poolEntry;
		}

		void* ReallocateAssetPoolM(uint32_t type, int multiplier)
		{
			int elSize = DB_GetXAssetSizeHandlers[type]();
			int newSize = multiplier * g_poolSize[type];

			void* poolEntry = malloc(newSize * elSize);
			DB_XAssetPool[type] = poolEntry;
			g_poolSize[type] = newSize;

			return poolEntry;
		}

		void Com_PrintfHook(int channel, const char* data, int unk)
		{
			printf(data);
		}

		const unsigned int textureBufferSize = 1024 * 1024 * 32; // 32mb
		unsigned int textureBufferIndex = 0;
		std::unordered_map<std::string, unsigned int> textureMap;
		std::string texturesFastfiles;

		char* GetTextureBuffer()
		{
			static char textureBuffer[textureBufferSize];
			return textureBuffer;
		}

		void ClearTextures()
		{
			// Fastfile name pointer from your earlier T4 code
			auto fastfile = static_cast<std::string>(*(const char**)0x116936C);

			if (fastfile != texturesFastfiles)
			{
				auto* buffer = GetTextureBuffer();
				std::memset(buffer, 0, textureBufferSize);
				textureBufferIndex = 0;
				textureMap.clear();
				texturesFastfiles = fastfile;
			}
		}

		void StoreTexture()
		{
			GfxImage* image = *reinterpret_cast<GfxImage**>(0x1169598);
			if (!image || !image->name)
				return;

			// At this point image->texture.loadDef should already be valid
			GfxImageLoadDef* loadDef = image->texture.loadDef;
			if (!loadDef)
				return;

			ClearTextures();

			auto* buffer = GetTextureBuffer();

			if (textureMap.contains(image->name))   // or textureMap.find(...) != end()
			{
				image->texture.loadDef = reinterpret_cast<GfxImageLoadDef*>(&buffer[textureMap[image->name]]);
				return;
			}

			const size_t size = 16 + loadDef->resourceSize;

			if (textureBufferIndex + size >= textureBufferSize)
			{
				ZONETOOL_FATAL("T4 Texture Buffer exceeded on %s", image->name);
			}

			void* dst = &buffer[textureBufferIndex];
			textureMap[image->name] = textureBufferIndex;
			textureBufferIndex += static_cast<unsigned int>(size);

			std::memcpy(dst, loadDef, size);
			image->texture.loadDef = reinterpret_cast<GfxImageLoadDef*>(dst);

			ZONETOOL_INFO("Stored texture %s (size = %zu)", image->name, size);
		}

		void Linker::startup()
		{
			if (this->is_used())
			{
				// Realloc asset pools
				ReallocateAssetPoolM(localize, 2);
				ReallocateAssetPoolM(material, 2);
				ReallocateAssetPoolM(font, 2);
				ReallocateAssetPoolM(image, 2);
				ReallocateAssetPoolM(techset, 2);
				ReallocateAssetPoolM(fx, 4);
				ReallocateAssetPoolM(xanim, 2);
				ReallocateAssetPoolM(xmodel, 2);
				ReallocateAssetPoolM(physpreset, 2);
				ReallocateAssetPoolM(weapon, 2);
				ReallocateAssetPoolM(game_map_sp, 2);
				ReallocateAssetPoolM(game_map_mp, 2);
				ReallocateAssetPoolM(map_ents, 5);
				ReallocateAssetPoolM(com_map, 5);
				ReallocateAssetPoolM(col_map_mp, 5);
				ReallocateAssetPoolM(gfx_map, 5);
				ReallocateAssetPoolM(rawfile, 2);
				ReallocateAssetPoolM(loaded_sound, 2);
				ReallocateAssetPoolM(sound, 2);
				ReallocateAssetPoolM(stringtable, 2);

				// Asset dump hook
				Memory(0x004BA892).call(DB_AddXAsset); //Updated for T4

				// Always use dedicated mode
				Memory(0x566117).call(Dedicated_RegisterDvarBool);
				Memory(0x564D98).call(Dedicated_RegisterDvarBool); //Updated for T4
				Memory(0x564DBE).call(Dedicated_RegisterDvarBool); //Updated for T4
				Memory(0x564D98).call(Dedicated_RegisterDvarBool); //Updated for T4

				// Store image data
				Memory(0x6E234A).nop(3); //Updated for T4
				//Memory(0x6E2330).call(StoreTexture);

				// idc if you can't initialise PunkBuster
				Memory(0x5D08C1).nop(5); //Updated for T4
				Memory(0x5D08CB).nop(5); //Updated for T4

				// Initialise console_mp.log
				Memory(0x562478).nop(2); //Updated for T4

				// We don't need recommended settings
				//Memory(0x46E8E3).set<std::uint8_t>(0xEB); //Address needs updating
				//Memory(0x4FE993).nop(7); //Address needs updating

				// We do not need to load the config_mp.cfg
				Memory(0x55C790).set<std::uint8_t>(0xEB); //Updated for T4

				// Don't give a frametime warning
				Memory(0x566081).nop(5); //Updated for T4

				// No huffmann message
				Memory(0x56E592).nop(5); //Updated for T4

				// Disable console window
				Memory(0x00499F6E).nop(5); //Updated for T4

				// Obtain console output from T4
				Memory(0x5624D0).call(Com_PrintfHook); //Updated for T4
			}
		}

		std::shared_ptr<IZone> Linker::alloc_zone(const std::string& zone)
		{
			ZONETOOL_ERROR("AllocZone called but T4 is not intended to compile zones!");
			return nullptr;
		}

		std::shared_ptr<ZoneBuffer> Linker::alloc_buffer()
		{
			ZONETOOL_ERROR("AllocBuffer called but T4 is not intended to compile zones!");
			return nullptr;
		}

		void Linker::load_zone(const std::string& name)
		{
			static XZoneInfo zone;
			zone.zone = _strdup(&name[0]);
			zone.loadFlags = 0;
			zone.unloadFlags = 0;

			Memory::func<void(XZoneInfo*, int, int)>(0x4BAD70)(&zone, 1, 0); //Updated for T4
		}

		void Linker::unload_zones()
		{
		}

		bool Linker::is_valid_asset_type(const std::string& type)
		{
			return this->type_to_int(type) >= 0;
		}

		std::int32_t Linker::type_to_int(std::string type)
		{
			auto xassettypes = reinterpret_cast<char**>(0x008D0B98); //Updated for T4

			for (std::int32_t i = 0; i < max; i++)
			{
				if (xassettypes[i] == type)
					return i;
			}

			return -1;
		}

		std::string Linker::type_to_string(std::int32_t type)
		{
			auto xassettypes = reinterpret_cast<char**>(0x008D0B98); //Updated for T4
			return xassettypes[type];
		}

		bool Linker::supports_building()
		{
			return false;
		}

		bool Linker::supports_version(const zone_target_version version)
		{
			return version == zone_target_version::t4_release;
		}

		void Linker::dump_zone(const std::string& name)
		{
			isDumping = true;
			currentDumpingZone = name;
			load_zone(name);
		}

		void Linker::verify_zone(const std::string& name)
		{
			isVerifying = true;
			currentDumpingZone = name;
			load_zone(name);
		}
	}
}
