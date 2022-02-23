#include "BinaryReader.hpp"

#include "../../Game.hpp"

namespace dc
{
	void BinaryReader::loadFile(const std::string& filepath)
	{
		this->close();

		if (dc::Game::instance().pakFileSystem().isUsingAppDataFolder())
		{
			if (!basestream.is_open())
			{
				basestream.open(filepath, std::ios::in | std::ios::binary);

				//prevent whitespace skipping
				basestream >> std::noskipws;

				//get the filesize
				if (basestream.is_open())
				{
					uint32_t pos = basestream.tellg();
					basestream.seekg(0, std::ios::beg);
					auto fSize = basestream.tellg();
					basestream.seekg(0, std::ios::end);
					fSize = basestream.tellg() - fSize;
					this->fileSize = fSize;
					//return to the beginning of the file
					basestream.seekg(0, std::ios::beg);
				}
			}
		}
		else
		{

		}
	}

	void BinaryReader::loadFromMemory(const std::vector<uint8_t>& data)
	{
		this->close();

		this->buffer = std::vector<uint8_t>(data);
	}


	void BinaryReader::close()
	{
		buffer.clear();
		buffer.shrink_to_fit();

		if (basestream.is_open())
		{
			basestream.clear();
			basestream.close();
		}

		isBigEndian = isBigEndianSystem;
		fileSize = 0;
	}


	void BinaryReader::setPosition(uint64_t pos)
	{
		this->position = pos;
	}

	uint64_t BinaryReader::getPosition()
	{
		return this->position;
	}

	uint32_t  BinaryReader::getLength()
	{
		if (basestream.is_open())
			return fileSize;
		
		else
			return buffer.size();
		
	}

	char BinaryReader::readChar()
	{
		char c = this->readInt8();
		return c;
	}


	uint8_t BinaryReader::readUInt8()
	{
		if (basestream.is_open())
		{
			char temp[1];
			basestream.read(temp, 1);
			position++;
			return (uint8_t)temp[0];
		}
		else
		{
			char temp;
			temp = buffer[position];
			position++;
			return (uint8_t)temp;
		}
	}

	int8_t BinaryReader::readInt8()
	{
		if (basestream.is_open())
		{
			char temp[1];
			basestream.read(temp, 1);
			position++;
			return (int8_t)temp[0];
		}
		else
		{
			char temp;
			temp = buffer[position];
			position++;
			return (int8_t)temp;
		}
	}

	uint16_t BinaryReader::readUInt16()
	{

		union ushort_u
		{
			uint8_t arr[2];
			uint16_t value;
		};
		ushort_u temp;

		this->readByteArray(temp.arr, 2);

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + 2);
		}

		return temp.value;

	}

	int16_t BinaryReader::readInt16()
	{


		union short_u
		{
			uint8_t arr[2];
			int16_t value;
		};
		short_u temp;

		this->readByteArray(temp.arr, 2);

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + 2);
		}

		return temp.value;
	}

	uint32_t BinaryReader::readUInt32()
	{
		union uint_u
		{
			uint8_t arr[4];
			uint32_t value;
		};
		uint_u temp;

		this->readByteArray(temp.arr, 4);

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + 4);
		}

		return temp.value;
	}

	int32_t BinaryReader::readInt32()
	{
		union int_u
		{
			uint8_t arr[4];
			int32_t value;
		};
		int_u temp;

		this->readByteArray(temp.arr, 4);

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + 4);
		}

		return temp.value;
	}

	uint64_t BinaryReader::readUInt64()
	{
		union ulong_u
		{
			uint8_t arr[8];
			uint64_t value;
		};
		ulong_u temp;

		this->readByteArray(temp.arr, 8);

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + 8);
		}

		return temp.value;
	}

	int64_t BinaryReader::readInt64()
	{

		union long_u
		{
			uint8_t arr[8];
			int64_t value;
		};
		long_u temp;

		this->readByteArray(temp.arr, 8);

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + 8);
		}

		return temp.value;
	}

	float BinaryReader::readSingle()
	{
		union float_u
		{
			uint8_t arr[sizeof(float)];
			float value;
		};
		float_u temp;

		this->readByteArray(temp.arr, sizeof(float));

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + sizeof(float));
		}

		return temp.value;
	}

	double BinaryReader::readDouble()
	{

		union double_u
		{
			uint8_t arr[sizeof(double)];
			float value;
		};
		double_u temp;

		this->readByteArray(temp.arr, sizeof(double));

		//if there is a mismatch, we need to reverse the stuff
		if (this->isBigEndian != isBigEndianSystem)
		{
			std::reverse(temp.arr, temp.arr + sizeof(double));
		}

		return temp.value;
	}

	void BinaryReader::readByteArray(uint8_t* arr, uint32_t count)
	{
		if (basestream.is_open())
		{
			basestream.read((char*)arr, count);
		}
		else
		{
			std::memcpy(arr, buffer.data() + position, count);
		}
		this->position += count;
	}


	std::string BinaryReader::readString()
	{
		std::string buffer;

		char c = (char)readInt8();

		while (c != (char)0x00)
		{
			buffer += c;
			c = (char)readInt8();
		}

		return buffer;
	}

}