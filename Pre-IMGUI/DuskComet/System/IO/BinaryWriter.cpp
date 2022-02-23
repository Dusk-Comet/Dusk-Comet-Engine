#include "BinaryWriter.hpp"

#include "../../Game.hpp"


namespace dc
{

	BinaryWriter::BinaryWriter()
	{

	}
	//BinaryWriter::BinaryWriter(std::string filepath)
	//{
	//	basestream.open(filepath, std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);

	//	if (!basestream.is_open())
	//	{
	//		std::cout << "Unable to create BinaryWriter on file: \"" << filepath << "\"" << std::endl;
	//		return;
	//	}


	//	//prevent whitespace skipping
	//	basestream >> std::noskipws;

	//	//get the filesize
	//	if (basestream.is_open())
	//	{
	//		uint32_t pos = basestream.tellg();
	//		basestream.seekg(0, std::ios::beg);
	//		auto fSize = basestream.tellg();
	//		basestream.seekg(0, std::ios::end);
	//		fSize = basestream.tellg() - fSize;
	//		this->fileSize = fSize;
	//	}

	//}

	void BinaryWriter::setPosition(uint64_t pos)
	{
		this->position = pos;
	}
	uint64_t BinaryWriter::getPosition() 
	{ 
		return this->position;
	}


	uint64_t BinaryWriter::getLength()
	{
		return buffer.size();
	}

	std::vector<uint8_t> BinaryWriter::getBuffer()
	{
		return std::vector<uint8_t>(this->buffer);
	}

	void BinaryWriter::close()
	{
		buffer.clear();
		buffer.shrink_to_fit();

		//basestream.clear();

		//basestream.close();

		isBigEndian = isBigEndianSystem;
		fileSize = 0;
	}





	void BinaryWriter::write(std::uint8_t value)
	{

		std::uint8_t arr[1];
		arr[0] = value;
		this->write(arr, 1);
	}
	void BinaryWriter::write(std::int8_t value)
	{

		std::uint8_t arr[1];
		arr[0] = value;
		this->write(arr, 1);
	}

	void BinaryWriter::write(std::uint16_t value)
	{


		union ushort_u
		{
			std::uint8_t arr[sizeof(std::uint16_t)];
			std::uint16_t value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(std::uint16_t));


		this->write(temp_u.arr, sizeof(std::uint16_t));
	}
	void BinaryWriter::write(std::int16_t value)
	{


		union short_u
		{
			std::uint8_t arr[sizeof(std::int16_t)];
			std::int16_t value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(std::int16_t));


		this->write(temp_u.arr, sizeof(std::int16_t));
	}


	void BinaryWriter::write(std::uint32_t value)
	{


		union uint_u
		{
			std::uint8_t arr[sizeof(std::uint32_t)];
			std::uint32_t value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(std::uint32_t));


		this->write(temp_u.arr, sizeof(std::uint32_t));
	}
	void BinaryWriter::write(std::int32_t value)
	{


		union int_u
		{
			std::uint8_t arr[sizeof(std::int32_t)];
			std::int32_t value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(std::int32_t));


		this->write(temp_u.arr, sizeof(std::int32_t));
	}


	void BinaryWriter::write(std::uint64_t value)
	{

		union ulong_u
		{
			std::uint8_t arr[sizeof(std::uint64_t)];
			std::uint64_t value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(std::uint64_t));


		this->write(temp_u.arr, sizeof(std::uint64_t));
	}
	void BinaryWriter::write(std::int64_t value)
	{

		union long_u
		{
			std::uint8_t arr[sizeof(std::int64_t)];
			std::int64_t value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(std::int64_t));


		this->write(temp_u.arr, sizeof(std::int64_t));
	}

	void BinaryWriter::write(float value)
	{


		union float_u
		{
			std::uint8_t arr[sizeof(float)];
			float value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(float));


		this->write(temp_u.arr, sizeof(float));
	}
	void BinaryWriter::write(double value)
	{


		union double_u
		{
			std::uint8_t arr[sizeof(double)];
			double value;
		} temp_u;

		temp_u.value = value;

		//if there is a mismatch we need to reverse the endianess
		if (isBigEndian != isBigEndianSystem)
			std::reverse(temp_u.arr, temp_u.arr + sizeof(double));


		this->write(temp_u.arr, sizeof(double));
	}

	void BinaryWriter::write(uint8_t arr[], uint32_t size)
	{
		
		if (size + position > this->buffer.size())
		{
			buffer.resize(size + position);
		}

		std::copy(arr, arr + size, buffer.begin() + position);

		this->position += size;
	}

	void BinaryWriter::write(std::string value)
	{
		for (char c : value)
		{
			this->write((uint8_t)c);
		}
		this->write((uint8_t)0x00);
	}
}