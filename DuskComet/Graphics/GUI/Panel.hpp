#ifndef DUSKCOMET_GRAPHICS_GUI_PANEL__HPP
#define DUSKCOMET_GRAPHICS_GUI_PANEL__HPP

#include "../../System/Types/Vectors.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>

#include "../../System/Event.hpp"

namespace dc
{
	enum class MouseButtons
	{
		LEFT,
		RIGHT,
		MIDDLE,
		EXTRA1,
		EXTRA2
	};


	class GUIEventArgs
	{

	};

	class Panel;

	template<typename t>
	class PanelEventDispatcher : EventDispatcher<t>
	{

		friend class Panel;
	};

	class MouseMoveEventArgs : GUIEventArgs
	{
	private:
		Point _mouseLocation = Point(0, 0);
	public:
		MouseMoveEventArgs(Point mouselocation)
		{
			this->_mouseLocation = mouselocation;
		}

		Point getMouseLocation();
	};

	class MouseButtonEventArgs : EventArgs
	{
	private:
		MouseButtons _button;
	public:
		MouseButtonEventArgs(const MouseButtons& button)
		{
			this->_button = button;
		}

		MouseButtons getMouseButton();
	};


	class KeyButtonEventArgs : EventArgs
	{
	private:
		sf::Keyboard::Key _code;

		bool _alt;
		bool _control;
		bool _shift;
		bool _system;
	public:
		KeyButtonEventArgs(const sf::Keyboard::Key& code, const bool& alt, const bool& control, const bool& shift)
		{
			_code = code;
			_alt = alt;
			_control = control;
			_shift = shift;
		}

		sf::Keyboard::Key getKeyCode() { return _code; }

		bool isAltPressed() { return _alt; }
		bool isControlPressed() { return _control; }
		bool isShiftPressed() { return _shift; }
	};

	class TextEnteredEventArgs : EventArgs
	{
	private:
		uint32_t _char;


	public:
		TextEnteredEventArgs(const uint32_t& unicodeChar)
		{
			this->_char = unicodeChar;
		}

		uint32_t getChar() { return _char; }
	};


	class Panel : public sf::Drawable
	{
	private:
		bool _disposing = false;
		bool _disposed = false;


		sf::VertexArray _backgroundVerts = sf::VertexArray(sf::PrimitiveType::Triangles);

		Panel* _parent = nullptr;

		std::vector<Panel*> _children;

		bool _invalid = true;

		Point _controlPosition = Point(0, 0);
		Size _controlSize = Size(0, 0);


		bool _containsMouse = false;

		bool _focused = false;

		Point _mousePos = Point(0, 0);

		

		std::string _name = std::string("");
		dc::Color _backColor = dc::Color(0x00, 0x00, 0x00, 0x00);

		PanelEventDispatcher<EventArgs> _defaultEventDispatcher;

		PanelEventDispatcher<MouseButtonEventArgs> _mouseButtonEventDispatcher;

	protected:


		virtual void onKeyPressed()
		{

		}



		/// <summary>
		/// Called whenever the control is to be disposed
		/// </summary>
		virtual void onDispose() { }



		/// <summary>
		/// Event called whenever the mouse moves and the control has focus
		/// </summary>
		/// <param name="mousepos"></param>
		virtual void onMouseMove(MouseMoveEventArgs e) { }

		
		virtual void onTextEntered(TextEnteredEventArgs e) { }



		/// <summary>
		/// Event called whenever a key is pressed on the keyboard
		/// </summary>
		/// <param name="e"></param>
		virtual void onKeyPressed(KeyButtonEventArgs e) { }
		/// <summary>
		/// Event called whenever a key is released on the keyboard
		/// </summary>
		/// <param name="e"></param>
		virtual void onKeyReleased(KeyButtonEventArgs e) { }

		virtual void onPositionChanged(GUIEventArgs e) { }
		virtual void onSizeChanged(GUIEventArgs e) { }


		/// <summary>
		/// Event called whenever the control is invalid and needs to be updated
		/// </summary>
		virtual void onUpdate(GUIEventArgs e) { }

		/// <summary>
		/// Event called whenever the control is to be painted
		/// </summary>
		virtual void onPaint(sf::RenderTarget& target, sf::RenderStates states) const { };

	public:

#pragma region Public Events
		Event<EventArgs> onFocusGained;
		Event<EventArgs> onFocusLost;

		Event<MouseButtonEventArgs> onMouseButtonPressed;
		Event<MouseButtonEventArgs> onMouseButtonReleased;

		/// <summary>
		/// Event called whenever the mouse enters the control bounds
		/// </summary>
		Event<EventArgs> onMouseEnter;
		/// <summary>
		/// Event called whenever the mouse enters the control bounds
		/// </summary>
		Event<EventArgs> onMouseLeave;
#pragma endregion

#pragma region Children
		/// <summary>
		/// Returns the amount of children controls
		/// </summary>
		/// <returns></returns>
		uint32_t getChildrenCount();



		/// <summary>
		/// Add a new child control with a given name
		/// </summary>
		void addChild(const std::string& name, Panel* child);

		/// <summary>
		/// Get a child by index
		/// </summary>
		Panel* getChild(const uint32_t& index);

#pragma endregion
		~Panel();
		void Dispose();


		/// <summary>
		/// Set the backcolor of the Panel
		/// </summary>
		void setBackColor(const dc::Color& backColor);
		/// <summary>
		/// Gets the backcolor of the Panel
		/// </summary>
		/// <returns></returns>
		dc::Color getBackColor();



		/// <summary>
		/// Gets the position of control relative to the window
		/// </summary>
		/// <returns></returns>
		dc::Point getControlWindowPosition();


		/// <summary>
		/// Sets the control position (relative to it's parent)
		/// </summary>
		/// <param name="size"></param>
		void setControlPosition(const dc::Point& position);
		/// <summary>
		/// Gets the control position (relative to it's parent)
		/// </summary>
		dc::Point getControlPosition();


		/// <summary>
		/// Sets the control size
		/// </summary>
		/// <param name="size"></param>
		void setControlSize(const dc::Size& size);
		/// <summary>
		/// Gets the control size
		/// </summary>
		dc::Size getControlSize();

		/// <summary>
		/// Does the control contain the mouse position?
		/// </summary>
		/// <returns></returns>
		bool containsMouse();

		void setMousePressed(const MouseButtons& button);
		void setMouseReleased(const MouseButtons& button);

		void setKeyPressed(const sf::Keyboard::Key& code, const bool& alt, const bool& control, const bool& shift);
		void setKeyReleased(const sf::Keyboard::Key& code, const bool& alt, const bool& control, const bool& shift);

		void setTextEntered(const uint32_t& unicodeChar);




		/// <summary>
		/// Update the internal mouse position, will invoke MouseMove and possibly the Enter/Leave events
		/// </summary>
		void setMousePos(const Point& mousepos);

		/// <summary>
		/// Gets the current mouse pos (relative to the control)
		/// </summary>
		Point getMousePosition();

		/// <summary>
		/// Gets the current mouse pos (relative to the control)
		/// </summary>
		Point getMouseWindowPosition();

		void requestFocus();
		bool isFocused();

		/// <summary>
		/// Make the control as invalid, and call the "OnUpdate" event on the next game loop iteration
		/// </summary>
		void invalidate();


		/// <summary>
		/// Invoke the "onUpdate" event if the control is invalid
		/// </summary>
		void update();


		// Inherited via Drawable
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		friend class GameWindow;
	};
}

#endif // !DUSKCOMET_GRAPHICS_GUI_PANEL__HPP
