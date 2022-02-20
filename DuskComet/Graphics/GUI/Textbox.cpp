#include "Textbox.hpp"

#include <iostream>

#include "../../Game.hpp"


#define CHAR_BACKSPACE 0x8


#define CHAR_SIZE 6

namespace dc
{
	void Textbox::textbox_OnFocusGained(EventArgs e)
	{
		this->invalidate();
	}
	void Textbox::textbox_OnFocusLost(EventArgs e)
	{
		this->invalidate();
	}

	void Textbox::textbox_OnMouseEnter(EventArgs e)
	{
		this->setBackColor(dc::Color(0x33, 0x99, 0xff, 0xFF));
	}
	void Textbox::textbox_OnMouseLeave(EventArgs e)
	{
		this->setBackColor(dc::Color(0x2d, 0x2d, 0x30, 0xFF));
	}
	void Textbox::textbox_OnMouseButtonPressed(MouseButtonEventArgs e)
	{
		this->requestFocus();

		if (e.getMouseButton() == dc::MouseButtons::LEFT)
		{

			this->invalidate();
		}
	}
	void Textbox::textbox_OnMouseButtonReleased(MouseButtonEventArgs e)
	{
		if (e.getMouseButton() == dc::MouseButtons::LEFT)
		{

		}
	}

	Textbox::Textbox()
	{
		//first create functions we can use to subscribe
		std::function<void(EventArgs)> f_onFocusGainedFunc = std::bind(&Textbox::textbox_OnFocusGained, this, std::placeholders::_1);
		std::function<void(EventArgs)> f_onFocusLostFunc = std::bind(&Textbox::textbox_OnFocusLost, this, std::placeholders::_1);

		std::function<void(EventArgs)> f_onMouseEnter = std::bind(&Textbox::textbox_OnMouseEnter, this, std::placeholders::_1);
		std::function<void(EventArgs)> f_onMouseLeave = std::bind(&Textbox::textbox_OnMouseLeave, this, std::placeholders::_1);

		std::function<void(MouseButtonEventArgs)> f_onMouseButtonPressed = std::bind(&Textbox::textbox_OnMouseButtonPressed, this, std::placeholders::_1);
		std::function<void(MouseButtonEventArgs)> f_onMouseButtonReleased = std::bind(&Textbox::textbox_OnMouseButtonReleased, this, std::placeholders::_1);

		this->setBackColor(dc::Color(0x2d, 0x2d, 0x30, 0xFF));
		this->setControlSize(Size(32, 32));

		this->onFocusGained += f_onFocusGainedFunc;
		this->onFocusLost += f_onFocusLostFunc;

		this->onMouseEnter += f_onMouseEnter;
		this->onMouseLeave += f_onMouseLeave;

		this->onMouseButtonPressed += f_onMouseButtonPressed;
		this->onMouseButtonReleased += f_onMouseButtonReleased;

		_displayText.setFont(dc::Game::gameWindow.getFont());
		_displayText.setPosition(1, 1);


		_displayText.setCharacterSize(11);
		_displayText.setString("dcButton");

		auto bounds = _displayText.getLocalBounds();

		this->setControlPosition(dc::Point(32, 8));
		this->setControlSize(dc::Size(bounds.left + bounds.width + 6, bounds.top + bounds.height + 6));
	}

	void Textbox::onDispose()
	{
		this->_textureBuffer.clear();
		this->_textureBuffer.create(1, 1);

	}



	void Textbox::onMouseMove(MouseMoveEventArgs e)
	{

	}


	void Textbox::onTextEntered(TextEnteredEventArgs e)
	{
		uint32_t controlCharWidth = this->getControlSize().x / CHAR_SIZE;


		switch (e.getChar())
		{
		case CHAR_BACKSPACE:
		{
			auto partA = _displayText.getString().substring(0, this->_charPos + this->_controlCharOffset - 1);
			auto partB = _displayText.getString().substring(this->_charPos + this->_controlCharOffset);

			this->_displayText.setString(partA + partB);


			decrementCaret();
		}
			break;
		default:
		{
			auto partA = _displayText.getString().substring(0, this->_charPos + this->_controlCharOffset);
			auto partB = _displayText.getString().substring(this->_charPos + this->_controlCharOffset);

			this->_displayText.setString(partA + e.getChar() + partB);
			incrementCaret();
			//if (this->_charPos == controlCharWidth || this->_charPos + this->_controlCharOffset == this->_displayText.getString().getSize() - 1)
			//	incrementCaret();
		}
			break;
		}


		this->invalidate();
	}

	void Textbox::onKeyPressed(KeyButtonEventArgs e)
	{


		switch (e.getKeyCode())
		{
		case sf::Keyboard::Key::Right:
			incrementCaret();
			break;
		case sf::Keyboard::Key::Left:
			decrementCaret();
			break;
		default:
			break;
		}

	}

	void Textbox::onKeyReleased(KeyButtonEventArgs e)
	{

	}


	void Textbox::incrementCaret()
	{
		uint32_t controlCharWidth = this->getControlSize().x / CHAR_SIZE;

		if (this->_charPos + this->_controlCharOffset >= this->_displayText.getString().getSize())
		{
			this->invalidate();
			return;
		}

		if (this->_charPos != controlCharWidth)
		{
			this->_charPos++;
		}
		else
		{
			if (this->_controlCharOffset < (_displayText.getString().getSize() - controlCharWidth))
				this->_controlCharOffset++;
		}


		this->invalidate();

	}
	void Textbox::decrementCaret()
	{
		uint32_t controlCharWidth = this->getControlSize().x / CHAR_SIZE;


		if (this->_charPos == 0)
		{
			if (this->_controlCharOffset > 0)
				this->_controlCharOffset--;
		}
		else
		{
			if (this->_controlCharOffset > (_displayText.getString().getSize() - controlCharWidth))
			{
				this->_controlCharOffset = (_displayText.getString().getSize() - controlCharWidth);
			}
			else
				this->_charPos--;
		}



		this->invalidate();

	}


	void Textbox::onPositionChanged(GUIEventArgs e)
	{
		this->invalidate();
	}
	void Textbox::onSizeChanged(GUIEventArgs e)
	{
		this->invalidate();
	}

	void Textbox::onUpdate(GUIEventArgs e)
	{
		if (this->_textureBuffer.getSize().x != this->getControlSize().x || this->_textureBuffer.getSize().y != this->getControlSize().y)
		{
			if (this->getControlSize().x >= 1 && this->getControlSize().y >= 1)
				this->_textureBuffer.create(this->getControlSize().x, this->getControlSize().y);
			else
				this->_textureBuffer.create(4, 4);
		}


		_textureBuffer.clear(sf::Color(0x1e, 0x1c, 0x1d, 0xFF));

		_lineVerts.clear();

		sf::Color borderDarkDark = sf::Color(this->_borderDarkDark.getR(), this->_borderDarkDark.getG(), this->_borderDarkDark.getB(), this->_borderDarkDark.getA());
		sf::Color borderDark = sf::Color(this->_borderDark.getR(), this->_borderDark.getG(), this->_borderDark.getB(), this->_borderDark.getA());

		sf::Color borderlight = sf::Color(this->_borderLight.getR(), this->_borderLight.getG(), this->_borderLight.getB(), this->_borderLight.getA());
		sf::Color borderlightlight = sf::Color(this->_borderLightLight.getR(), this->_borderLightLight.getG(), this->_borderLightLight.getB(), this->_borderLightLight.getA());

		_lineVerts.append(sf::Vertex(sf::Vector2f(0, 0), borderDarkDark));
		_lineVerts.append(sf::Vertex(sf::Vector2f(1, 1), borderDarkDark));

		_lineVerts.append(sf::Vertex(sf::Vector2f(1, 0), borderDark));
		_lineVerts.append(sf::Vertex(sf::Vector2f(this->getControlSize().x - 1, 1), borderDark));

		_lineVerts.append(sf::Vertex(sf::Vector2f(0, 1), borderDark));
		_lineVerts.append(sf::Vertex(sf::Vector2f(1, this->getControlSize().y - 1), borderDark));



		_lineVerts.append(sf::Vertex(sf::Vector2f(1, this->getControlSize().y - 1), borderlight));
		_lineVerts.append(sf::Vertex(sf::Vector2f(this->getControlSize().x - 1, this->getControlSize().y), borderlight));

		_lineVerts.append(sf::Vertex(sf::Vector2f(this->getControlSize().x - 1, 1), borderlight));
		_lineVerts.append(sf::Vertex(sf::Vector2f(this->getControlSize().x, this->getControlSize().y - 1), borderlight));


		_lineVerts.append(sf::Vertex(sf::Vector2f(this->getControlSize().x - 1, this->getControlSize().y - 1), borderlightlight));
		_lineVerts.append(sf::Vertex(sf::Vector2f(this->getControlSize().x, this->getControlSize().y), borderlightlight));





		if (this->isFocused())
		{
			int offX = (CHAR_SIZE * this->_charPos);



			_lineVerts.append(sf::Vertex(sf::Vector2f((1 + ((int)offX)), 1), sf::Color::White));
			_lineVerts.append(sf::Vertex(sf::Vector2f((2 + ((int)offX)), this->getControlSize().y - 1), sf::Color::White));

			_displayText.setPosition(1 + (-CHAR_SIZE * (int32_t)this->_controlCharOffset), 1);
		}


		_textureBuffer.draw(_lineVerts);


		_textureBuffer.draw(_displayText);

		_spritePuppet.setPosition(sf::Vector2f(this->getControlWindowPosition().x, this->getControlWindowPosition().y));
		_textureBuffer.display();
		_spritePuppet.setTexture(_textureBuffer.getTexture());
		_spritePuppet.setTextureRect(sf::IntRect(0, 0, this->getControlSize().x, this->getControlSize().y));
	}

	void Textbox::onPaint(sf::RenderTarget& target, sf::RenderStates states) const
	{
		
		target.draw(_spritePuppet);
	}

	int Textbox::getGlyphSize(char& letter, sf::Font& font, int font_size)
	{
		return font.getGlyph(int(letter), font_size, false).advance;
	}
}