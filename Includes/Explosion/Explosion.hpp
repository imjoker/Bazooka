#pragma once

#include "SFML\Graphics.hpp"

#include "Rocket.hpp"

class Explosion
{

    public:

	    void           Init            (const sf::Texture & pTexture, const sf::Vector2f & pPosition, int pFramecount, float pAnimDuration) noexcept;

		void           Update          () noexcept;

	    bool           IsLifeTimeOver  (float pDt) noexcept;
  
  const sf::Sprite &   GetSprite       () const noexcept;

    private:    // data members

		float          vDurationPerFrame;
		sf::Clock      vClock;            // to maintain the lifetime for explosion object
	    sf::Sprite     vSprite;
	    sf::Vector2f   vPosition;
 const sf::Vector2i    vSpriteSize  {100, 100};
};

#include "Explosion.hxx"