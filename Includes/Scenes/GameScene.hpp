#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include <vector>

#include "ControlsScene.hpp"

#define MAX_ENEMIES 20

enum class eGameState : int {

    YET_TO_START,
    RUNNING,
    GAME_OVER,
};

class GameScene {

    public:

        void                  Init                  (const sf::Vector2f & pViewSize) noexcept;
        void                  Reset                 (int pLevel = 0) noexcept;

        void                  Draw                  (sf::RenderWindow & pWindow) noexcept;

        void                  Update                (float pDt, const sf::Vector2f & pViewSize) noexcept;
        void                  UpdateEvent           (const sf::Event & pEvent) noexcept;

        eGameState            GetCurrState          () const noexcept;
        bool                  IsGameOver            () const noexcept;

        void                  StartMusic            () noexcept;
        void                  StopAllMusic          () noexcept;

    private:    // internal private functions

        void                  SpawnEnemy            (const sf::Vector2f & pViewSize) noexcept;

        void                  Shoot                 () noexcept;

        bool                  CheckCollision        (const sf::Sprite & pSprite1, const sf::Sprite & pSprite2) noexcept;

    private:    // data members

        bool                      vIsGameWon;
        eGameState                vGameState;
        int                       vScore;
        int                       vCurrLevel;
        int                       vRemainingRockets;
        int                       vRemainingEnemies;
        float                     vPrevTime;
        float                     vCurrentTime;

        Hero                      vHero;

        // textures/sprites

        sf::Texture               vBgTexture;
        sf::Sprite                vBgSprite;
   
        sf::Texture               vLevelTexture;
        sf::Sprite                vLevelSprite;

        sf::Texture               vEnemyTexture;
        sf::Texture               vRocketTexture;
        sf::Texture               vExplosionTexture;

        std::vector<Enemy *>      vEnemies;
        std::vector<Rocket *>     vRockets;
        std::vector<Explosion *>  vExplosions;

        // Text

        sf::Font                  vFont;
        sf::Text                  vStatsText;
        sf::Text                  vLevelText;

        // Audio

        sf::SoundBuffer           vFireBuffer;
        sf::SoundBuffer           vHitBuffer;
        sf::Sound                 vFireSound    {vFireBuffer};
        sf::Sound                 vHitSound     {vHitBuffer};

        sf::Music                 vLvlStartMusic;
        sf::Music                 vGameRunningMusic;
        sf::Music                 vGameLostMusic;
        sf::Music                 vGameWonMusic;

    // constants

static constexpr float sJumpDistance            {750.0f};
static constexpr float sRocketSpeed             {500.0f};

static constexpr float sEnemySpawnInterval[3]   {1.125f, 1.025f, 1.0f};
static constexpr float sSpeedMultiplier[3]      {1.0f, 1.1f, 1.2f};
static constexpr int   sNumRockets[3]           {30, 25, 20};

    // texts

static constexpr const char * sLevel1GoalStr {"LEVEL-1.\n"
                                              "Emergency alert! Neighbouring country started invasion on our country. \n"
                                              "Our army tried their best to prevent them from crossing our borders,\n"
                                              "but still some more enemies are still alive. You are our last line of defense and our ultimate hope.\n"
                                              "\nTarget: 20 enemies incoming. You have 30 missiles in your bazooka. Make 'em count."
                                              "\n\n\t\t\t\t\t\t\tPress Enter to start round, Escape to return to Menu"};

static constexpr const char * sLevel2GoalStr {"LEVEL-2.\n"
                                              "Excellent job in eliminating all enemies. But it's too early to celebrate.\n"
                                              "Another enemy wave is on it's way! We have to be prepared and ready\n"
                                              "\nTarget: 20 enemies incoming at high speed. You have 25 missiles in your bazooka.\n"
                                              "Hit 'em hard!"
                                              "\n\n\t\t\t\t\t\t\tPress Enter to start round, Escape to return to Menu"};

static constexpr const char * sLevel3GoalStr {"LEVEL-3.\n"
                                              "We knew we could depend on you. We are right to trust you to save us.\n"
                                              "But it's not yet over. We just got the information that final wave of enemies are nearby!\n"
                                              "Oh no! They are already here, and they seem to be coming at good pace, really faster than previous two waves.\n"
                                              "Another sad news, we only got 20 missiles left. It is all upto you now.\n"
                                              "\nTarget: 20 enemies headed right at us, and you only have one missile for each of them."
                                              "\n\n\t\t\t\t\t\t\tPress Enter to start round, Escape to return to Menu"};


static constexpr const char * sGameWonStr    {"\t\t\t\t\t\t\tYou did it! We knew you would.\n"
                                              "\t\t\t\t\t\t\tYou saved our village, our people, our lives. You are our Hero!\n"
                                              "\t\t\t\t\t\t\t Hail the hero! Hail the champion!\n"
                                              "\n\t\t\t\t\t\t\tClick Escape to return to Menu"};

static constexpr const char * sGameLostStr   {"\t\t\t\t\t\t\tWe lost this one battle, but we haven't lost the the war yet.\n"
                                              "\t\t\t\t\t\t\tLet us not lose hope. We will come back stronger.\n"
                                              "\n\t\t\t\t\t\t\tClick Escape to return to Menu"};

static constexpr const char * sLevelTexts[3]  {sLevel1GoalStr, sLevel2GoalStr, sLevel3GoalStr};

};


#include "GameScene.hxx"