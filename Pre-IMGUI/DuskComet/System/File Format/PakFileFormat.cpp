#include "PakFileFormat.hpp"
#include "../../Game.hpp"

#if __cpluscplus == 201703L || __cplusplus ==202002L
#include <filesystem>
#endif

#include "../IO/sha256.hpp"

namespace dc
{
	void PakFileFormat::readDirectory(const std::string& directory)
	{
		std::vector<std::string> fileNames;

		std::map<std::string, std::vector<std::uint8_t>> files;

#if __cplusplus == 199711L

#elif __cplusplus == 201103L

#elif __cplusplus == 201402L

#elif __cpluscplus == 201703L || __cplusplus ==202002L
		for (const auto& file : std::filesystem::recursive_directory_iterator(directory))
		{
			if (!file.is_directory())
			{
				std::string name = file.path().string().substr(directory.size());
				std::cout << "Found file: " << name << std::endl << "Hashed Name: " << sha256(name) << std::endl;
			}
		}



#endif
	}

	void writeDirectory(const std::string& directory)
	{

	}

	void readPakFile(const std::string& filepath)
	{

	}

	void writePakFile(const std::string& filepath)
	{

	}
}