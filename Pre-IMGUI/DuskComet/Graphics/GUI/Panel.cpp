#include "Panel.hpp"

#include "../../Game.hpp"


#include "../../System/Windows/Console.hpp"

namespace dc
{
	Point MouseMoveEventArgs::getMouseLocation()
	{
		return this->_mouseLocation;
	}


	MouseButtons MouseButtonEventArgs ::getMouseButton()
	{
		return this->_button;
	}



	void Panel::Dispose()
	{
		if (!_disposed && !_disposing)
		{
			_disposing = true;

			std::cout << "Disposing: " << this->_name << std::endl;
			this->onDispose();

			for (int i = 0; i < this->getChildrenCount(); i++)
			{
				auto child = this->getChild(i);
				if (child != nullptr)
				{
					child->Dispose();
				}
				
			}
			this->_children.clear();

			_disposed = true;
		}
	}

	//Panel::~Panel()
	//{
	//	std::cout << "Disposing: " << this->_name  << " destructor has been run." << std::endl;
	//	if (!_disposed && !_disposing)
	//	{
	//		Dispose();
	//	}
	//	return;
	//}


#pragma region Children
	uint32_t Panel::getChildrenCount()
	{
		return this->_children.size();
	}

	void Panel::addChild(const std::string& name, Panel* child)
	{
		child->_parent = this;
		child->_name = name;

		this->_children.push_back(child);
	}

	Panel* Panel::getChild(const uint32_t& index)
	{
		if (this->getChildrenCount() > 0 && this->getChildrenCount() > index)
			return this->_children[index];
		else
			return nullptr;
	}
#pragma endregion

	void Panel::setBackColor(const dc::Color& backColor)
	{
		this->_backColor = backColor;
		this->invalidate();
	}

	dc::Color Panel::getBackColor()
	{
		return this->_backColor;
	}


	dc::Point Panel::getControlWindowPosition()
	{
		if (this->_parent == nullptr)
		{
			//we are a base panel.
			return this->_controlPosition;
		}
		else
		{
			return (this->_controlPosition + _parent->getControlPosition());
		}
	}

	void Panel::setControlPosition(const dc::Point& position)
	{
		this->_controlPosition = position;
		this->onPositionChanged(GUIEventArgs());
	}
	dc::Point Panel::getControlPosition()
	{
		return this->_controlPosition;
	}


	void Panel::setControlSize(const dc::Size& size)
	{
		this->_controlSize = size;
		this->onPositionChanged(GUIEventArgs());
	}

	dc::Size Panel::getControlSize()
	{
		return this-> _controlSize;
	}

	void Panel::update()
	{
		if (!this->_focused)
		{
			if (dc::Game::instance().gameWindow().getFocusedPanel() == this)
			{
				//invoke the onFocusGained event
				_focused = true;
				this->_defaultEventDispatcher.invokeEvent(this->onFocusGained, EventArgs());
			}
		}
		else //we do have focus (supposedly)
		{
			if (dc::Game::instance().gameWindow().getFocusedPanel() != this)
			{
				//invoke the onFocusLost event
				_focused = false;
				this->_defaultEventDispatcher.invokeEvent(this->onFocusLost, EventArgs());
			}
		}

		if (this->_invalid)
		{
			this->_invalid = false;
			//Draw the background
			_backgroundVerts.clear();
			auto pos = this->getControlWindowPosition();

			sf::Color color = sf::Color(_backColor.getR(), _backColor.getG(), _backColor.getB(), _backColor.getA());

			sf::Vertex TL = sf::Vertex(sf::Vector2f(pos.x, pos.y), color);
			sf::Vertex TR = sf::Vertex(sf::Vector2f(pos.x + _controlSize.x, pos.y), color);
			sf::Vertex BR = sf::Vertex(sf::Vector2f(pos.x + _controlSize.x, pos.y + _controlSize.y), color);
			sf::Vertex BL = sf::Vertex(sf::Vector2f(pos.x, pos.y + _controlSize.y), color);

			_backgroundVerts.append(TL);
			_backgroundVerts.append(TR);
			_backgroundVerts.append(BR);

			_backgroundVerts.append(BR);
			_backgroundVerts.append(BL);
			_backgroundVerts.append(TL);

			this->onUpdate(GUIEventArgs());
		}
		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				child->update();
			}
		}
	}


	bool Panel::containsMouse()
	{
		return this->_containsMouse;
	}

	void Panel::setMousePressed(const MouseButtons& button)
	{
		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{

				if (child->containsMouse())
					this->_mouseButtonEventDispatcher.invokeEvent(child->onMouseButtonPressed, dc::MouseButtonEventArgs(button));

			}
		}
	}

	void Panel::setMouseReleased(const MouseButtons& button)
	{
		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				if (child == dc::Game::instance().gameWindow().getFocusedPanel())
					this->_mouseButtonEventDispatcher.invokeEvent(child->onMouseButtonReleased, dc::MouseButtonEventArgs(button));

			}
		}
	}
	void Panel::setKeyPressed(const sf::Keyboard::Key& code, const bool& alt, const bool& control, const bool& shift)
	{
		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				if (child == dc::Game::instance().gameWindow().getFocusedPanel())
					child->onKeyPressed(dc::KeyButtonEventArgs(code, alt, control, shift));

			}
		}
	}
	void Panel::setKeyReleased(const sf::Keyboard::Key& code, const bool& alt, const bool& control, const bool& shift)
	{
		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				if (child == dc::Game::instance().gameWindow().getFocusedPanel())
					child->onKeyReleased(dc::KeyButtonEventArgs(code, alt, control, shift));

			}
		}
	}

	void Panel::setTextEntered(const uint32_t& unicodeChar)
	{
		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				if (child == dc::Game::instance().gameWindow().getFocusedPanel())
					child->onTextEntered(dc::TextEnteredEventArgs(unicodeChar));

			}
		}
	}

	void Panel::setMousePos(const Point& mousepos)
	{
		auto controlPos = this->getControlWindowPosition();

		this->_mousePos = dc::Point(mousepos.x - controlPos.x, mousepos.y - controlPos.y);

		auto controlRight = this->_controlSize.x + controlPos.x;
		auto controlBottom = this->_controlSize.y + controlPos.y;

		if ((controlPos.x <= mousepos.x && controlPos.y <= mousepos.y) && (controlRight >= mousepos.x && controlBottom >= mousepos.y))
		{
			//Control contains mouse
			if (!this->_containsMouse)
			{
				//Mouse Enter event has not been triggered.

				this->_containsMouse = true;
				this->_defaultEventDispatcher.invokeEvent(this->onMouseEnter, EventArgs());
			}
		}
		else
		{
			//Control does not contain mouse
			if (this->_containsMouse)
			{
				//Mouse Left event has not been triggered.
				this->_containsMouse = false;
				this->_defaultEventDispatcher.invokeEvent(this->onMouseLeave, EventArgs());
			}
		}
		this->onMouseMove(MouseMoveEventArgs(mousepos));



		//update the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				child->setMousePos(mousepos);
			}
		}
	}

	Point Panel::getMousePosition()
	{
		return this->_mousePos;
	}
	Point Panel::getMouseWindowPosition()
	{
		auto controlPos = this->getControlWindowPosition();

		return dc::Point(_mousePos.x + controlPos.x, _mousePos.y + controlPos.y);
	}

	void Panel::requestFocus()
	{
		dc::Game::instance().gameWindow().setFocusedPanel(this);
	}

	bool Panel::isFocused()
	{
		return (this == dc::Game::instance().gameWindow().getFocusedPanel());
	}

	void Panel::invalidate()
	{
		this->_invalid = true;
	}

	void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		target.draw(_backgroundVerts);

		//draw the children
		for (int i = 0; i < _children.size(); i++)
		{
			auto child = _children[i];
			if (child != nullptr)
			{
				child->draw(target, states);
			}
		}

		this->onPaint(target, states);
	}
}
