#include "Button.hpp"

#include <iostream>

#include "../../Game.hpp"

namespace dc
{
	void Button::button_OnFocusGained(EventArgs e)
	{

	}
	void Button::button_OnFocusLost(EventArgs e)
	{

	}

	void Button::button_OnMouseEnter(EventArgs e)
	{
		this->setBackColor(dc::Color(0x33, 0x99, 0xff, 0xFF));
	}
	void Button::button_OnMouseLeave(EventArgs e)
	{
		this->setBackColor(dc::Color(0x2d, 0x2d, 0x30, 0xFF));
	}
	void Button::button_OnMouseButtonPressed(MouseButtonEventArgs e)
	{
		this->requestFocus();

		if (e.getMouseButton() == dc::MouseButtons::LEFT)
		{
			this->_pressed = true;
			this->invalidate();
		}
	}
	void Button::button_OnMouseButtonReleased(MouseButtonEventArgs e)
	{
		if (e.getMouseButton() == dc::MouseButtons::LEFT)
		{
			if (this->_pressed)
			{
				this->_pressed = false;
				std::cout << "click!!" << std::endl;
				this->invalidate();
			}
		}
	}


	Button::Button()
	{
		//subscribe to our events!

		//first create functions we can use to subscribe
		std::function<void(EventArgs)> f_onFocusGainedFunc = std::bind(&Button::button_OnFocusGained, this, std::placeholders::_1);
		std::function<void(EventArgs)> f_onFocusLostFunc = std::bind(&Button::button_OnFocusLost, this, std::placeholders::_1);

		std::function<void(EventArgs)> f_onMouseEnter = std::bind(&Button::button_OnMouseEnter, this, std::placeholders::_1);
		std::function<void(EventArgs)> f_onMouseLeave = std::bind(&Button::button_OnMouseLeave, this, std::placeholders::_1);

		std::function<void(MouseButtonEventArgs)> f_onMouseButtonPressed = std::bind(&Button::button_OnMouseButtonPressed, this, std::placeholders::_1);
		std::function<void(MouseButtonEventArgs)> f_onMouseButtonReleased = std::bind(&Button::button_OnMouseButtonReleased, this, std::placeholders::_1);

		this->setBackColor(dc::Color(0x2d, 0x2d, 0x30, 0xFF));
		this->setControlSize(Size(32, 32));

		this->onFocusGained += f_onFocusGainedFunc;
		this->onFocusLost += f_onFocusLostFunc;

		this->onMouseEnter += f_onMouseEnter;
		this->onMouseLeave += f_onMouseLeave;

		this->onMouseButtonPressed += f_onMouseButtonPressed;
		this->onMouseButtonReleased += f_onMouseButtonReleased;

		_displayText.setFont(dc::Game::instance().gameWindow().getFont());

		_displayText.setCharacterSize(11);
		_displayText.setString("dcButton");

		auto bounds = _displayText.getLocalBounds();

		this->setControlPosition(dc::Point(32, 32));
		this->setControlSize(dc::Size(bounds.left + bounds.width + 6, bounds.top + bounds.height + 6));

	}

	void Button::onDispose() 
	{

	}



	void Button::onMouseMove(MouseMoveEventArgs e)
	{

	}



	void Button::onPositionChanged(GUIEventArgs e)
	{

	}
	void Button::onSizeChanged(GUIEventArgs e)
	{

	}

	void Button::drawBackground()
	{
		sf::Color colorLightLight = sf::Color(this->_borderLightLight.x, this->_borderLightLight.y, this->_borderLightLight.z, this->_borderLightLight.w);
		sf::Color colorLight = sf::Color(this->_borderLight.x, this->_borderLight.y, this->_borderLight.z, this->_borderLight.w);
		sf::Color defaultColor = sf::Color(this->_defaultBackColor.x, this->_defaultBackColor.y, this->_defaultBackColor.z, this->_defaultBackColor.w);

		sf::Color colorDark = sf::Color(this->_borderDark.x, this->_borderDark.y, this->_borderDark.z, this->_borderDark.w);
		sf::Color colorDarkDark = sf::Color(this->_borderDarkDark.x, this->_borderDarkDark.y, this->_borderDarkDark.z, this->_borderDarkDark.w);

		auto controlPosition = this->getControlPosition();
		auto controlSize = this->getControlSize();

		Rectangle LightLightBounds = Rectangle(controlPosition.x, controlPosition.y, 1, 1);
		Rectangle LightBounds = Rectangle(controlPosition.x, controlPosition.y, controlSize.x - 1, controlSize.y - 1);
		Rectangle TextBounds = Rectangle(controlPosition.x + 1, controlPosition.y + 1, controlSize.x - 2, controlSize.y - 2);
		Rectangle DarkBounds = Rectangle(controlPosition.x + 1, controlPosition.y + 1, controlSize.x - 1, controlSize.y - 1);
		Rectangle DarkDarkBounds = Rectangle(controlPosition.x + controlSize.x - 1, controlPosition.y + controlSize.y - 1, 1, 1);

		if (this->_pressed)
		{
			auto startLLB = LightLightBounds;
			auto startLB = LightBounds;
			auto startDB = DarkBounds;
			auto startDDB = DarkDarkBounds;


			LightLightBounds = startDDB;
			LightBounds = startDB;

			DarkBounds = startLB;
			DarkDarkBounds = startLLB;
		}

		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x				, DarkBounds.y				 ), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x + DarkBounds.z, DarkBounds.y				 ), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x + DarkBounds.z, DarkBounds.y + DarkBounds.w), sf::Color(colorDark)));

		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x + DarkBounds.z, DarkBounds.y + DarkBounds.w), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x				, DarkBounds.y + DarkBounds.w), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x				, DarkBounds.y				 ), sf::Color(colorDark)));



		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x				  , LightBounds.y				 ), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x + LightBounds.z, LightBounds.y				 ), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x + LightBounds.z, LightBounds.y + LightBounds.w), sf::Color(colorLight)));

		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x + LightBounds.z, LightBounds.y + LightBounds.w), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x				  , LightBounds.y + LightBounds.w), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x				  , LightBounds.y				 ), sf::Color(colorLight)));



		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x					, DarkDarkBounds.y				     ), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x + DarkDarkBounds.z, DarkDarkBounds.y					 ), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x + DarkDarkBounds.z, DarkDarkBounds.y + DarkDarkBounds.w), sf::Color(colorDarkDark)));

		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x + DarkDarkBounds.z, DarkDarkBounds.y + DarkDarkBounds.w), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x				    , DarkDarkBounds.y + DarkDarkBounds.w), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x				    , DarkDarkBounds.y					 ), sf::Color(colorDarkDark)));


		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x                     , LightLightBounds.y), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x + LightLightBounds.z, LightLightBounds.y), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x + LightLightBounds.z, LightLightBounds.y + LightLightBounds.w), sf::Color(colorLightLight)));

		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x + LightLightBounds.z, LightLightBounds.y + LightLightBounds.w), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x                     , LightLightBounds.y + LightLightBounds.w), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x                     , LightLightBounds.y), sf::Color(colorLightLight)));



		_triVerts.append(sf::Vertex(sf::Vector2f(TextBounds.x				, TextBounds.y				 ), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(TextBounds.x + TextBounds.z, TextBounds.y				 ), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(TextBounds.x + TextBounds.z, TextBounds.y + TextBounds.w), sf::Color(defaultColor)));

		_triVerts.append(sf::Vertex(sf::Vector2f(TextBounds.x + TextBounds.z, TextBounds.y + TextBounds.w), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(TextBounds.x				, TextBounds.y + TextBounds.w), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(TextBounds.x				, TextBounds.y				 ), sf::Color(defaultColor)));
	}

	void Button::onUpdate(GUIEventArgs e)
	{
		this->_triVerts.clear();

		auto bounds = _displayText.getLocalBounds();
		this->setControlSize(dc::Size(bounds.left + bounds.width + 6, bounds.top + bounds.height + 6));

		drawBackground();

		//Draw the border
		//End of drawing the border

		if (this->_pressed)
			_displayText.setPosition(this->getControlPosition().x + 3, this->getControlPosition().y + 2);
		else
			_displayText.setPosition(this->getControlPosition().x + 2, this->getControlPosition().y + 1);

	}

	void Button::onPaint(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_triVerts);

		target.draw(_displayText);
	}
}
