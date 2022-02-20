#ifndef DCAPIW_FRAMEWORK__H
#define DCAPIW_FRAMEWORK__H


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files
#include <windows.h>

#include <Game.hpp>

#ifdef __cplusplus
extern "C" {
#endif

	uint32_t __declspec(dllexport) __cdecl isSystemBigEndian() { return (dc::SYSTEM_IS_BIG_ENDIAN() ? 1 : 0); }


#ifdef __cplusplus
}
#endif

#endif // !DCAPIW_FRAMEWORK__H
