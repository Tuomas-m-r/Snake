#include "GameManager.h"
#include <SDL.h>

int main(int argc, char *argv[]) {

	GameManager *gameManager = nullptr;
	gameManager = new GameManager();

	const int FPS = 10;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (gameManager->running()) {

		frameStart = SDL_GetTicks();

		gameManager->update();
		gameManager->renderSnake();
		gameManager->handleEvents();
		gameManager->renderFood();
		
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	delete gameManager;

	return 0;
}