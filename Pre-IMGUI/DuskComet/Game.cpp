#include "Game.hpp"

#if __cplusplus >= 201703L //introduces C++ <filesystem>
#include <filesystem>
#endif

#if defined WIN32 || defined WIN64
#include <ShlObj.h>
#endif // WIN32 || WIN64

#include <vector>

#include "System/File Format/PakFileFormat.hpp"

dc::Game dc::Game::_instance = dc::Game();

namespace dc
{
	bool Game::getInitializeResult()
	{
		return Game::binitSuccess;
	}

	void Game::initialize()
	{
		std::vector<std::string> additonalPaths;

#if defined WIN32 || defined WIN64
		PWSTR documentsPath;
		SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, NULL, &documentsPath);

		std::wstring wStrPath = std::wstring(documentsPath);

		std::string documentsDir = std::string(wStrPath.begin(), wStrPath.end()) + "\\DuskComet\\PC\\";

		additonalPaths.push_back(documentsDir);

		CoTaskMemFree(documentsPath);
#endif // WIN64 || WIN32

		PakFileFormat format;
		format.readDirectory(documentsDir);

		if (Game::pakFileSystem().initialize(additonalPaths.data(), additonalPaths.size()))
		{

		}



		Game::binitSuccess = true;
	}



}