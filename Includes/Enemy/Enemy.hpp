#pragma once

#include "SFML\Graphics.hpp"

#include "Hero.hpp"

class Enemy
{

   public:

	   void            Init           (const sf::Texture & pTexture, const sf::Vector2f & pPosition, float pSpeed) noexcept;
	   void            Update         (float pDt) noexcept;
 const sf::Sprite &    GetSprite      () const noexcept;

   private: // data members

	   float           vSpeed;
	   sf::Sprite      vSprite;
	   sf::Vector2f    vPosition;
};

#include "Enemy.hxx"
