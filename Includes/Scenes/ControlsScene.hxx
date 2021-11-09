#include "ControlsScene.hpp"

void 
ControlsScene::Init (const sf::Vector2f & pViewSize) noexcept
{
	vFont.loadFromFile ("Assets/fonts/MAIAN.TTF");

	vControlsText.setFont (vFont);
	vControlsText.setString ("CONTROLS:\n"
	                         "  To Jump:  Press 'Up-arrow' button\n"
	                         "  To Shoot: Press 'Space' button\n"
	                         "\nPress Escape to return back to Menu");

	vControlsText.setCharacterSize (40);
	vControlsText.setFillColor (sf::Color::Red);
	vControlsText.setPosition (pViewSize.x * 0.2f, pViewSize.y * 0.3f);
	vControlsText.setStyle (sf::Text::Bold);

	vBgTexture.loadFromFile ("Assets/graphics/controls.jpg");
	vBgSprite.setTexture (vBgTexture);
}

inline void 
ControlsScene::Draw (sf::RenderWindow & pWindow) noexcept
{
	pWindow.draw (vBgSprite);
	pWindow.draw (vControlsText);
}
