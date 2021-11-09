
void 
Hero::Init (const std::string & pTextureName, int pFrameCount, float pAnimDuration, const sf::Vector2f & pPosition, float pMass) noexcept
{
	vPosition     = pPosition;
	vMass         = pMass;
	vIsGrounded   = false;
	vFrameCount   = pFrameCount;
	vAnimDuration = pAnimDuration;

	// Load a Texture

	vTexture.loadFromFile (pTextureName.c_str ());

	// Create Sprite and attach a Texture

	vSprite.setTexture (vTexture);
	vSprite.setTextureRect (sf::IntRect (0, 0, vSpriteSize.x, vSpriteSize.y));

	vSprite.setPosition (vPosition);
	vSprite.setOrigin (vSpriteSize.x / 2, vSpriteSize.y / 2);
}

void 
Hero::Update (float pDt) noexcept
{
		int animFrame;

	// Animate Sprite

	vElapsedTime += pDt;

    animFrame = static_cast<int> ((vElapsedTime / vAnimDuration) * vFrameCount) % vFrameCount;

	vSprite.setTextureRect (sf::IntRect (animFrame * vSpriteSize.x, 0, vSpriteSize.x, vSpriteSize.y));

	// Update Position

	vVelocity   -= vMass * vGravity * pDt;
	vPosition.y -= vVelocity * pDt;

	vSprite.setPosition (vPosition);

	if (vPosition.y >= 768 * 0.75) {

		vPosition.y = 768 * 0.75;
		vVelocity   = 0;
		vIsGrounded = true;
		vJumpCount  = 0;
	}
}

inline void Hero::Jump (float pVelocity) noexcept
{
	if (vJumpCount < 2) {

		vJumpCount++;

		vVelocity   = pVelocity;
		vIsGrounded = false;
	}
}

inline const sf::Sprite &
Hero::GetSprite () const noexcept
{
	return vSprite;
}

