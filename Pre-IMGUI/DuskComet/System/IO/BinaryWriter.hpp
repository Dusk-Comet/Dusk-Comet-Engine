#ifndef DUSKCOMET_SYSTEM_IO_BINARYWRITER__HPP
#define DUSKCOMET_SYSTEM_IO_BINARYWRITER__HPP

#include "../../Game.hpp"

#include <iostream>
#include <fstream>

#include <string>
#include <cstdint>

namespace dc
{

	class BinaryWriter
	{
	private:
		//std::fstream basestream;
		std::vector<uint8_t> buffer;

		uint64_t position = 0;

		bool isBigEndian = dc::SYSTEM_IS_BIG_ENDIAN();
		bool isBigEndianSystem = dc::SYSTEM_IS_BIG_ENDIAN();

		uint32_t fileSize = 0;

	public:
		BinaryWriter();
		//BinaryWriter(std::string filepath);


		std::vector<uint8_t> getBuffer();


		void close();


		void setPosition(uint64_t pos);
		uint64_t getPosition();


		uint64_t getLength();

		bool isStreamBigEndian() { return isBigEndian; }

		void setStreamBigEndian(bool value) { isBigEndian = value; }


		void write(uint8_t value);
		void write(int8_t value);

		void write(uint16_t value);
		void write(int16_t value);

		void write(uint32_t value);
		void write(int32_t value);

		void write(uint64_t value);
		void write(int64_t value);

		void write(float value);
		void write(double value);

		void write(uint8_t arr[], uint32_t size);

		void write(std::string value);

	};

}


#endif // !DUSKCOMET_SYSTEM_IO_BINARYWRITER__HPP
