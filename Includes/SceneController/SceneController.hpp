#pragma once

#include "SFML\Graphics.hpp"
#include "GameScene.hpp"

enum class eSceneState : int {

    MENU_SCENE,
    GAME_SCENE,
    CONTROLS_SCENE,
};

class SceneController {

    public:

        void                  Init                 () noexcept;
        void                  Draw                 () noexcept;
        void                  UpdateUserAction     () noexcept;

        void                  UpdateGameScene      (const sf::Time & pDt) noexcept;

        sf::RenderWindow &    GetWindow            () noexcept;

        eSceneState           GetCurrentScene      () const noexcept;
        bool                  IsWindowOpen         () const noexcept;

    private:

        using UpdateActionFunc = void (*) (SceneController & pWC);

static  void                  UpdateActionInMenuScene      (SceneController & pWC) noexcept;
static  void                  UpdateActionInGameScene      (SceneController & pWC) noexcept;
static  void                  UpdateActionInControlsScene  (SceneController & pWC) noexcept;


        // Window

        eSceneState           vCurrState           {eSceneState::MENU_SCENE};     
const   sf::Vector2f          vViewSize            {sHorizontalResolution, sVerticalResolution};
const   sf::VideoMode         vVM                  {sHorizontalResolution, sVerticalResolution};
        sf::RenderWindow      vWindow              {vVM, "Bazooka", sf::Style::Default};
	    sf::Event             vEvent;

        // Scenes

        MenuScene             vMenu;
        GameScene             vGame;
        ControlsScene         vControls;

        // Audio

        sf::Music             vBgMusic;

static constexpr int sHorizontalResolution         {1024};
static constexpr int sVerticalResolution           {768};

static constexpr UpdateActionFunc sUpdateAction[3]     {UpdateActionInMenuScene, UpdateActionInGameScene, UpdateActionInControlsScene};
};


#include "SceneController.hxx"