#ifndef SYSTEM_ZLIB
#define SYSTEM_ZLIB

#include <cstdint>
#include <vector>
#include <assert.h>

namespace dc
{
	class zlib
	{
	public:
		static std::vector<uint8_t> compress(std::vector<uint8_t> in);
		static std::vector<uint8_t> decompress(std::vector<uint8_t> in, uint64_t uncompressedSize);
	};
}


#endif // !SYSTEM_ZLIB
