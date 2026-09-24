#include "stdafx.hpp"
#include "../Include.hpp"

#include "IwiImage.hpp"
#include "Assets/Material.hpp"

#include "IW5/IW5.hpp"
#include "IW4/IW4.hpp"
#include "IW3/IW3.hpp"

#include <cstring>

namespace ZoneTool::IW5
{
	namespace IW7Converter
	{
		namespace
		{
			enum IwiFormat : std::uint8_t
			{
				IWI_BITMAP_RGBA = 1,
				IWI_BITMAP_RGB = 2,
				IWI_BITMAP_LUMINANCE_ALPHA = 3,
				IWI_BITMAP_LUMINANCE = 4,
				IWI_BITMAP_ALPHA = 5,
				IWI_DXT1 = 11,
				IWI_DXT3 = 12,
				IWI_DXT5 = 13,
				IWI_DXN = 14,

				IWI_D3D_ARGB = 200,
			};

			constexpr std::uint8_t iwi_default_gloss = 64;

			enum IwiFlags
			{
				IWI_FLAG_NOPICMIP = 0x1,
				IWI_FLAG_NOMIPMAPS = 0x2,
				IWI_FLAG_CUBEMAP = 0x4,
				IWI_FLAG_VOLMAP = 0x8,
			};

			struct iwi_header
			{
				std::uint8_t format;
				unsigned int flags;
				unsigned short width;
				unsigned short height;
				unsigned short depth;
				std::size_t data_offset;
			};

			bool parse_iwi_header(const std::string& file, iwi_header& out)
			{
				if (file.size() < 32 || std::memcmp(file.data(), "IWi", 3) != 0)
				{
					return false;
				}

				const auto* b = reinterpret_cast<const std::uint8_t*>(file.data());
				if (b[3] <= 6)
				{
					out.format = b[4];
					out.flags = b[5];
					std::memcpy(&out.width, b + 6, 2);
					std::memcpy(&out.height, b + 8, 2);
					std::memcpy(&out.depth, b + 10, 2);
					out.data_offset = 28;
				}
				else
				{
					std::memcpy(&out.flags, b + 4, 4);
					out.format = b[8];
					std::memcpy(&out.width, b + 10, 2);
					std::memcpy(&out.height, b + 12, 2);
					std::memcpy(&out.depth, b + 14, 2);
					out.data_offset = 32;
				}
				return out.width && out.height;
			}

			unsigned int block_bytes(std::uint8_t format)
			{
				switch (format)
				{
				case IWI_DXT1: return 8;
				case IWI_DXT3:
				case IWI_DXT5:
				case IWI_DXN: return 16;
				default: return 0;
				}
			}

			unsigned int pixel_bytes(std::uint8_t format)
			{
				switch (format)
				{
				case IWI_BITMAP_RGBA: return 4;
				case IWI_BITMAP_RGB: return 3;
				case IWI_BITMAP_LUMINANCE_ALPHA: return 2;
				case IWI_BITMAP_LUMINANCE:
				case IWI_BITMAP_ALPHA: return 1;
				default: return 0;
				}
			}

			std::vector<std::size_t> mip_sizes(const iwi_header& hdr)
			{
				std::vector<std::size_t> sizes;
				const auto bb = block_bytes(hdr.format);
				const auto pb = pixel_bytes(hdr.format);

				auto w = static_cast<unsigned int>(hdr.width);
				auto h = static_cast<unsigned int>(hdr.height);
				while (true)
				{
					sizes.push_back(bb
						? static_cast<std::size_t>((w + 3) / 4) * ((h + 3) / 4) * bb
						: static_cast<std::size_t>(w) * h * pb);

					if (w <= 1 && h <= 1)
					{
						break;
					}
					w = std::max(1u, w / 2);
					h = std::max(1u, h / 2);
				}
				return sizes;
			}

			void bc4_decode(const std::uint8_t* block, float out[16])
			{
				const float a0 = block[0];
				const float a1 = block[1];

				float pal[8];
				pal[0] = a0;
				pal[1] = a1;
				if (a0 > a1)
				{
					for (int k = 1; k <= 6; k++)
					{
						pal[1 + k] = ((7 - k) * a0 + k * a1) / 7.0f;
					}
				}
				else
				{
					for (int k = 1; k <= 4; k++)
					{
						pal[1 + k] = ((5 - k) * a0 + k * a1) / 5.0f;
					}
					pal[6] = 0.0f;
					pal[7] = 255.0f;
				}

				std::uint64_t bits = 0;
				for (int i = 0; i < 6; i++)
				{
					bits |= static_cast<std::uint64_t>(block[2 + i]) << (8 * i);
				}
				for (int t = 0; t < 16; t++)
				{
					out[t] = pal[(bits >> (3 * t)) & 7];
				}
			}

			void bc4_encode(const float values[16], std::uint8_t* out)
			{
				float fmin = values[0], fmax = values[0];
				for (int i = 1; i < 16; i++)
				{
					fmin = std::min(fmin, values[i]);
					fmax = std::max(fmax, values[i]);
				}

				int hi = std::clamp(static_cast<int>(std::lround(fmax)), 0, 255);
				int lo = std::clamp(static_cast<int>(std::lround(fmin)), 0, 255);
				if (hi == lo)
				{
					if (hi < 255) { hi++; }
					else if (lo > 0) { lo--; }
				}

				const auto span = static_cast<float>(std::max(hi - lo, 1));
				std::uint64_t bits = 0;
				for (int k = 0; k < 16; k++)
				{
					const auto t = std::clamp(
						static_cast<int>(std::lround((values[k] - lo) * 7.0f / span)), 0, 7);
					const std::uint64_t sel = (t == 7) ? 0 : ((t == 0) ? 1 : static_cast<std::uint64_t>(8 - t));
					bits |= sel << (3 * k);
				}

				out[0] = static_cast<std::uint8_t>(hi);
				out[1] = static_cast<std::uint8_t>(lo);
				for (int i = 0; i < 6; i++)
				{
					out[2 + i] = static_cast<std::uint8_t>((bits >> (8 * i)) & 0xFF);
				}
			}

			void bc1_decode_green(const std::uint8_t* block, float out[16])
			{
				const unsigned int c0 = block[0] | (block[1] << 8);
				const unsigned int c1 = block[2] | (block[3] << 8);
				const float g0 = static_cast<float>(((c0 >> 5) & 63) * 255 / 63);
				const float g1 = static_cast<float>(((c1 >> 5) & 63) * 255 / 63);

				float pal[4];
				pal[0] = g0;
				pal[1] = g1;
				if (c0 > c1)
				{
					pal[2] = (2.0f * g0 + g1) / 3.0f;
					pal[3] = (g0 + 2.0f * g1) / 3.0f;
				}
				else
				{
					pal[2] = (g0 + g1) / 2.0f;
					pal[3] = 0.0f;
				}

				const unsigned int bits = block[4] | (block[5] << 8) | (block[6] << 16) | (block[7] << 24);
				for (int t = 0; t < 16; t++)
				{
					out[t] = pal[(bits >> (2 * t)) & 3];
				}
			}

			void bc4_decode_alpha(const std::uint8_t* block, std::uint8_t out[16])
			{
				const int a0 = block[0];
				const int a1 = block[1];

				int pal[8];
				pal[0] = a0;
				pal[1] = a1;
				if (a0 > a1)
				{
					for (int k = 1; k <= 6; k++)
					{
						pal[1 + k] = ((7 - k) * a0 + k * a1) / 7;
					}
				}
				else
				{
					for (int k = 1; k <= 4; k++)
					{
						pal[1 + k] = ((5 - k) * a0 + k * a1) / 5;
					}
					pal[6] = 0;
					pal[7] = 255;
				}

				std::uint64_t bits = 0;
				for (int i = 0; i < 6; i++)
				{
					bits |= static_cast<std::uint64_t>(block[2 + i]) << (8 * i);
				}
				for (int t = 0; t < 16; t++)
				{
					out[t] = static_cast<std::uint8_t>(pal[(bits >> (3 * t)) & 7]);
				}
			}

			constexpr int bc7_weights[4] = { 0, 21, 43, 64 };

			int bc7_interp(int a, int b, int w)
			{
				return (a * (64 - w) + b * w + 32) >> 6;
			}

			int bc7_quantize7(int value)
			{
				return std::clamp((value * 127 + 127) / 255, 0, 127);
			}

			int bc7_expand7(int value)
			{
				return (value << 1) | (value >> 6);
			}

			void bc7_fit(const std::uint8_t* values, int& lo, int& hi, int indices[16],
				bool endpoints_are_7bit)
			{
				const auto decode = [&](int e) { return endpoints_are_7bit ? bc7_expand7(e) : e; };

				for (int t = 0; t < 16; t++)
				{
					auto best = INT_MAX;
					for (int i = 0; i < 4; i++)
					{
						const auto v = bc7_interp(decode(lo), decode(hi), bc7_weights[i]);
						const auto err = std::abs(v - static_cast<int>(values[t]));
						if (err < best)
						{
							best = err;
							indices[t] = i;
						}
					}
				}

				if (indices[0] >= 2)
				{
					std::swap(lo, hi);
					for (int t = 0; t < 16; t++)
					{
						indices[t] = 3 - indices[t];
					}
				}
			}

			struct bc7_bit_writer
			{
				std::uint8_t* out;
				int pos = 0;

				void put(unsigned int value, int count)
				{
					for (auto i = 0; i < count; i++, pos++)
					{
						if ((value >> i) & 1)
						{
							out[pos >> 3] |= static_cast<std::uint8_t>(1 << (pos & 7));
						}
					}
				}
			};

			void bc7_encode_normal_block(const std::uint8_t green[16], const std::uint8_t alpha[16],
				std::uint8_t* out)
			{
				auto g_lo = 255;
				auto g_hi = 0;
				auto a_lo = 255;
				auto a_hi = 0;
				for (int t = 0; t < 16; t++)
				{
					g_lo = std::min<int>(g_lo, green[t]);
					g_hi = std::max<int>(g_hi, green[t]);
					a_lo = std::min<int>(a_lo, alpha[t]);
					a_hi = std::max<int>(a_hi, alpha[t]);
				}

				auto g0 = bc7_quantize7(g_lo);
				auto g1 = bc7_quantize7(g_hi);
				int colour_indices[16];
				bc7_fit(green, g0, g1, colour_indices, true);

				int alpha_indices[16];
				bc7_fit(alpha, a_lo, a_hi, alpha_indices, false);

				const auto r7 = bc7_quantize7(255);
				const auto b7 = bc7_quantize7(0);

				std::memset(out, 0, 16);
				bc7_bit_writer bits{ out };
				bits.put(1 << 5, 6);
				bits.put(0, 2);
				bits.put(r7, 7); bits.put(r7, 7);
				bits.put(g0, 7); bits.put(g1, 7);
				bits.put(b7, 7); bits.put(b7, 7);
				bits.put(a_lo, 8); bits.put(a_hi, 8);

				bits.put(colour_indices[0], 1);
				for (int t = 1; t < 16; t++) bits.put(colour_indices[t], 2);
				bits.put(alpha_indices[0], 1);
				for (int t = 1; t < 16; t++) bits.put(alpha_indices[t], 2);
			}

			void dxt5_to_bc7_normal(const std::uint8_t* src, std::uint8_t* dst, std::size_t blocks)
			{
				for (std::size_t i = 0; i < blocks; i++)
				{
					const auto* in = src + i * 16;

					std::uint8_t x[16];
					bc4_decode_alpha(in, x);

					float y_float[16];
					bc1_decode_green(in + 8, y_float);

					std::uint8_t y[16];
					for (int t = 0; t < 16; t++)
					{
						y[t] = static_cast<std::uint8_t>(std::clamp(y_float[t] + 0.5f, 0.0f, 255.0f));
					}

					bc7_encode_normal_block(y, x, dst + i * 16);
				}
			}

			void dxt1_to_bc3(const std::uint8_t* src, std::uint8_t* dst, std::size_t blocks,
				std::uint8_t gloss)
			{
				for (std::size_t i = 0; i < blocks; i++)
				{
					auto* out = dst + i * 16;
					std::memset(out, 0, 8);
					out[0] = gloss;
					out[1] = gloss;
					std::memcpy(out + 8, src + i * 8, 8);
				}
			}
		}

		std::uint8_t normalize_format(int format)
		{
			switch (static_cast<unsigned int>(format))
			{
			case 0x31545844: return IWI_DXT1;
			case 0x33545844: return IWI_DXT3;
			case 0x35545844: return IWI_DXT5;
			case 0x32495441: return IWI_DXN;
			case 0x15:
			case 0x16: return IWI_D3D_ARGB;
			case 0x32: return IWI_BITMAP_LUMINANCE;
			default: break;
			}
			return (format > 0 && format <= 19) ? static_cast<std::uint8_t>(format) : 0;
		}

		bool split_levels(const std::vector<std::size_t>& sizes, std::size_t available,
			std::vector<std::size_t>& present, std::size_t& total)
		{
			std::size_t acc = 0;
			std::vector<std::size_t> suffix;
			for (auto it = sizes.rbegin(); it != sizes.rend(); ++it)
			{
				suffix.push_back(*it);
				acc += *it;
				if (acc == available)
				{
					present.assign(suffix.rbegin(), suffix.rend());
					total = acc;
					return true;
				}
				if (acc > available)
				{
					break;
				}
			}

			if (!sizes.empty() && available == sizes[0])
			{
				present.assign(1, sizes[0]);
				total = sizes[0];
				return true;
			}
			return false;
		}

		IW7::GfxImage* build_image(const char* name, std::uint8_t iw5_semantic, std::uint8_t format,
			unsigned short width, unsigned short height, const std::uint8_t* data,
			std::size_t available, bool cube_hint, allocator& mem)
		{
			iwi_header hdr{};
			hdr.format = format;
			hdr.width = width;
			hdr.height = height;

			const auto sizes = mip_sizes(hdr);

			std::size_t faces = 1;
			std::vector<std::size_t> present;
			std::size_t total = 0;
			if (!split_levels(sizes, available, present, total))
			{
				if ((available % 6) == 0 && split_levels(sizes, available / 6, present, total))
				{
					faces = 6;
				}
				else
				{
					ZONETOOL_WARNING("Image \"%s\": %ux%u format %u does not account for %u bytes",
						name, width, height, format, static_cast<unsigned int>(available));
					return nullptr;
				}
			}
			else if (cube_hint && available == total)
			{
				ZONETOOL_WARNING("Image \"%s\": flagged as a cube but only holds one face", name);
			}

			const auto semantic = static_cast<std::uint8_t>(IW7::convert_semantic(iw5_semantic));
			const auto* blob = data + (available - total * faces);

			DXGI_FORMAT dxgi;
			std::size_t out_size = total;
			bool transcode_normal = false;
			bool transcode_specular = false;

			if (format == IWI_DXT5 && semantic == IW7::TextureSemantic::TS_NORMAL_MAP)
			{
				dxgi = DXGI_FORMAT_BC7_UNORM;
				transcode_normal = true;
			}
			else if (format == IWI_DXT1 && semantic == IW7::TextureSemantic::TS_SPECULAR_MAP)
			{
				dxgi = DXGI_FORMAT_BC3_UNORM;
				transcode_specular = true;
				out_size = total * 2;
			}
			else
			{
				switch (format)
				{
				case IWI_DXT1: dxgi = DXGI_FORMAT_BC1_UNORM; break;
				case IWI_DXT3: dxgi = DXGI_FORMAT_BC2_UNORM; break;
				case IWI_DXT5: dxgi = DXGI_FORMAT_BC3_UNORM; break;
				case IWI_DXN: dxgi = DXGI_FORMAT_BC5_UNORM; break;
				case IWI_BITMAP_RGBA: dxgi = DXGI_FORMAT_R8G8B8A8_UNORM; break;
				case IWI_BITMAP_LUMINANCE_ALPHA: dxgi = DXGI_FORMAT_R8G8_UNORM; break;
				case IWI_BITMAP_LUMINANCE:
				case IWI_BITMAP_ALPHA: dxgi = DXGI_FORMAT_R8_UNORM; break;
				case IWI_D3D_ARGB: dxgi = DXGI_FORMAT_R8G8B8A8_UNORM; break;
				case IWI_BITMAP_RGB:
					dxgi = DXGI_FORMAT_R8G8B8A8_UNORM;
					out_size = (total / 3) * 4;
					break;
				default:
					ZONETOOL_WARNING("Image \"%s\": no mapping for image format %u", name, format);
					return nullptr;
				}
			}

			auto* pixels = mem.allocate<std::uint8_t>(static_cast<unsigned int>(out_size * faces));

			std::size_t src_off = 0;
			std::vector<std::size_t> src_offsets(present.size());
			for (std::size_t i = present.size(); i-- > 0; )
			{
				src_offsets[i] = src_off;
				src_off += present[i];
			}

			constexpr bool source_is_mip_major = true;

			std::size_t dst_off = 0;
			for (std::size_t face = 0; face < faces; face++)
			for (std::size_t i = 0; i < present.size(); i++)
			{
				const auto len = present[i];
				const auto* in = source_is_mip_major
					? blob + src_offsets[i] * faces + face * len
					: blob + face * total + src_offsets[i];

				if (transcode_normal)
				{
					dxt5_to_bc7_normal(in, pixels + dst_off, len / 16);
					dst_off += len;
				}
				else if (transcode_specular)
				{
					dxt1_to_bc3(in, pixels + dst_off, len / 8, iwi_default_gloss);
					dst_off += len * 2;
				}
				else if (format == IWI_D3D_ARGB)
				{
					for (std::size_t q = 0; q < len / 4; q++)
					{
						pixels[dst_off + q * 4 + 0] = in[q * 4 + 2];
						pixels[dst_off + q * 4 + 1] = in[q * 4 + 1];
						pixels[dst_off + q * 4 + 2] = in[q * 4 + 0];
						pixels[dst_off + q * 4 + 3] = in[q * 4 + 3];
					}
					dst_off += len;
				}
				else if (format == IWI_BITMAP_RGB)
				{
					for (std::size_t q = 0; q < len / 3; q++)
					{
						pixels[dst_off + q * 4 + 0] = in[q * 3 + 0];
						pixels[dst_off + q * 4 + 1] = in[q * 3 + 1];
						pixels[dst_off + q * 4 + 2] = in[q * 3 + 2];
						pixels[dst_off + q * 4 + 3] = 255;
					}
					dst_off += (len / 3) * 4;
				}
				else
				{
					std::memcpy(pixels + dst_off, in, len);
					dst_off += len;
				}
			}

			const auto image = mem.allocate<IW7::GfxImage>();
			image->name = mem.duplicate_string(name);
			image->imageFormat = dxgi;
			image->flags = 0;
			image->semantic = static_cast<IW7::TextureSemantic>(semantic);
			image->category = IW7::IMG_CATEGORY_LOAD_FROM_FILE;
			image->picmip.platform[0] = 0;
			image->picmip.platform[1] = 2;
			image->dataLen1 = static_cast<unsigned int>(dst_off);
			image->dataLen2 = image->dataLen1;
			image->width = width;
			image->height = height;
			image->depth = 1;
			image->numElements = 1;
			image->mapType = (faces == 6) ? IW7::MAPTYPE_CUBE : IW7::MAPTYPE_2D;
			image->levelCount = static_cast<unsigned char>(present.size());
			image->streamed = false;
			image->pixelData = pixels;

			return image;
		}

		bool load_source(GfxImage* asset, source_image& out)
		{
			const std::uint8_t* data = nullptr;
			std::size_t available = 0;

			const auto* load_def = asset->texture.loadDef;
			if (load_def && load_def->resourceSize > 0)
			{
				out.format = normalize_format(load_def->format);
				out.width = asset->width;
				out.height = asset->height;
				data = reinterpret_cast<const std::uint8_t*>(&load_def->data);
				available = static_cast<std::size_t>(load_def->resourceSize);
			}
			else
			{
				std::function read_file = filesystem_read_big_file;
				if (get_linker_mode() == linker_mode::iw4) read_file = ZoneTool::IW4::filesystem_read_big_file;
				if (get_linker_mode() == linker_mode::iw3) read_file = ZoneTool::IW3::filesystem_read_big_file;

				out.storage = read_file(va("images/%s.iwi", asset->name).data());
				if (out.storage.empty())
				{
					return false;
				}

				iwi_header hdr{};
				if (!parse_iwi_header(out.storage, hdr))
				{
					return false;
				}
				out.format = hdr.format;
				out.width = hdr.width;
				out.height = hdr.height;
				data = reinterpret_cast<const std::uint8_t*>(out.storage.data()) + hdr.data_offset;
				available = out.storage.size() - hdr.data_offset;
			}

			if (!out.format || !out.width || !out.height)
			{
				return false;
			}

			iwi_header shape{};
			shape.format = out.format;
			shape.width = out.width;
			shape.height = out.height;

			std::vector<std::size_t> present;
			std::size_t total = 0;
			if (!split_levels(mip_sizes(shape), available, present, total))
			{
				return false;
			}

			const auto* blob = data + (available - total);
			std::vector<std::size_t> offsets(present.size());
			std::size_t off = 0;
			for (std::size_t i = present.size(); i-- > 0; )
			{
				offsets[i] = off;
				off += present[i];
			}
			for (std::size_t i = 0; i < present.size(); i++)
			{
				out.levels.emplace_back(blob + offsets[i], present[i]);
			}
			return true;
		}

		IW7::GfxImage* convert_resident(GfxImage* asset, allocator& mem)
		{
			const auto* load_def = asset->texture.loadDef;
			if (!load_def || load_def->resourceSize <= 0)
			{
				return nullptr;
			}

			const auto format = normalize_format(load_def->format);
			if (!format)
			{
				ZONETOOL_WARNING("Image \"%s\": unknown resident format %d", asset->name, load_def->format);
				return nullptr;
			}

			const auto cube = asset->mapType == 5
				|| (load_def->flags & IWI_FLAG_CUBEMAP) != 0;

			return build_image(asset->name, asset->semantic, format, asset->width, asset->height,
				reinterpret_cast<const std::uint8_t*>(&load_def->data),
				static_cast<std::size_t>(load_def->resourceSize), cube, mem);
		}

		IW7::GfxImage* convert_iwi(const char* name, std::uint8_t iw5_semantic, allocator& mem)
		{
			std::function read_file = filesystem_read_big_file;
			if (get_linker_mode() == linker_mode::iw4) read_file = ZoneTool::IW4::filesystem_read_big_file;
			if (get_linker_mode() == linker_mode::iw3) read_file = ZoneTool::IW3::filesystem_read_big_file;

			auto file = read_file(va("images/%s.iwi", name).data());
			if (file.empty())
			{
				file = read_file(va("raw/images/%s.iwi", name).data());
				if (file.empty())
				{
					return nullptr;
				}
			}

			iwi_header hdr{};
			if (!parse_iwi_header(file, hdr))
			{
				ZONETOOL_WARNING("Image \"%s\": not a usable .iwi", name);
				return nullptr;
			}

			return build_image(name, iw5_semantic, hdr.format, hdr.width, hdr.height,
				reinterpret_cast<const std::uint8_t*>(file.data()) + hdr.data_offset,
				file.size() - hdr.data_offset, (hdr.flags & IWI_FLAG_CUBEMAP) != 0, mem);
		}
	}
}
