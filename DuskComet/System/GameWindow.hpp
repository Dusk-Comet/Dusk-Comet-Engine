#ifndef DUSKCOMET_SYSTEM_GAMEWINDOW__HPP
#define DUSKCOMET_SYSTEM_GAMEWINDOW__HPP

#include "Types/Vectors.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>

#include <string>

#include <vector>

#include "../Graphics/GUI/Panel.hpp"
#include "Event.hpp"

namespace dc
{
	class GameWindow;

	template<typename t>
	class GameWindowEventDispatcher : EventDispatcher<t>
	{

		friend class GameWindow;
	};


	class GameWindow
	{
	private:

		GameWindowEventDispatcher<EventArgs> _eventDispatcher;


		Size _internalResolution = Size(32, 32);
		Size _windowSize = Size(32, 32);
		std::unique_ptr<sf::RenderWindow> _sfRenderWindow = nullptr;

		std::string _engineBuildDate = __DATE__;
		std::string _engineBuildTime = __TIME__;
		std::string _windowTitle = "Dusk Comet Game Window";
		sf::Font _fontsCascadiaMono = sf::Font();

		sf::Text _displayDebugText = sf::Text();

		bool _windowBorder = true;
		bool _freeFormSizing = true;
		bool _closeButton = true;
		bool _fullscreen = false;
		bool _running = false;

		
		uint32_t createSFVideoMode();

		void createSFRenderWindow();

	public:
#pragma region Events
		Event<EventArgs> onFocusGained;
		Event<EventArgs> onFocusLost;
#pragma endregion

		sf::Font& getFont();




		/// <summary>
		/// Initialize the game enviroment
		/// </summary>
		/// <returns></returns>
		bool initialize();


		/// <summary>
		/// Create/Recreate the window context
		/// </summary>
		/// <param name="windowTitle"></param>
		void createGameWindow(const std::string& windowTitle, Size internalResolution, bool windowBorder = true, bool freeFormResize = true, bool closeButton = true);




		/// <summary>
		/// Run the current GameWindow gameloop.
		/// </summary>
		void run();

		/// <summary>
		/// Is the current GameWindow context valid?
		/// </summary>
		/// <returns></returns>
		bool isRenderContextValid();

		/// <summary>
		/// Sets the current GameWindow title
		/// </summary>
		/// <param name="name"></param>
		void setWindowTitle(const std::string& name);
		/// <summary>
		/// Gets the current GameWindow title
		/// </summary>
		/// <returns></returns>
		std::string getWindowTitle();


		/// <summary>
		/// Set the current GameWindow size
		/// </summary>
		/// <param name="size"></param>
		void setWindowSize(const Size& size);
		/// <summary>
		/// Gets the current GameWindow size
		/// </summary>
		/// <returns></returns>
		Size getWindowSize();


		/// <summary>
		/// Set whether the current GameWindow should be fullscreen.
		/// <para>This will save your window settings and re-apply them whenever fullscreen is turned off.</para>
		/// </summary>
		void setWindowFullScreen(const bool& value);
		/// <summary>
		/// Is the current GameWindow fullscreen?
		/// </summary>
		/// <returns></returns>
		bool getWindowFullScreen();


		/// <summary>
		/// Should the current GameWindow close?
		/// </summary>
		void setWindowIsOpen(const bool& value);
		/// <summary>
		/// Is the current GameWindow in the process of closing?
		/// </summary>
		/// <returns></returns>
		bool getWindowIsOpen();


		/// <summary>
		/// Is the user allowed to freely resize the GameWindow?
		/// </summary>
		/// <returns></returns>
		bool getAllowFreeWindowSizing();
		/// <summary>
		/// Set whether the user is allowed to freely resize the GameWindow.
		/// <para>THIS WILL CLOSE AND RE-OPEN THE WINDOW CONTEXT.</para>
		/// </summary>
		void setAllowFreeWindowSizing(const bool& value);


	};
}
#endif // !DUSKCOMET_SYSTEM_GAMEWINDOW__HPP
