
void 
Enemy::Init (const sf::Texture & pTexture, const sf::Vector2f & pPosition, float pSpeed) noexcept
{
	vSpeed    = pSpeed;
	vPosition = pPosition;

	// Create Sprite and attach a Texture

	vSprite.setTexture (pTexture);
	vSprite.setPosition (vPosition);
	vSprite.setOrigin (pTexture.getSize ().x / 2, pTexture.getSize ().y / 2);

}

inline void 
Enemy::Update (float pDt) noexcept
{
	vSprite.move (vSpeed * pDt, 0);
}


inline const sf::Sprite &
Enemy::GetSprite () const noexcept
{
	return vSprite;
}
