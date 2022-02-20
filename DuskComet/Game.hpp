#ifndef DUSKCOMET_GAME__HPP
#define DUSKCOMET_GAME__HPP


#include <cstdint>


#if defined WIN32 || defined WIN64

#ifdef SFML_STATIC
#define NOMINMAX
#endif // SFML_STATIC

#include <Windows.h>
#endif // WIN32 || WIN64

#include <string>
#include <iostream>

#pragma region Pre-Processor Definitions

#define DC_CONSTANTS_FILESYSTEM_APPDATA_FILE_NAME std::string("AppData")
#define DC_CONSTANTS_FILESYSTEM_APPDATA_FILE_EXT std::string(".pak")

#define DC_CONSTANTS_FILESYSTEM_APPDATA_FULLNAME DC_CONSTANTS_FILESYSTEM_APPDATA_FILE_NAME + DC_CONSTANTS_FILESYSTEM_APPDATA_FILE_EXT

#pragma endregion

#include "System/Event.hpp"
#include "System/PakFileSystem.hpp"
#include "System/GameWindow.hpp"

namespace dc
{
#pragma region Constant Expressions
	enum class CPPVersions
	{
		CPP_PRE98 = 1,
		CPP_98 = 199711L,
		CPP_11 = 201103L,
		CPP_14 = 201402L,
		CPP_17 = 201703L,
		CPP_20 = 202002L
	};
	constexpr CPPVersions ENGINE_CPP_VERSION()
	{
#if __cplusplus == 199711L
		return CPPVersions::CPP_98;
#elif __cplusplus == 201103L
		return CPPVersions::CPP_11;
#elif __cplusplus == 201402L
		return CPPVersions::CPP_14;
#elif __cpluscplus == 201703L
		return CPPVersions::CPP_17;
#elif __cplusplus == 202002L
		return CPPVersions::CPP_20;
#endif
		return CPPVersions::CPP_PRE98;
	}

	constexpr bool SYSTEM_IS_BIG_ENDIAN()
	{
		union {
			uint32_t i;
			char c[4];
		} temp = { 0x01020304 };
		return temp.c[0] == 0x1;
	}

#pragma endregion
	class Game
	{
	private:

		static bool s_initSuccess;

	public:
		static void initialize();
		static bool getInitializeResult();

		static dc::GameWindow gameWindow;
		static dc::PakFileSystem pakFileSystem;

	};
}
#endif // !DUSKCOMET_GAME__HPP
