#pragma once

#include "SFML\Graphics.hpp"

class Hero {

public:

	   void              Init            (const std::string & pTextureName, int pFrameCount, float pAnimDuration, const sf::Vector2f & pPosition, float pMass) noexcept;
	   void              Update          (float pDt) noexcept;
	   void              Jump            (float pVelocity) noexcept;
 const sf::Sprite &      GetSprite       () const noexcept;

private:    // data members

	   bool              vIsGrounded;
	   int               vJumpCount      {0};
	   int               vFrameCount;
	   float             vMass;
	   float             vVelocity;
	   float             vAnimDuration;
	   float             vElapsedTime;
 const float             vGravity        {9.80f};
	   sf::Texture       vTexture;
	   sf::Sprite        vSprite;
 const sf::Vector2i      vSpriteSize     {92, 126};
	   sf::Vector2f      vPosition;
};

#include "Hero.hxx"
