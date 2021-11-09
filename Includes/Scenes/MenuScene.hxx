#include "MenuScene.hpp"

void
MenuScene::Init (const sf::Vector2f & pViewSize) noexcept
{
	vFont.loadFromFile ("Assets/fonts/SnackerComic.ttf");

	vTitle.setFont (vFont);
	vTitle.setString ("Bazooka");
	vTitle.setCharacterSize (60);
	vTitle.setFillColor (sf::Color::Magenta);
	vTitle.setPosition (pViewSize.x * sTitleHorizFactor, pViewSize.y * 0.05f);
	vTitle.setStyle (sf::Text::Bold);

	vOptions[0].setFont (vFont);
	vOptions[0].setString ("Play");
	vOptions[0].setCharacterSize (45);
	vOptions[0].setFillColor (sActiveOptionColor);
	vOptions[0].setPosition (pViewSize.x * sOptionHorizFactor, pViewSize.y * 0.30f);
	vOptions[0].setStyle (sf::Text::Bold);

	vOptions[1].setFont (vFont);
	vOptions[1].setString ("Controls");
	vOptions[1].setCharacterSize (45);
	vOptions[1].setFillColor (sInactiveOptionColor);
	vOptions[1].setPosition (pViewSize.x * sOptionHorizFactor, pViewSize.y * 0.40f);
	vOptions[1].setStyle (sf::Text::Bold);

	vOptions[2].setFont (vFont);
	vOptions[2].setString ("Exit");
	vOptions[2].setCharacterSize (45);
	vOptions[2].setFillColor (sInactiveOptionColor);
	vOptions[2].setPosition (pViewSize.x * sOptionHorizFactor, pViewSize.y * 0.50f);
	vOptions[2].setStyle (sf::Text::Bold);

	vBgTexture.loadFromFile ("Assets/graphics/menu.jpg");
	vBgSprite.setTexture (vBgTexture);

	vCurrentOption = 0;
}

inline void
MenuScene::Reset () noexcept
{
	vCurrentOption = 0;

	vOptions[0].setFillColor (sActiveOptionColor);
	vOptions[1].setFillColor (sInactiveOptionColor);
	vOptions[2].setFillColor (sInactiveOptionColor);
}

inline void
MenuScene::Draw (sf::RenderWindow & pWindow) noexcept
{
	pWindow.draw (vBgSprite);

	pWindow.draw (vTitle);

	for (int i = 0; i < (int) eMenuOptions::MAX_NUM_OPTIONS; ++i)
		pWindow.draw (vOptions[i]);
}

inline void
MenuScene::MoveUp () noexcept 
{
	vOptions[vCurrentOption].setFillColor (sInactiveOptionColor);

	if (vCurrentOption == 0)
		vCurrentOption = ((int) eMenuOptions::MAX_NUM_OPTIONS) - 1;
	else
		--vCurrentOption;

	vOptions[vCurrentOption].setFillColor (sActiveOptionColor);
}
		
inline void
MenuScene::MoveDown () noexcept
{
	vOptions[vCurrentOption].setFillColor (sInactiveOptionColor);

	++vCurrentOption;
	vCurrentOption %= ((int) eMenuOptions::MAX_NUM_OPTIONS); 

	vOptions[vCurrentOption].setFillColor (sActiveOptionColor);
}

inline eMenuOptions
MenuScene::GetCurrentOption () noexcept
{
	return (eMenuOptions) vCurrentOption;
}
