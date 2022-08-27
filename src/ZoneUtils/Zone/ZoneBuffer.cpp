// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

#include <zstd.h>
#include <zlib.h>
#include <tomcrypt.h>

#include "PrivateKey.hpp"

#define ZSTD_BEST_COMPRESSION 22
#define ZLIB_BEST_COMPRESSION Z_BEST_COMPRESSION

namespace ZoneTool
{
	ZoneBuffer::ZoneBuffer()
	{
		this->m_stream = 0;
		this->m_shiftsize = 0;
		this->m_numstreams = 0;

		this->m_pos = 0;
		this->m_len = MAX_ZONE_SIZE;

		this->m_zonepointers.clear();

		// 370mb, should be enough?
		this->m_buf.resize(this->m_len);
	}

	ZoneBuffer::~ZoneBuffer()
	{
		// clear zone pointers
		this->m_zonepointers.clear();

		// clear scriptstrings
		for (std::size_t idx = 0; idx < this->m_scriptstrings.size(); idx++)
		{
			free(this->m_scriptstrings[idx]);
		}
		this->m_scriptstrings.clear();

		// clear zone buffer
		this->m_buf.clear();
	}

	ZoneBuffer::ZoneBuffer(std::vector<std::uint8_t> data)
	{
		this->m_stream = 0;
		this->m_shiftsize = 0;
		this->m_numstreams = 0;

		this->m_buf = data;
		this->m_pos = data.size();
		this->m_len = data.size();

		this->m_zonepointers.clear();
	}

	ZoneBuffer::ZoneBuffer(std::size_t size)
	{
		this->m_stream = 0;
		this->m_shiftsize = 0;
		this->m_numstreams = 0;

		this->m_pos = 0;
		this->m_len = size;
		this->m_buf.resize(this->m_len);

		this->m_zonepointers.clear();
	}

	void ZoneBuffer::init_streams(std::size_t streams)
	{
		this->m_numstreams = streams;
		this->m_zonestreams.resize(streams);

		this->m_shiftsize = 32;

		for (std::size_t i = 31; i > 0; i--)
		{
			if (std::bitset<sizeof(std::size_t) * 8>(this->m_numstreams).test(i))
			{
				this->m_shiftsize -= (i + 1);
				break;
			}
		}
	}

	void ZoneBuffer::write_data(const void* _data, std::size_t size, std::size_t count)
	{
		// Check if we should realloc the buffer
		if ((size * count) + m_pos > m_len)
		{
			ZONETOOL_ERROR("No more space left in zone buffer."); // this->realloc(((size * count) + m_pos) - m_len);
			return;
		}

		// Copy data to buffer
		memcpy(&m_buf[m_pos], _data, size * count);
		m_pos += size * count;
	}

	void ZoneBuffer::write_data(const void* _data, std::size_t size)
	{
		write_data(_data, size, 1);
	}

	void ZoneBuffer::write_stream(const void* _data, std::size_t size, std::size_t count)
	{
		// If we're writing to stream 2...
		if (m_stream == 2) // ZONESTREAM_RUNTIME. Meaning that this data is generated when the game runs.
			// Therefore we need to alloc space, but we don't write data.
		{
			// if (m_numstreams > 0)
			{
				m_zonestreams[m_stream] += size * count;
			}

			return;
		}

		write_data(_data, size, count);

		// Update streams
		// if (m_numstreams > 0)
		{
			m_zonestreams[m_stream] += size * count;
		}
	}

	void ZoneBuffer::write_stream(const void* _data, size_t size)
	{
		return write_stream(_data, size, 1);
	}

	char* ZoneBuffer::write_str(const std::string& _str)
	{
		write_stream(_str.data(), _str.size() + 1);
		return reinterpret_cast<char*>(-1);
	}

	void ZoneBuffer::write_str_raw(const std::string& _str)
	{
		return write_stream(_str.data(), _str.size() + 1);
	}

	std::uint8_t* ZoneBuffer::buffer()
	{
		return m_buf.data();
	}

	std::size_t ZoneBuffer::size()
	{
		return m_pos;
	}

	void ZoneBuffer::align(std::uint32_t alignment)
	{
		// if (m_numstreams > 0)
		{
			m_zonestreams[m_stream] = ~alignment & (alignment + m_zonestreams[m_stream]);
		}
	}

	void ZoneBuffer::inc_stream(const std::uint32_t stream, const std::size_t size)
	{
		m_zonestreams[stream] += size;
	}

	void ZoneBuffer::push_stream(std::uint32_t stream)
	{
		m_streamstack.push(m_stream);
		m_stream = stream;
	}

	void ZoneBuffer::pop_stream()
	{
		m_stream = m_streamstack.top();
		m_streamstack.pop();
	}

	std::uint8_t ZoneBuffer::current_stream()
	{
		return m_stream;
	}

	std::uint32_t ZoneBuffer::current_stream_offset()
	{
		return m_zonestreams[m_stream];
	}

	std::uint32_t ZoneBuffer::stream_offset(std::uint8_t stream)
	{
		return m_zonestreams[stream];
	}

	std::uint16_t ZoneBuffer::write_scriptstring(std::string str)
	{
		this->m_scriptstrings.push_back(_strdup(str.data()));
		return static_cast<std::uint16_t>(this->m_scriptstrings.size() - 1);
	}

	const char* ZoneBuffer::get_scriptstring(std::size_t idx)
	{
		return this->m_scriptstrings[idx];
	}

	std::size_t ZoneBuffer::scriptstring_count()
	{
		return this->m_scriptstrings.size();
	}

	void ZoneBuffer::save(const std::string& filename)
	{
		// Alloc file
		std::filebuf _fb;
		_fb.open(filename, (std::ios::out | std::ios::binary));

		// Write buffer to file
		std::ostream _os(&_fb);
		_os.write(reinterpret_cast<const char*>(m_buf.data()), m_pos);

		// Close file
		_fb.close();
	}

	std::vector<std::uint8_t> ZoneBuffer::compress_zlib(const std::uint8_t* data, const std::size_t data_size, bool compress_blocks)
	{
		auto compressBound = [](unsigned long sourceLen)
		{
			return static_cast<unsigned long>((ceil(sourceLen * 1.001)) + 12);
		};

		if (compress_blocks == false)
		{
			// calculate buffer size needed for current zone
			auto size = compressBound(data_size);

			// alloc array for compressed data
			std::vector<std::uint8_t> compressed;
			compressed.resize(size);

			// compress buffer
			auto status = compress2(compressed.data(), &size, data, data_size, ZLIB_BEST_COMPRESSION);
			compressed.resize(size);

			// return compressed buffer
			return compressed;
		}
		else
		{
			// data should be 0x10000 byte aligned
			const auto block_size = 0x10000;
			auto bound_size = compressBound(block_size);
			auto num_blocks = data_size / block_size;

			std::vector<std::vector<std::uint8_t>> blocks;
			blocks.resize(num_blocks);

			auto data_ptr = data;
			for (auto& block : blocks)
			{
				// allocate for compressed data
				block.resize(bound_size);

				// compress block buffer
				unsigned long size;
				auto status = compress2(block.data(), &size, data_ptr, block_size, ZLIB_BEST_COMPRESSION);
				if (size >= block_size)
				{
					// discard compressed data and just store uncompressed data
					block.resize(block_size + 2);

					// 0 block size is uncompressed
					block[0] = 0;
					block[1] = 0;
					memcpy(block.data() + 2, data_ptr, block_size);
				}
				else
				{
					block.resize(size);

					// overwrite zlib header with block size
					size -= 2;
					block[0] = (size & 0xff00) >> 8;
					block[1] = size & 0xff;
				}

				// go to next block
				data_ptr += block_size;
			}

			std::vector<uint8_t> compressed;
			for (auto& block : blocks)
			{
				compressed.insert(compressed.end(), block.begin(), block.end());
			}


			return compressed;
		}
	}

	std::vector<std::uint8_t> ZoneBuffer::compress_zlib(const std::vector<std::uint8_t>& data, bool compress_blocks)
	{
		return ZoneBuffer::compress_zlib(data.data(), data.size(), compress_blocks);
	}

	std::vector<std::uint8_t> ZoneBuffer::compress_zstd()
	{
		// calculate buffer size needed for current zone
		auto size = ZSTD_compressBound(this->m_pos);

		// alloc array for compressed data
		std::vector<std::uint8_t> compressed;
		compressed.resize(size);

		// compress buffer
		auto destsize = ZSTD_compress(compressed.data(), size, this->m_buf.data(), this->m_pos, 11);
		compressed.resize(destsize);

		if (ZSTD_isError(destsize))
		{
			ZONETOOL_ERROR("An error occured while compressing the fastfile: %s", ZSTD_getErrorName(destsize));
			return {};
		}

		// return compressed buffer
		return compressed;
	}

	std::vector<std::uint8_t> ZoneBuffer::compress_zlib(bool compress_blocks)
	{
		return ZoneBuffer::compress_zlib(this->m_buf.data(), this->m_pos, compress_blocks);
	}

	void GenerateKeys(XZoneKey* key)
	{
		srand(time(nullptr));

		auto buffer = reinterpret_cast<std::uint8_t*>(key);

		for (auto idx = 0u; idx < sizeof XZoneKey; idx++)
		{
			buffer[idx] = (rand() % 0xFF);
		}
	}

	void ZoneBuffer::encrypt()
	{
		// register ciphers
		register_cipher(&aes_desc);

		// find hashes
		auto h_sha512 = find_hash("sha512");
		auto h_aes = find_cipher("aes");

		// generate random encryption key
		XZoneKey zonekey;
		GenerateKeys(&zonekey);
		zonekey.version = 1;

		// realloc buffersize
		{
			auto destsize =
#ifdef USE_PRIVATEKEY
				512 +
#else
				sizeof XZoneKey +
#endif
				this->m_buf.size();
			std::vector<std::uint8_t> temp = this->m_buf;
			this->m_buf.resize(destsize + (16 - (destsize % 16)));
			memcpy(&this->m_buf[0], &temp[0], temp.size());
		}

#ifdef USE_PRIVATEKEY
		unsigned long keylen = 512;
		unsigned char enc_key[512];

		// import rsa key...
		rsa_key key;
		rsa_import(&PrivateKey[0], PrivateKey.size(), &key);
		rsa_encrypt_key(reinterpret_cast<unsigned char*>(&zonekey), sizeof XZoneKey, enc_key, &keylen, 0, 0, 0, 0, h_sha512, &key);
		rsa_free(&key);

		// move ff data
		memcpy(&this->m_buf[512], &this->m_buf[0], this->m_buf.size() - 512);

		// copy RSA key
		memcpy(&this->m_buf[0], enc_key, 512);
#else
		// move ff data
		memcpy(&this->m_buf[sizeof XZoneKey], &this->m_buf[0], this->m_buf.size() - sizeof XZoneKey);
#endif

		// encrypt fastfile data
		symmetric_CBC cbc;
		cbc_start(h_aes, zonekey.iv, zonekey.key, 32, 0, &cbc);
#ifdef USE_PRIVATEKEY
		cbc_encrypt(&this->m_buf[512], &this->m_buf[512], this->m_buf.size() - 512, &cbc);
#else
		cbc_encrypt(&this->m_buf[sizeof XZoneKey], &this->m_buf[sizeof XZoneKey], this->m_buf.size() - sizeof XZoneKey,
		            &cbc);
#endif
		cbc_done(&cbc);
	}
}
