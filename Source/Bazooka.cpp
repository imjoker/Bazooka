#include "LibWrap.hpp"

int main() {

	    sf::Clock        clock;
	    SceneController  ctrl;

	ctrl.Init ();

	while (ctrl.IsWindowOpen ()) {

		ctrl.UpdateUserAction ();

		if (ctrl.GetCurrentScene () == eSceneState::GAME_SCENE) {

		        sf::Time dt = clock.restart ();

		    ctrl.UpdateGameScene (dt);
		}

		ctrl.GetWindow ().clear ();
		ctrl.Draw ();
		ctrl.GetWindow ().display ();
	}

	return 0;
}

/*
TODO:
3. Escape to return text. Enter to start text
*/