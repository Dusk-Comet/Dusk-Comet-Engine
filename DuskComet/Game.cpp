#include "Game.hpp"

#if __cplusplus >= 201703L //introduces C++ <filesystem>
#include <filesystem>
#endif

#if defined WIN32 || defined WIN64
#include <ShlObj.h>
#endif // WIN32 || WIN64

#include <vector>

#include "System/File Format/PakFileFormat.hpp"

bool dc::Game::s_initSuccess = false;
dc::GameWindow dc::Game::gameWindow = dc::GameWindow();
dc::PakFileSystem dc::Game::pakFileSystem = dc::PakFileSystem();

namespace dc
{
	bool Game::getInitializeResult()
	{
		return Game::s_initSuccess;
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

		if (Game::pakFileSystem.initialize(additonalPaths.data(), additonalPaths.size()))
		{

		}



		Game::s_initSuccess = true;
	}



}