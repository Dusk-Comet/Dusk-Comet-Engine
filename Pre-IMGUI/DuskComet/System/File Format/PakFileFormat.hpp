#ifndef DUSKCOMET_SYSTEM_FILE_FORMATS_PAKFILEFORMAT__HPP
#define DUSKCOMET_SYSTEM_FILE_FORMATS_PAKFILEFORMAT__HPP

#include <string>
#include <map>

namespace dc
{
	class PakFileFormat
	{
	private:
		std::string _filesystemLocation = "";

		std::map<std::uint64_t, std::string> _filenameDictionary;

		std::map<std::uint64_t, std::uint64_t> _fileDictionary;


	public:
		void readDirectory(const std::string& directory);
		void writeDirectory(const std::string& directory);


		void readPakFile(const std::string& filepath);
		void writePakFile(const std::string& filepath);


		uint32_t getFileCount();

		bool containsFilenameDictionary();




	};
}

#endif // !DUSKCOMET_SYSTEM_FILE_FORMATS_PAKFILEFORMAT__HPP
