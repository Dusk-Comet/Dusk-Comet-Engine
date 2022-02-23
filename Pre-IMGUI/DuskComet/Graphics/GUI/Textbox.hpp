#ifndef DUSKCOMET_GRAPHICS_GUI_TEXTBOX__HPP
#define DUSKCOMET_GRAPHICS_GUI_TEXTBOX__HPP

#include "Panel.hpp"
#include "../../System/Event.hpp"

namespace dc
{
	class Textbox;





	class Textbox : public Panel
	{
	private:

		dc::Color _borderLightLight = dc::Color(0xc4, 0xc4, 0xc4, 0xFF);
		dc::Color _borderLight = dc::Color(0xb0, 0xb0, 0xb0, 0xFF);

		dc::Color _borderDarkDark = dc::Color(0x2b, 0x2b, 0x2b, 0xFF);
		dc::Color _borderDark = dc::Color(0x38, 0x38, 0x38, 0xFF);


		void textbox_OnFocusGained(EventArgs e);
		void textbox_OnFocusLost(EventArgs e);

		void textbox_OnMouseEnter(EventArgs e);
		void textbox_OnMouseLeave(EventArgs e);

		void textbox_OnMouseButtonPressed(MouseButtonEventArgs e);
		void textbox_OnMouseButtonReleased(MouseButtonEventArgs e);

		sf::RenderTexture _textureBuffer = sf::RenderTexture();
		sf::Sprite _spritePuppet = sf::Sprite();

		sf::Text _displayText = sf::Text();
		sf::VertexArray _lineVerts = sf::VertexArray(sf::PrimitiveType::Lines);


		int32_t _charPos = 0;
		int32_t _controlCharOffset = 0;

		void incrementCaret();
		void decrementCaret();


		int getGlyphSize(char& letter, sf::Font& font, int font_size);
	public:
		Textbox();

		void onDispose() override;



		void onMouseMove(MouseMoveEventArgs e) override;


		void onTextEntered(TextEnteredEventArgs e) override;

		void onKeyPressed(KeyButtonEventArgs e) override;
		void onKeyReleased(KeyButtonEventArgs e) override;

		void onPositionChanged(GUIEventArgs e)  override;
		void onSizeChanged(GUIEventArgs e) override;

		void onUpdate(GUIEventArgs e) override;

		void onPaint(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}


#endif // !DUSKCOMET_GRAPHICS_GUI_TEXTBOX__HPP
