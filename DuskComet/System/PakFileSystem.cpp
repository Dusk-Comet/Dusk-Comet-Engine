#include "PakFileSystem.hpp"
#include "../Game.hpp"

#include <filesystem>
namespace dc
{
	bool PakFileSystem::does_Filesystem_File_Exist(const std::string& path)
	{
#if __cplusplus == 199711L

#elif __cplusplus == 201103L

#elif __cplusplus == 201402L

#elif __cpluscplus == 201703L
		return std::filesystem::exists(path);
#elif __cplusplus == 202002L
		return std::filesystem::exists(path);
#endif
	}

	bool PakFileSystem::does_Filesystem_Directory_Exist(const std::string& path)
	{
#if __cplusplus == 199711L

#elif __cplusplus == 201103L

#elif __cplusplus == 201402L

#elif __cpluscplus == 201703L
		return std::filesystem::is_directory(path);
#elif __cplusplus == 202002L
		return std::filesystem::is_directory(path);
#endif

	}


	bool PakFileSystem::initialize(std::string additionalLookupPaths[], const int& pathAmount)
	{
		//first lets search for anything in our root directory
		if (this->does_Filesystem_File_Exist(std::filesystem::current_path().string() + DC_CONSTANTS_FILESYSTEM_APPDATA_FULLNAME))
		{
			this->_usingAppDataFolder = false;

			//read and index the file here, then return true!
			return true;
		}

		if (this->does_Filesystem_Directory_Exist(std::filesystem::current_path().string() + DC_CONSTANTS_FILESYSTEM_APPDATA_FILE_NAME))
		{
			this->_usingAppDataFolder = true;


			return true;
		}


		for (int i = 0; i < pathAmount; i++)
		{
			if (this->does_Filesystem_File_Exist(additionalLookupPaths[i] + DC_CONSTANTS_FILESYSTEM_APPDATA_FULLNAME))
			{
				this->_usingAppDataFolder = false;
				this->_appDataPath = additionalLookupPaths[i];


				return true;
			}
			if (this->does_Filesystem_Directory_Exist(additionalLookupPaths[i] + DC_CONSTANTS_FILESYSTEM_APPDATA_FILE_NAME))
			{
				this->_usingAppDataFolder = true;
				this->_appDataPath = additionalLookupPaths[i];


				return true;
			}
		}

		return false;
	}



	std::string PakFileSystem::getAppDataPath()
	{
		return this->_appDataPath;
	}

	bool PakFileSystem::isUsingAppDataFolder()
	{
		return this->_usingAppDataFolder;
	}
}