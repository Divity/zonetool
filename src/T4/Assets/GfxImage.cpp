#include "stdafx.hpp"
#include "../IW4/Assets/GfxImage.hpp"

#include <unzip.h>
#include <filesystem>

namespace ZoneTool
{
	namespace T4
	{
		namespace
		{
			bool is_map_image(const std::string& name)
			{
				if (name == "$outdoor")
				{
					return true;
				}

				return name.size() >= 6 && (name.substr(0, 6) == "*light" || name.substr(0, 6) == "*refle");
			}

			std::string to_lower(std::string value)
			{
				std::transform(value.begin(), value.end(), value.begin(), ::tolower);
				return value;
			}

			std::unordered_map<std::string, std::string>& iwi_index()
			{
				static std::unordered_map<std::string, std::string> index;
				static bool built = false;

				if (built)
				{
					return index;
				}

				built = true;

				std::error_code code;
				std::vector<std::string> archives;

				for (const auto& entry : std::filesystem::directory_iterator("main", code))
				{
					if (entry.is_regular_file(code) && to_lower(entry.path().extension().string()) == ".iwd")
					{
						archives.push_back(entry.path().string());
					}
				}

				std::sort(archives.begin(), archives.end());

				for (const auto& archive : archives)
				{
					auto* zip = unzOpen(archive.data());
					if (!zip)
					{
						continue;
					}

					if (unzGoToFirstFile(zip) == UNZ_OK)
					{
						do
						{
							char entry_name[512]{};
							unz_file_info info{};

							if (unzGetCurrentFileInfo(zip, &info, entry_name, sizeof entry_name - 1, nullptr, 0, nullptr, 0) != UNZ_OK)
							{
								continue;
							}

							auto name = to_lower(entry_name);
							if (name.size() > 4 && name.substr(name.size() - 4) == ".iwi")
							{
								std::replace(name.begin(), name.end(), '\\', '/');

								const auto slash = name.find_last_of('/');
								const auto base = (slash == std::string::npos) ? name : name.substr(slash + 1);

								index[base.substr(0, base.size() - 4)] = archive;
							}
						}
						while (unzGoToNextFile(zip) == UNZ_OK);
					}

					unzClose(zip);
				}

				ZONETOOL_INFO("Indexed %u images across %u iwd archives.",
					static_cast<unsigned>(index.size()), static_cast<unsigned>(archives.size()));

				return index;
			}

#pragma pack(push, 1)
			struct IwiHeaderV6
			{
				char tag[3];
				char version;
				char format;
				char flags;
				std::int16_t dimensions[3];
				std::int32_t fileSizeForPicmip[4];
			};

			struct IwiHeaderV8
			{
				char tag[3];
				char version;
				std::uint32_t flags;
				char format;
				char unused;
				std::int16_t dimensions[3];
				std::int32_t fileSizeForPicmip[4];
			};
#pragma pack(pop)

			struct IwiInfo
			{
				bool valid;
				char format;
				char flags;
				std::int16_t dimensions[3];
				std::uint32_t dataSize;
			};

			IwiInfo dump_iwi(const std::string& name)
			{
				IwiInfo info{};

				auto& index = iwi_index();

				const auto entry = index.find(to_lower(name));
				if (entry == index.end())
				{
					ZONETOOL_WARNING("Could not find iwi for image \"%s\"!", name.data());
					return info;
				}

				auto* zip = unzOpen(entry->second.data());
				if (!zip)
				{
					return info;
				}

				const auto path = "images/" + name + ".iwi";

				if (unzLocateFile(zip, path.data(), 2) == UNZ_OK && unzOpenCurrentFile(zip) == UNZ_OK)
				{
					unz_file_info file_info{};
					unzGetCurrentFileInfo(zip, &file_info, nullptr, 0, nullptr, 0, nullptr, 0);

					std::vector<std::uint8_t> buffer(file_info.uncompressed_size);

					const auto read = unzReadCurrentFile(zip, buffer.data(), static_cast<unsigned>(buffer.size()));
					unzCloseCurrentFile(zip);

					if (read > static_cast<int>(sizeof IwiHeaderV6) && !memcmp(buffer.data(), "IWi", 3))
					{
						const auto header = *reinterpret_cast<const IwiHeaderV6*>(buffer.data());

						if (header.version == 6)
						{
							IwiHeaderV8 converted{};
							memcpy(converted.tag, header.tag, sizeof converted.tag);
							converted.version = 8;
							converted.flags = static_cast<std::uint8_t>(header.flags);
							converted.format = header.format;
							converted.unused = 0;
							memcpy(converted.dimensions, header.dimensions, sizeof converted.dimensions);

							constexpr auto delta = static_cast<std::int32_t>(sizeof IwiHeaderV8 - sizeof IwiHeaderV6);
							for (auto i = 0; i < 4; i++)
							{
								converted.fileSizeForPicmip[i] = header.fileSizeForPicmip[i] + delta;
							}

							const auto pixels = read - static_cast<int>(sizeof IwiHeaderV6);

							std::vector<std::uint8_t> out(sizeof converted + pixels);
							memcpy(out.data(), &converted, sizeof converted);
							memcpy(out.data() + sizeof converted, buffer.data() + sizeof IwiHeaderV6, pixels);

							buffer = std::move(out);

							info.valid = true;
							info.format = header.format;
							info.flags = header.flags;
							memcpy(info.dimensions, header.dimensions, sizeof info.dimensions);
							info.dataSize = static_cast<std::uint32_t>(pixels);
						}
						else if (header.version == 8)
						{
							const auto v8 = *reinterpret_cast<const IwiHeaderV8*>(buffer.data());

							info.valid = true;
							info.format = v8.format;
							info.flags = static_cast<char>(v8.flags);
							memcpy(info.dimensions, v8.dimensions, sizeof info.dimensions);
							info.dataSize = static_cast<std::uint32_t>(read - static_cast<int>(sizeof IwiHeaderV8));

							buffer.resize(read);
						}
						else
						{
							ZONETOOL_WARNING("Unsupported iwi version %u for image \"%s\"!",
								static_cast<unsigned>(header.version), name.data());
						}
					}

					if (info.valid)
					{
						auto* file = FileSystem::FileOpen("images\\" + name + ".iwi", "wb");
						if (file)
						{
							fwrite(buffer.data(), buffer.size(), 1, file);
							FileSystem::FileClose(file);
						}
					}
				}

				unzClose(zip);

				return info;
			}
		}

		void IGfxImage::dump(GfxImage* asset, ZoneMemory* mem)
		{
			if (!asset || !asset->name)
			{
				return;
			}

			if (!is_map_image(asset->name))
			{
				dump_iwi(asset->name);
				return;
			}

			auto* iw4_image = generate_iw4_image(asset, mem);
			if (!iw4_image)
			{
				return;
			}

			ZONETOOL_INFO("Dumping image %s (%ux%u, %u bytes)", asset->name,
				iw4_image->width, iw4_image->height, iw4_image->dataLen1);

			IW4::IGfxImage::dump(iw4_image);
		}

		IW4::GfxImage* IGfxImage::generate_iw4_image(GfxImage* asset, ZoneMemory* mem)
		{
			if (!asset)
			{
				return nullptr;
			}

			auto* loadDef = asset->texture.loadDef;
			if (!loadDef || !loadDef->resourceSize)
			{
				return nullptr;
			}

			auto* iw4_image = mem->Alloc<IW4::GfxImage>();

			iw4_image->mapType = static_cast<char>(asset->mapType);
			iw4_image->semantic = asset->semantic;
			iw4_image->category = asset->category;
			iw4_image->flags = 0;
			iw4_image->cardMemory = asset->cardMemory.platform[0];
			iw4_image->dataLen1 = loadDef->resourceSize;
			iw4_image->dataLen2 = loadDef->resourceSize;
			iw4_image->width = loadDef->dimensions[0];
			iw4_image->height = loadDef->dimensions[1];
			iw4_image->depth = loadDef->dimensions[2];
			iw4_image->loaded = false;
			iw4_image->name = const_cast<char*>(asset->name);

			auto* iw4_loaddef = mem->ManualAlloc<IW4::GfxImageLoadDef>(
				sizeof IW4::GfxImageLoadDef + loadDef->resourceSize);

			iw4_loaddef->mipLevels = loadDef->levelCount;
			iw4_loaddef->flags = loadDef->flags;
			iw4_loaddef->dimensions[0] = loadDef->dimensions[0];
			iw4_loaddef->dimensions[1] = loadDef->dimensions[1];
			iw4_loaddef->dimensions[2] = loadDef->dimensions[2];
			iw4_loaddef->format = loadDef->format;
			iw4_loaddef->dataSize = loadDef->resourceSize;
			std::memcpy(&iw4_loaddef->texture, loadDef->data, loadDef->resourceSize);

			iw4_image->texture = iw4_loaddef;

			return iw4_image;
		}
	}
}
