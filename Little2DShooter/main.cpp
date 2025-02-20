#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 30;
	const int freameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Little2DShooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (freameDelay > frameTime) {
			SDL_Delay(freameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}