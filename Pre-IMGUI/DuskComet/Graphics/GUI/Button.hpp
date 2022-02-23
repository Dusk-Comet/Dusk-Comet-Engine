#ifndef DUSKCOMET_GRAPHICS_GUI_BUTTON__HPP
#define DUSKCOMET_GRAPHICS_GUI_BUTTON__HPP

#include "Panel.hpp"
#include "../../System/Event.hpp"

namespace dc
{
	class Button;

	template<typename t>
	class ButtonEventDispatcher : EventDispatcher<t>
	{

		friend class Button;
	};

	class Button : public Panel
	{
	private:
		void button_OnFocusGained(EventArgs e);
		void button_OnFocusLost(EventArgs e);

		void button_OnMouseEnter(EventArgs e);
		void button_OnMouseLeave(EventArgs e);

		void button_OnMouseButtonPressed(MouseButtonEventArgs e);
		void button_OnMouseButtonReleased(MouseButtonEventArgs e);


		dc::Color _borderLightLight = dc::Color(0xc4, 0xc4, 0xc4, 0xFF);
		dc::Color _borderLight = dc::Color(0xb0, 0xb0, 0xb0, 0xFF);

		dc::Color _borderDarkDark = dc::Color(0x2b, 0x2b, 0x2b, 0xFF);
		dc::Color _borderDark = dc::Color(0x38, 0x38, 0x38, 0xFF);


		dc::Color _defaultBackColor = dc::Color(0x67, 0x67, 0x67, 0xFF);

		sf::Text _displayText = sf::Text();

		sf::VertexArray _triVerts = sf::VertexArray(sf::PrimitiveType::Triangles);

		bool _pressed = false;

		void drawBackground();
	public:

		Event<EventArgs> eventOnClick;

		Button();

		void onDispose() override;

		void onMouseMove(MouseMoveEventArgs e) override;




		void onPositionChanged(GUIEventArgs e)  override;
		void onSizeChanged(GUIEventArgs e) override;

		void onUpdate(GUIEventArgs e) override;

		void onPaint(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
#endif //!DUSKCOMET_GRAPHICS_GUI_BUTTON__HPP