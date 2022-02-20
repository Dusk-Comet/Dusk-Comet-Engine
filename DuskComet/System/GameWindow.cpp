#include "GameWindow.hpp"

#include "../Resources/Fonts/CascadiaMono.hpp"

#include "../Game.hpp"

#include "../Graphics/GUI/Button.hpp"
#include "../Graphics/GUI/Textbox.hpp"
#include "../Graphics/GUI/Checkbox.hpp"
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

		if (dc::Game::pakFileSystem.isUsingAppDataFolder())
			title += " (Using AppData Folder)";
		this->_sfRenderWindow->create
		(
			sf::VideoMode(this->_internalResolution.x, this->_internalResolution.y),
			title,
			this->createSFVideoMode()
		);


		_basePanel.setControlSize(this->_internalResolution);

	}
#pragma endregion

#pragma region Public

	sf::Font& GameWindow::getFont()
	{
		return this->_fontsCascadiaMono;
	}


	void GameWindow::setFocusedPanel(Panel* panelHandle)
	{
		this->_focusedPanel = panelHandle;
	}

	Panel* GameWindow::getFocusedPanel()
	{
		return this->_focusedPanel;
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
	}

	void GameWindow::run()
	{
		if (_running) //prevent recursive badness
			return;

		_running = true;


		this->_basePanel.addChild("button1", new Button());
		this->_basePanel.addChild("textbox1", new Textbox());
		this->_basePanel.addChild("checkbox1", new Checkbox());
		while (this->getWindowIsOpen())
		{
			sf::Event windowEvent;
			while (this->_sfRenderWindow->pollEvent(windowEvent))
			{
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
					_basePanel.setTextEntered(windowEvent.text.unicode);
					break;
				case sf::Event::KeyPressed:
					_basePanel.setKeyPressed(windowEvent.key.code, windowEvent.key.alt, windowEvent.key.control, windowEvent.key.shift);
					break;
				case sf::Event::KeyReleased:
					_basePanel.setKeyReleased(windowEvent.key.code, windowEvent.key.alt, windowEvent.key.control, windowEvent.key.shift);
					break;
				case sf::Event::MouseButtonPressed:
					_basePanel.setMousePressed((dc::MouseButtons)((int)windowEvent.mouseButton.button));
					break;
				case sf::Event::MouseButtonReleased:
					_basePanel.setMouseReleased((dc::MouseButtons)((int)windowEvent.mouseButton.button));
						break;
				case sf::Event::MouseMoved:
					//scale the mouse pos
					float xScale = ((float)this->_internalResolution.x) / (this->_sfRenderWindow->getSize().x);
					float yScale = ((float)this->_internalResolution.y) / (this->_sfRenderWindow->getSize().y);

					_basePanel.setMousePos(dc::Point(windowEvent.mouseMove.x, windowEvent.mouseMove.y));
					break;
				}
			}
			this->_sfRenderWindow->clear(sf::Color(0xFF, 0x00, 0xFF, 0xFF));


			this->_displayDebugText.setString(std::string("Engine Build Date: ") + this->_engineBuildDate + " " + _engineBuildTime);

			_basePanel.invalidate();

			_basePanel.update();

			this->_sfRenderWindow->draw(_basePanel);

			this->_sfRenderWindow->draw(this->_displayDebugText);
			this->_sfRenderWindow->display();
		}
		this->_focusedPanel = nullptr;
		this->_basePanel.Dispose();


		this->_sfRenderWindow->setActive(false);

		_running = false;
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
		this->_basePanel.setControlSize(size);
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
		this->_fullscreen = value;

		if (this->getWindowFullScreen())
		{
			if (!beforeValue)
				this->createSFRenderWindow();
		}
		else
		{
			if (beforeValue)
				this->createSFRenderWindow();
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