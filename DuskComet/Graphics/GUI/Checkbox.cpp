#include "Checkbox.hpp"

#include "../../Game.hpp"

namespace dc
{
	Checkbox::Checkbox()
	{
		_displayText.setFont(dc::Game::gameWindow.getFont());
		_displayText.setPosition(1, 1);


		_displayText.setCharacterSize(11);
		_displayText.setString("dcCheckbox");

		this->setControlPosition(dc::Point(128, 128));
		this->invalidate();
	}


	void Checkbox::onDispose()
	{
		_displayText.setString(std::string());
		_triVerts.clear();

	}

	void Checkbox::onMouseMove(MouseMoveEventArgs e)
	{

	}




	void Checkbox::onPositionChanged(GUIEventArgs e)
	{

	}
	void Checkbox::onSizeChanged(GUIEventArgs e)
	{

	}

	void Checkbox::onUpdate(GUIEventArgs e)
	{
		_triVerts.clear();

		sf::Color colorLightLight = sf::Color(this->_borderLightLight.x, this->_borderLightLight.y, this->_borderLightLight.z, this->_borderLightLight.w);
		sf::Color colorLight = sf::Color(this->_borderLight.x, this->_borderLight.y, this->_borderLight.z, this->_borderLight.w);
		sf::Color defaultColor = sf::Color(this->_defaultBackColor.x, this->_defaultBackColor.y, this->_defaultBackColor.z, this->_defaultBackColor.w);

		sf::Color colorDark = sf::Color(this->_borderDark.x, this->_borderDark.y, this->_borderDark.z, this->_borderDark.w);
		sf::Color colorDarkDark = sf::Color(this->_borderDarkDark.x, this->_borderDarkDark.y, this->_borderDarkDark.z, this->_borderDarkDark.w);


		int height = _displayText.getLocalBounds().height * 2;


		Rectangle DarkDarkBounds = Rectangle(getControlPosition().x, getControlPosition().y, 1, 1);
		Rectangle DarkBounds = Rectangle(getControlPosition().x, getControlPosition().y, height - 1, height - 1);
		Rectangle CheckBounds = Rectangle(getControlPosition().x, getControlPosition().y, height, height);
		Rectangle LightBounds = Rectangle(getControlPosition().x + 1, getControlPosition().y + 1, height - 1, height - 1);
		Rectangle LightLightBounds = Rectangle(getControlPosition().x + height - 1, getControlPosition().y + height - 1, 1, 1);


		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x, CheckBounds.y), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x + CheckBounds.z, CheckBounds.y), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x + CheckBounds.z, CheckBounds.y + CheckBounds.w), sf::Color(defaultColor)));

		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x + CheckBounds.z, CheckBounds.y + CheckBounds.w), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x, CheckBounds.y + CheckBounds.w), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x, CheckBounds.y), sf::Color(defaultColor)));

		CheckBounds = Rectangle(getControlPosition().x + 1, getControlPosition().y + 1, height - 2, height - 2);

		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x, DarkBounds.y), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x + DarkBounds.z, DarkBounds.y), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x + DarkBounds.z, DarkBounds.y + DarkBounds.w), sf::Color(colorDark)));

		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x + DarkBounds.z, DarkBounds.y + DarkBounds.w), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x, DarkBounds.y + DarkBounds.w), sf::Color(colorDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkBounds.x, DarkBounds.y), sf::Color(colorDark)));



		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x, LightBounds.y), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x + LightBounds.z, LightBounds.y), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x + LightBounds.z, LightBounds.y + LightBounds.w), sf::Color(colorLight)));

		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x + LightBounds.z, LightBounds.y + LightBounds.w), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x, LightBounds.y + LightBounds.w), sf::Color(colorLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightBounds.x, LightBounds.y), sf::Color(colorLight)));



		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x, DarkDarkBounds.y), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x + DarkDarkBounds.z, DarkDarkBounds.y), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x + DarkDarkBounds.z, DarkDarkBounds.y + DarkDarkBounds.w), sf::Color(colorDarkDark)));

		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x + DarkDarkBounds.z, DarkDarkBounds.y + DarkDarkBounds.w), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x, DarkDarkBounds.y + DarkDarkBounds.w), sf::Color(colorDarkDark)));
		_triVerts.append(sf::Vertex(sf::Vector2f(DarkDarkBounds.x, DarkDarkBounds.y), sf::Color(colorDarkDark)));


		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x, LightLightBounds.y), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x + LightLightBounds.z, LightLightBounds.y), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x + LightLightBounds.z, LightLightBounds.y + LightLightBounds.w), sf::Color(colorLightLight)));

		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x + LightLightBounds.z, LightLightBounds.y + LightLightBounds.w), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x, LightLightBounds.y + LightLightBounds.w), sf::Color(colorLightLight)));
		_triVerts.append(sf::Vertex(sf::Vector2f(LightLightBounds.x, LightLightBounds.y), sf::Color(colorLightLight)));

		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x, CheckBounds.y), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x + CheckBounds.z, CheckBounds.y), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x + CheckBounds.z, CheckBounds.y + CheckBounds.w), sf::Color(defaultColor)));

		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x + CheckBounds.z, CheckBounds.y + CheckBounds.w), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x, CheckBounds.y + CheckBounds.w), sf::Color(defaultColor)));
		_triVerts.append(sf::Vertex(sf::Vector2f(CheckBounds.x, CheckBounds.y), sf::Color(defaultColor)));






		this->setControlSize(dc::Size(height + _displayText.getString().getSize(), height));

		_displayText.setPosition(this->getControlPosition().x + height, this->getControlPosition().y);
	}

	void Checkbox::onPaint(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_triVerts);
		target.draw(_displayText);
	}

}