#ifndef DUSKCOMET_SYSTEM_PAKFILESYSTEM__HPP
#define DUSKCOMET_SYSTEM_PAKFILESYSTEM__HPP

#include <string>
namespace dc
{
	class PakFileSystem
	{
	private:
		std::string _appDataPath = "";
		bool _usingAppDataFolder = false;
		bool _initialized = false;


		bool does_Filesystem_File_Exist(const std::string& path);
		bool does_Filesystem_Directory_Exist(const std::string& path);

	public:
		bool initialize(std::string additionalLookupPaths[], const int& pathAmount);



		std::string getAppDataPath();
		bool isUsingAppDataFolder();
	};
}
#endif // !DUSKCOMET_SYSTEM_PAKFILESYSTEM__HPP
