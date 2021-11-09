#pragma once

#include "SFML\Graphics.hpp"

#include "Explosion.hpp"

static const sf::Color sActiveOptionColor   {sf::Color::Red};
static const sf::Color sInactiveOptionColor {sf::Color::Black};

enum class eMenuOptions : int {

	PLAY,
	CONTROLS,
	EXIT,
	MAX_NUM_OPTIONS,
};

class MenuScene {

    public:

		void            Init                (const sf::Vector2f & pViewSize) noexcept;
		void            Reset               () noexcept;
		void            Draw                (sf::RenderWindow & pWindow) noexcept;

		void            MoveUp              () noexcept;
		void            MoveDown            () noexcept;

		eMenuOptions    GetCurrentOption    () noexcept;

	private:

		int            vCurrentOption;
		sf::Font       vFont;
		sf::Text       vTitle;
		sf::Text       vOptions[(int) eMenuOptions::MAX_NUM_OPTIONS];

        sf::Texture    vBgTexture;
        sf::Sprite     vBgSprite;

static constexpr float sTitleHorizFactor  {0.4f};
static constexpr float sOptionHorizFactor {0.45f};

};

#include "MenuScene.hxx"