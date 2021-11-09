
void 
Rocket::Init (const sf::Texture & pTexture, const sf::Vector2f & pPosition, float pSpeed) noexcept
{
	vSpeed    = pSpeed;
	vPosition = pPosition;

	// Create Sprite and attach the Texture

	vSprite.setTexture (pTexture);
	vSprite.setPosition (vPosition);
	vSprite.setOrigin (pTexture.getSize ().x / 2, pTexture.getSize ().y / 2);
}

inline void 
Rocket::Update (float pDt) noexcept
{
	vSprite.move (vSpeed * pDt, 0);
}

inline const sf::Sprite &
Rocket::GetSprite () const noexcept
{
	return vSprite;
}