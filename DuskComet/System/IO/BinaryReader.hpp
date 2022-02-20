#ifndef DUSKCOMET_SYSTEM_IO_BINARYREADER_HPP
#define DUSKCOMET_SYSTEM_IO_BINARYREADER_HPP

#include "../../Game.hpp"

#include <iostream>
#include <fstream>

#include <string>
#include <cstdint>
namespace dc
{
	class BinaryReader
	{
	private:
		std::vector<uint8_t> buffer;
		uint64_t position = 0;


		std::fstream basestream;

		bool isBigEndian = dc::SYSTEM_IS_BIG_ENDIAN();
		bool isBigEndianSystem = dc::SYSTEM_IS_BIG_ENDIAN();

		uint32_t fileSize = 0;

	public:


		void loadFile(const std::string& filepath);
		void loadFromMemory(const std::vector<uint8_t>& data);


		void close();

		bool isOpen() { return buffer.size() > 0; }


		
		void setPosition(uint64_t pos);
		uint64_t getPosition();


		uint32_t getLength();

		bool isEndOfStream() { return getLength() <= getPosition(); }


		bool isStreamBigEndian() { return isBigEndian; }

		void setStreamBigEndian(bool value) { isBigEndian = value; }

		char readChar();

		uint8_t readUInt8();
		int8_t readInt8();

		uint16_t readUInt16();
		int16_t readInt16();

		uint32_t readUInt32();
		int32_t readInt32();

		uint64_t readUInt64();
		int64_t readInt64();

		float readSingle();
		double readDouble();

		void readByteArray(uint8_t* arr, uint32_t count);

		std::string readString();

	};

}



#endif // !DUSKCOMET_SYSTEM_IO_BINARYREADER_HPP
