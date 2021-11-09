#pragma once

#include "MenuScene.hpp"

class ControlsScene {

    public:

	    void           Init           (const sf::Vector2f & pViewSize) noexcept;
	    void           Draw           (sf::RenderWindow & pWindow) noexcept;

    private:

	    sf::Font       vFont;
	    sf::Text       vControlsText;
        sf::Texture    vBgTexture;
        sf::Sprite     vBgSprite;
};

#include "ControlsScene.hxx"