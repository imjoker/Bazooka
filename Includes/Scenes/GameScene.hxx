#include "GameScene.hpp"

void
GameScene::Init (const sf::Vector2f & pViewSize) noexcept
{
		sf::FloatRect headingbounds;
		sf::FloatRect levelbounds;
		sf::FloatRect tutorialbounds;
		sf::Image     img;

	// initialize members

	vIsGameWon        = false;
	vGameState        = eGameState::YET_TO_START;
	vScore            = 0;
	vCurrLevel        = 0;
	vRemainingRockets = sNumRockets[vCurrLevel];
	vRemainingEnemies = MAX_ENEMIES;
	vPrevTime         = 0.0f;

	vEnemies.reserve (MAX_ENEMIES);        // reserve the space needed for enemies in advance
	vRockets.reserve (vRemainingRockets);  // reserve the space needed for rockets in advance

	// load all textures

	vBgTexture.loadFromFile ("Assets/graphics/level.png");
	vBgSprite.setTexture (vBgTexture);

	vLevelTexture.loadFromFile ("Assets/graphics/instructions.jpg");
	vLevelSprite.setTexture (vLevelTexture);

	vEnemyTexture.loadFromFile ("Assets/graphics/enemy.png");

	img.loadFromFile ("Assets/graphics/rocket.png");
	img.createMaskFromColor (sf::Color::White);          // mask the background color with transparent
	vRocketTexture.loadFromImage (img);

	img.loadFromFile ("Assets/graphics/exploding.png");
	img.createMaskFromColor (sf::Color::White);          // mask the background color with transparent
	vExplosionTexture.loadFromImage (img);

	// Load font

	vFont.loadFromFile ("Assets/fonts/TEMPSITC.TTF");

	// Set Stats Text

	vStatsText.setFont (vFont);
	vStatsText.setString ("Bullets remaining: " + std::to_string (vRemainingRockets) + "\nEnemies remaining: " +  std::to_string (vRemainingEnemies));
	vStatsText.setCharacterSize (25);
	vStatsText.setFillColor (sf::Color::Red);

	headingbounds = vStatsText.getLocalBounds ();
	vStatsText.setOrigin (headingbounds.width / 2, headingbounds.height / 2);
	vStatsText.setPosition (pViewSize.x * 0.15f, pViewSize.y * 0.05f);

	// set Level text

	vLevelText.setFont (vFont);
	vLevelText.setString (sLevel1GoalStr);
	vLevelText.setCharacterSize (20);
	vLevelText.setFillColor (sf::Color::Red);

	levelbounds = vLevelText.getLocalBounds ();
	vLevelText.setPosition (pViewSize.x * 0.1f, pViewSize.y * 0.04f);
	vLevelText.setStyle (sf::Text::Bold);

	// Audio 

	vHitBuffer.loadFromFile ("Assets/audio/hit.ogg");
	vFireBuffer.loadFromFile ("Assets/audio/fire.ogg");

	vLvlStartMusic.openFromFile ("Assets/audio/levelstart.ogg");
	vLvlStartMusic.setLoop (true);

	vGameRunningMusic.openFromFile ("Assets/audio/menu.ogg");
	vGameRunningMusic.setLoop (true);

	vGameLostMusic.openFromFile ("Assets/audio/lost.ogg");
	vGameLostMusic.setLoop (true);

	vGameWonMusic.openFromFile ("Assets/audio/won.wav");
	vGameWonMusic.setLoop (true);

	vHero.Init ("Assets/graphics/heroAnim.png", 4, 1.0f, sf::Vector2f (pViewSize.x * 0.15f, 0.0f), 200);

	srand ((int) time (0));
}

void 
GameScene::UpdateEvent (const sf::Event & pEvent) noexcept
{
	if (vGameState == eGameState::RUNNING) {

		if (pEvent.key.code == sf::Keyboard::Up)
		    vHero.Jump (sJumpDistance);
		else if (pEvent.key.code == sf::Keyboard::Space)
			Shoot ();

	} else if (vGameState == eGameState::YET_TO_START) {

		if (pEvent.key.code == sf::Keyboard::Enter) {

     		vLvlStartMusic.stop ();
			vGameState = eGameState::RUNNING;
			vGameRunningMusic.play ();
		}
	}
}

void 
GameScene::Update (float pDt, const sf::Vector2f & pViewSize) noexcept
{
		Rocket *    rocket;
		Enemy  *    enemy;
		Explosion * explosion;
		int         i;

	vHero.Update (pDt);

	vCurrentTime += pDt;

	// Update Enemies

	for (i = 0; i < vEnemies.size (); i++) {

		enemy = vEnemies[i];

		enemy->Update (pDt);

		if (enemy->GetSprite ().getPosition ().x < 0) {

			vEnemies.erase (vEnemies.begin () + i);
			delete (enemy);

			vGameState = eGameState::GAME_OVER;
			vGameRunningMusic.stop ();
			vGameLostMusic.play ();
		}
	}

	// Update rockets

	for (i = 0; i < vRockets.size (); i++) {
		
		rocket = vRockets[i];

		rocket->Update (pDt);

		if (rocket->GetSprite ().getPosition ().x > pViewSize.x) {

			vRockets.erase (vRockets.begin () + i);
			delete (rocket);
		}
	}

	// Update explosions

	for (i = 0; i < vExplosions.size (); i++) {
		
		explosion = vExplosions[i];

		explosion->Update ();

		if (explosion->IsLifeTimeOver (pDt)) {

			vExplosions.erase (vExplosions.begin () + i);
			delete (explosion);
		}
	}

	// Check collision between Rocket and Enemies

	for (i = 0; i < vRockets.size (); i++) {

		for (int j = 0; j < vEnemies.size (); j++) {

			rocket = vRockets[i];
			enemy   = vEnemies[j];

			if (CheckCollision (rocket->GetSprite (), enemy->GetSprite ())) {

					Explosion * explosion;

				vHitSound.play ();

				explosion = new Explosion ();
				explosion->Init (vExplosionTexture, enemy->GetSprite ().getPosition (), 6, 0.2f);

				vExplosions.push_back (explosion);

				vScore++;

				vRockets.erase (vRockets.begin () + i);
				vEnemies.erase (vEnemies.begin () + j);

				delete (rocket);
				delete (enemy);

				if (vScore == MAX_ENEMIES) {

					if (vCurrLevel != 2) {

						Reset (vCurrLevel + 1);
						vGameRunningMusic.stop ();
						vLvlStartMusic.play ();

					} else {

						vIsGameWon = true;
			            vGameState = eGameState::GAME_OVER;
						vGameRunningMusic.stop ();
						vGameWonMusic.play ();
					}
				}					
			}
		}
	}

	// Spawn Enemies

	if (vCurrentTime >= (vPrevTime + sEnemySpawnInterval[vCurrLevel])) {

		SpawnEnemy (pViewSize);

		vPrevTime = vCurrentTime;
	}
}

void 
GameScene::Draw (sf::RenderWindow & pWindow) noexcept
{
	switch (vGameState)
	{
	    case eGameState::YET_TO_START:

			pWindow.draw (vLevelSprite);
			pWindow.draw (vLevelText);
		    break;

	    case eGameState::RUNNING:

	        pWindow.draw (vBgSprite);
	        pWindow.draw (vHero.GetSprite ());

	        for (Enemy * enemy : vEnemies)
		        pWindow.draw (enemy->GetSprite());

	        for (Rocket * rocket : vRockets)
		        pWindow.draw (rocket->GetSprite());

	        for (Explosion * explosions : vExplosions)
		        pWindow.draw (explosions->GetSprite());

	        vStatsText.setString ("Bullets remaining: " + std::to_string (vRemainingRockets) + "\nEnemies remaining: " +  std::to_string (MAX_ENEMIES - vScore));

	        pWindow.draw (vStatsText);
		    break;

	    case eGameState::GAME_OVER:

			if (vIsGameWon)
				vLevelText.setString (sGameWonStr);
			else
	            vLevelText.setString (sGameLostStr);       

			pWindow.draw (vLevelSprite);
		    pWindow.draw (vLevelText);
		    break;
	}
}

void 
GameScene::Reset (int pLevel) noexcept
{
	vIsGameWon        = false;
	vGameState        = eGameState::YET_TO_START;
	vScore            = 0;
	vCurrentTime      = 0.0f;
	vPrevTime         = 0.0f;
	vCurrLevel        = pLevel;
	vRemainingRockets = sNumRockets[pLevel];
	vRemainingEnemies = MAX_ENEMIES;

	vLevelText.setString (sLevelTexts[vCurrLevel]);

	for (Enemy * enemy : vEnemies)
		delete(enemy);

	for (Rocket * rocket : vRockets)
		delete(rocket);

	for (Explosion * explosions : vExplosions)
		delete(explosions);

	vEnemies.clear ();
	vRockets.clear ();
	vExplosions.clear ();
}

inline void 
GameScene::Shoot () noexcept
{
	    Rocket * rocket;
		
	if (!vRemainingRockets)      
		return;                       // no bullets left :(

	rocket = new Rocket ();

	rocket->Init (vRocketTexture, vHero.GetSprite ().getPosition (), sRocketSpeed);

	vRockets.push_back (rocket);

	vFireSound.play ();

	--vRemainingRockets;
}

void 
GameScene::SpawnEnemy (const sf::Vector2f & pViewSize) noexcept
{
	    sf::Vector2f enemyPos;
    	float        speed;
	    int          randLoc; 
		Enemy *      enemy;

	if (!vRemainingEnemies)
		return;

	randLoc = rand () % 3;

	switch (randLoc) {

	    case 0: 
			enemyPos = sf::Vector2f (pViewSize.x, pViewSize.y * 0.75f); 
			speed    = -(400 * sSpeedMultiplier[vCurrLevel]); 
			break;

	    case 1: 
		    enemyPos = sf::Vector2f (pViewSize.x, pViewSize.y * 0.60f); 
		    speed    = -(550 * sSpeedMultiplier[vCurrLevel]); 
		    break;

	    case 2: 
	    	enemyPos = sf::Vector2f (pViewSize.x, pViewSize.y * 0.40f);
	    	speed    = -(650 * sSpeedMultiplier[vCurrLevel]);  
	    	break;
	}

	enemy = new Enemy ();

	enemy->Init (vEnemyTexture, enemyPos, speed);
	vEnemies.push_back (enemy);

	--vRemainingEnemies;
}

inline bool 
GameScene::CheckCollision (const sf::Sprite & pSprite1, const sf::Sprite & pSprite2) noexcept
{
	    sf::FloatRect shape1;
	    sf::FloatRect shape2;

	shape1 = pSprite1.getGlobalBounds ();
	shape2 = pSprite2.getGlobalBounds ();

	return shape1.intersects (shape2);
}

inline eGameState
GameScene::GetCurrState () const noexcept
{
	return vGameState;
}

inline bool
GameScene::IsGameOver () const noexcept
{
	return vGameState == eGameState::GAME_OVER;
}

inline void 
GameScene::StartMusic () noexcept
{
	vLvlStartMusic.play ();
}

inline void 
GameScene::StopAllMusic () noexcept
{
	vLvlStartMusic.stop ();
	vGameRunningMusic.stop ();
	vGameLostMusic.stop ();
	vGameWonMusic.stop ();
}

