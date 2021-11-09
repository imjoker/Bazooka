
void
Explosion::Init (const sf::Texture & pTexture, const sf::Vector2f & pPosition, int pFramecount, float pAnimDuration) noexcept
{
	vPosition         = pPosition;
	vDurationPerFrame = pAnimDuration / (float) pFramecount;

	// adjusting position, as the starting image is at frame-1 in the sprite sheet

	vPosition.x += (2.5 * vSpriteSize.x);
	vPosition.y += (0.5 * vSpriteSize.y);

	vClock.restart ();

	// Create Sprite and attach a Texture

	vSprite.setTexture (pTexture);
	vSprite.setPosition (vPosition);
	vSprite.setOrigin (pTexture.getSize ().x / 2, pTexture.getSize ().y / 2);
}

inline void
Explosion::Update () noexcept
{
		int animFrame;

	// Animate Sprite

    animFrame = static_cast<int> (vClock.getElapsedTime ().asSeconds () / vDurationPerFrame);

	vSprite.setTextureRect (sf::IntRect (animFrame * vSpriteSize.x, 0, vSpriteSize.x, vSpriteSize.y));
}

inline bool
Explosion::IsLifeTimeOver (float pDt) noexcept // TODO: param
{	
	return (vClock.getElapsedTime ().asSeconds () >= 0.2f);   // explosion appears nearly for 0.2 second.
}

inline const sf::Sprite &
Explosion::GetSprite () const noexcept
{
	return vSprite;
}