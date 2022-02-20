#include "zlib.hpp"


#include <zlib.h>

#include <iostream>



namespace dc
{

	std::vector<uint8_t> zlib::compress(std::vector<uint8_t> in)
	{
		uLong len = compressBound(in.size());

		Bytef* outbuffer = new Bytef[len];

		int error = compress2(outbuffer, &len, reinterpret_cast<Bytef*>(in.data()), in.size(), Z_DEFAULT_COMPRESSION);
		if (error != Z_OK)
		{
			switch (error)
			{
			case Z_MEM_ERROR:
				std::cout << "zlib Memory Error!" << std::endl;
				break;
			case Z_BUF_ERROR:
				std::cout << "zlib Buffer Error!" << std::endl;
				break;
			default:
				std::cout << "zlib Unknown Error!" << std::endl;
				break;
			}
		}

		std::vector<uint8_t> outBuffer(outbuffer, outbuffer + len);
		delete[] outbuffer;

		return outBuffer;
	}

	std::vector<uint8_t> zlib::decompress(std::vector<uint8_t> in, uint64_t uncompressedSize)
	{
		uLong len = (uLong)(uncompressedSize);

		Bytef* outbuffer = new Bytef[len];

		uLong src = in.size();

		int error = uncompress(outbuffer, &len, reinterpret_cast<Bytef*>(in.data()), src);

		if (error != Z_OK)
		{
			switch (error)
			{
			case Z_MEM_ERROR:
				std::cout << "zlib Memory Error!" << std::endl;
				break;
			case Z_BUF_ERROR:
				std::cout << "zlib Buffer Error!" << std::endl;
				break;
			default:
				std::cout << "zlib Unknown Error!" << std::endl;
				break;
			}
		}
		std::vector<uint8_t> outBuffer(outbuffer, outbuffer + len);

		//delete[] outbuffer;

		return outBuffer;
	}
}

