#include "SceneController.hpp"

void
SceneController::Init() noexcept
{
	vMenu.Init (vViewSize);
	vGame.Init (vViewSize);
	vControls.Init (vViewSize);
	
	vBgMusic.openFromFile ("Assets/audio/menu.ogg");
	vBgMusic.setLoop (true);
	vBgMusic.play ();
}

inline void
SceneController::Draw () noexcept
{
	switch (vCurrState)
	{
	    case eSceneState::MENU_SCENE:
			vMenu.Draw (vWindow);
		    break;

	    case eSceneState::GAME_SCENE:
			vGame.Draw (vWindow);
		    break;

	    case eSceneState::CONTROLS_SCENE:
			vControls.Draw (vWindow);
		    break;

		default:
			printf ("Critical error! Only three scenes in our game! This shouldn't happen.");
			break;
	}		
}

inline void
SceneController::UpdateUserAction () noexcept
{
	sUpdateAction[(int) vCurrState] (*this);
}

inline void
SceneController::UpdateGameScene (const sf::Time & pDt) noexcept
{
	if (vGame.GetCurrState () == eGameState::RUNNING)
   		vGame.Update (pDt.asSeconds (), vViewSize);
}

void 
SceneController::UpdateActionInMenuScene (SceneController & pWC) noexcept
{
	// while there are pending events...
	while (pWC.vWindow.pollEvent (pWC.vEvent)) {

		if (pWC.vEvent.type == sf::Event::KeyPressed) {

			switch (pWC.vEvent.key.code)
			{
				case sf::Keyboard::Up:
					return pWC.vMenu.MoveUp ();

				case sf::Keyboard::Down:
					return pWC.vMenu.MoveDown ();

				case sf::Keyboard::Enter:					

					switch (pWC.vMenu.GetCurrentOption ())
				    {
				        case eMenuOptions::PLAY:
							pWC.vBgMusic.stop ();
				            pWC.vCurrState = eSceneState::GAME_SCENE;
							pWC.vGame.StartMusic ();
				    		return;

				    	case eMenuOptions::CONTROLS:
							pWC.vCurrState = eSceneState::CONTROLS_SCENE;
				    		return;
    
				    	case eMenuOptions::EXIT:
				    		return pWC.vWindow.close ();
				    }

				case sf::Keyboard::Escape:
					return pWC.vWindow.close ();
			}

		} else if (pWC.vEvent.type == sf::Event::Closed)
			pWC.vWindow.close ();
	}
}

void
SceneController::UpdateActionInGameScene (SceneController & pWC) noexcept
{
	// while there are pending events...
	while (pWC.vWindow.pollEvent (pWC.vEvent)) {

		if (pWC.vEvent.type == sf::Event::KeyPressed) {

			if (pWC.vEvent.key.code == sf::Keyboard::Escape) {   // return to menu

			    pWC.vGame.Reset ();    
				pWC.vGame.StopAllMusic ();

		        pWC.vCurrState = eSceneState::MENU_SCENE;
				pWC.vBgMusic.play ();

		    } else
				pWC.vGame.UpdateEvent (pWC.vEvent);

		} else if (pWC.vEvent.type == sf::Event::Closed) {

			pWC.vGame.Reset ();    // clear all objects before closing

			pWC.vWindow.close ();
		}
	}
}

void SceneController::UpdateActionInControlsScene (SceneController & pWC) noexcept
{
	// while there are pending events...
	while (pWC.vWindow.pollEvent (pWC.vEvent)) {

		if (pWC.vEvent.type == sf::Event::KeyPressed && pWC.vEvent.key.code == sf::Keyboard::Escape)
		    pWC.vCurrState = eSceneState::MENU_SCENE;    // return to menu
		else if (pWC.vEvent.type == sf::Event::Closed)
			pWC.vWindow.close ();
	}
}

inline eSceneState 
SceneController::GetCurrentScene() const noexcept
{
	return vCurrState;
}

inline bool
SceneController::IsWindowOpen () const noexcept
{
	return vWindow.isOpen();
}

inline sf::RenderWindow &
SceneController::GetWindow () noexcept
{
	return vWindow;
}
