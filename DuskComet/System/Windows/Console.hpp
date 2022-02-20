#ifndef DUSKCOMET_SYSTEM_WINDOWS_CONSOLE__HPP
#define DUSKCOMET_SYSTEM_WINDOWS_CONSOLE__HPP

#include <cstdint>
#include <iostream>

#define NOMINMAX
#include <Windows.h>

namespace dc::Windows
{
	class Console
	{
	public:

		/// <summary>
		/// Redirect the STD stream to the Console
		/// </summary>
		/// <returns></returns>
		static bool redirectConsoleIO();

		/// <summary>
		/// Releases the console
		/// </summary>
		/// <returns></returns>
		static bool releaseConsole();

		/// <summary>
		/// Adjust the screen buffer
		/// </summary>
		static void adjustConsoleBuffer(std::uint16_t minLength);

		/// <summary>
		/// Attempt to attach to the parent process's console
		/// </summary>
		/// <param name="minLength"></param>
		/// <returns></returns>
		static bool attachParentConsole(std::uint16_t minLength);

		/// <summary>
		/// Creates a new console, will destroy any existing Console
		/// </summary>
		/// <returns></returns>
		static bool createNewConsole(std::uint16_t minLength);


		static bool isVisible();
		static void show();
		static void hide();

	};
}

#endif // !DUSKCOMET_SYSTEM_WINDOWS_CONSOLE__HPP
