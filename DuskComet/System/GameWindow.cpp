#include "GameWindow.hpp"

#include "../Resources/Fonts/CascadiaMono.hpp"

#include "../Game.hpp"

#include "../Graphics/GUI/Button.hpp"
#include "../Graphics/GUI/Textbox.hpp"
#include "../Graphics/GUI/Checkbox.hpp"

#include "../Imgui/imgui.h"
#include "../Imgui-SFML/imgui-SFML.h"


namespace dc
{
#pragma region Private

	uint32_t GameWindow::createSFVideoMode()
	{
		uint32_t returnVar = sf::Style::None;

		if (_fullscreen)
		{
			return sf::Style::Fullscreen;
		}

		if (_windowBorder)
			returnVar |= sf::Style::Titlebar;

		if (_freeFormSizing)
			returnVar |= sf::Style::Resize;
		
		if (_closeButton)
			returnVar |= sf::Style::Close;

		return returnVar;
	}

	void GameWindow::createSFRenderWindow()
	{
		if (_sfRenderWindow == nullptr)
			return;

		std::string title = this->_windowTitle;

		if (dc::Game::instance().pakFileSystem().isUsingAppDataFolder())
			title += " (Using AppData Folder)";
		this->_sfRenderWindow->create
		(
			sf::VideoMode(this->_internalResolution.x, this->_internalResolution.y),
			title,
			this->createSFVideoMode()
		);


	}
#pragma endregion

#pragma region Public

	sf::Font& GameWindow::getFont()
	{
		return this->_fontsCascadiaMono;
	}


	bool GameWindow::initialize()
	{
		if (this->_sfRenderWindow == nullptr)
		{
			this->_sfRenderWindow = std::make_unique<sf::RenderWindow>();

			_fontsCascadiaMono.loadFromMemory(dc::Resources::RegularRawData, dc::Resources::RegularRawDataLength);

			_displayDebugText.setFont(_fontsCascadiaMono);
			_displayDebugText.setCharacterSize(11);

			return true;
		}
		else
			return false;
	}

	void GameWindow::createGameWindow(const std::string& windowTitle, Size internalResolution, bool windowBorder, bool freeFormResize, bool closeButton)
	{
		if (!this->isRenderContextValid())
			return;


		this->_windowTitle = windowTitle;
		this->_internalResolution = internalResolution;
		this->_windowBorder = windowBorder;
		this->_freeFormSizing = freeFormResize;
		this->_closeButton = closeButton;
		this->createSFRenderWindow();

		_windowSize = dc::Size(this->_sfRenderWindow->getSize().x, this->_sfRenderWindow->getSize().y);

		ImGui::SFML::Init(*this->_sfRenderWindow);
	}

	void GameWindow::run()
	{
		if (_running) //prevent recursive badness
			return;

		_running = true;

		sf::Clock deltaClock;
		bool fullscreenTempBool = false;
		while (this->getWindowIsOpen())
		{
			sf::Event windowEvent;
			while (this->_sfRenderWindow->pollEvent(windowEvent))
			{
				ImGui::SFML::ProcessEvent(*this->_sfRenderWindow, windowEvent);

				switch (windowEvent.type)
				{
				case sf::Event::GainedFocus:
					_eventDispatcher.invokeEvent(this->onFocusGained, EventArgs());
					break;
				case sf::Event::LostFocus:
					_eventDispatcher.invokeEvent(this->onFocusLost, EventArgs());
						break;
				case sf::Event::Closed:
					this->setWindowIsOpen(false);
					continue;
					break;
				case sf::Event::TextEntered:

					break;
				case sf::Event::KeyPressed:

					break;
				case sf::Event::KeyReleased:

					break;
				case sf::Event::MouseButtonPressed:

					break;
				case sf::Event::MouseButtonReleased:

						break;
				case sf::Event::MouseMoved:
					//scale the mouse pos
					float xScale = ((float)this->_internalResolution.x) / (this->_sfRenderWindow->getSize().x);
					float yScale = ((float)this->_internalResolution.y) / (this->_sfRenderWindow->getSize().y);

					break;
				}
			}

			ImGui::SFML::Update(*this->_sfRenderWindow, deltaClock.restart());

			this->_sfRenderWindow->clear(sf::Color(0xFF, 0x00, 0xFF, 0xFF));

			ImGui::Begin("Dusk Comet Dev Menu");
			
			if (ImGui::BeginTabBar("DevMenu#TabBar"))
			{
				if (ImGui::BeginTabItem("General"))
				{
					ImGui::Text("Tab 1");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Options"))
				{


					if (ImGui::Checkbox("Fullscreen", &_fullscreen))
					{
						_fullscreen = !_fullscreen;

						this->setWindowFullScreen(!_fullscreen);
					}

					ImGui::Text("Tab 2");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc"))
				{
					ImGui::Text("Tab 3");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Info"))
				{
					ImGui::Text(std::string(std::string("Engine Build Date: ") + this->_engineBuildDate + " " + _engineBuildTime).c_str());
					ImGui::Text(std::string(std::string("Target Framerate: 60 FPS")).c_str());
					auto winSize = ImGui::GetWindowSize();


					ImGui::DrawLine(sf::Vector2f(0, 0), sf::Vector2f(winSize.x, 0), sf::Color::White);
					auto textWidth = ImGui::CalcTextSize(":::: System Information ::::").x;
					ImGui::SetCursorPosX((winSize.x - textWidth) * 0.5f);
					ImGui::Text(":::: System Information ::::");
					ImGui::DrawLine(sf::Vector2f(0, 0), sf::Vector2f(winSize.x, 0), sf::Color::White);

#if defined WIN32
					ImGui::Text(std::string("System: Windows x32").c_str());
#endif
#if defined WIN64
					ImGui::Text(std::string("System: Windows x64").c_str());
#endif
					ImGui::DrawLine(sf::Vector2f(0, 0), sf::Vector2f(winSize.x, 0), sf::Color::White);
					textWidth = ImGui::CalcTextSize(":::: Graphics Information ::::").x;
					ImGui::SetCursorPosX((winSize.x - textWidth) * 0.5f);
					ImGui::Text(":::: Graphics Information ::::");
					ImGui::DrawLine(sf::Vector2f(0, 0), sf::Vector2f(winSize.x, 0), sf::Color::White);
					ImGui::Text(std::string("Render Backend: SFML - 2.5.1").c_str());
					ImGui::Text(std::string("Max Texture Size: " + std::string(std::to_string(sf::Texture::getMaximumSize())) + "^2 pixels").c_str());

					ImGui::EndTabItem();
				}
			}
			ImGui::EndTabBar();

			ImGui::End();

			ImGui::SFML::Render(*this->_sfRenderWindow);
			this->_sfRenderWindow->draw(this->_displayDebugText);
			this->_sfRenderWindow->display();
		}


		this->_sfRenderWindow->setActive(false);

		_running = false;

		ImGui::SFML::Shutdown();
	}

	bool GameWindow::isRenderContextValid()
	{
		return _sfRenderWindow != nullptr;
	}




	void GameWindow::setWindowSize(const Size& size)
	{
		if (!this->isRenderContextValid())
			return;
		this->_sfRenderWindow->setSize(sf::Vector2u(size.x, size.y));
		this->_sfRenderWindow->setView(sf::View(sf::FloatRect(0, 0, size.x, size.y)));
		_windowSize = dc::Size(this->_sfRenderWindow->getSize().x, this->_sfRenderWindow->getSize().y);
	}
	Size GameWindow::getWindowSize()
	{
		if (!this->isRenderContextValid())
			return Size(0, 0);

		auto size = this->_sfRenderWindow->getSize();

		return Size(size.x, size.y);
	}



	void GameWindow::setWindowTitle(const std::string& name)
	{
		_windowTitle = name;
		if (this->isRenderContextValid())
		{
			this->_sfRenderWindow->setTitle(_windowTitle);
		}
	}
	std::string GameWindow::getWindowTitle()
	{
		return _windowTitle;
	}

	void GameWindow::setWindowFullScreen(const bool& value)
	{

		auto beforeValue = this->getWindowFullScreen();

		if (!beforeValue)
			_windowSize = dc::Size(this->_sfRenderWindow->getSize().x, this->_sfRenderWindow->getSize().y);


		this->_fullscreen = value;

		if (this->getWindowFullScreen())
		{
			if (!beforeValue)
			{
				this->createSFRenderWindow();

			}
		}
		else
		{
			if (beforeValue)
			{
				this->createSFRenderWindow();
				this->setWindowSize(this->_windowSize);
			}
		}
	}

	bool GameWindow::getWindowFullScreen()
	{
		return this->_fullscreen;
	}

	void GameWindow::setWindowIsOpen(const bool& value)
	{
		if (!isRenderContextValid())
			return;

		if (!value)
			_sfRenderWindow->close();
	}
	bool GameWindow::getWindowIsOpen()
	{
		if (!isRenderContextValid())
			return false;

		return _sfRenderWindow->isOpen();
	}



	bool GameWindow::getAllowFreeWindowSizing()
	{
		if (!isRenderContextValid())
			return false;

		return this->_freeFormSizing;
	}
	void GameWindow::setAllowFreeWindowSizing(const bool& value)
	{
		if (!isRenderContextValid())
			return;

		auto beforeValue = getAllowFreeWindowSizing();

		this->_freeFormSizing = value;

		if (this->_freeFormSizing)
		{
			if (beforeValue)
				createSFRenderWindow();
		}
		else
		{
			if (!beforeValue)
				createSFRenderWindow();
			
		}
	}
#pragma endregion
}