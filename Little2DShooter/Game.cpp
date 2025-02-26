#include "Game.h"
#include "Player.h"


SDL_Renderer* Game::renderer = nullptr;


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {


	int xstart = (width / 2) - ((width / 2) % 32);
	int ystart = (height / 2) - ((height / 2) % 32);
	int speed = 16;

	player = new Player(this);

	player->init(xstart, ystart, 32, width, height, speed);

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		std::cout << "Subsystems Initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// setting the color of the renderer
			std::cout << "Rendrer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;	// stopping if something is wrong
	}

}

void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
	}

	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastMoveTime > moveDelay) {
		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		if (keystates[SDL_SCANCODE_W]) {
			player->move('u');
			lastMoveTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_S]) {
			player->move('d');
			lastMoveTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_A]) {
			player->move('l');
			lastMoveTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_D]) {
			player->move('r');
			lastMoveTime = currentTime;
		}

		if (keystates[SDL_SCANCODE_UP]) {
			player->shoot('u');
			lastMoveTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_DOWN]) {
			player->shoot('d');
			lastMoveTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_LEFT]) {
			player->shoot('l');
			lastMoveTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_RIGHT]) {
			player->shoot('r');
			lastMoveTime = currentTime;
		}
	}
}

void Game::update() {
	/*cnt++;
	std::cout << cnt << std::endl;*/
	for (Projectile& projectile : projectiles) {  // Iterates directly over each projectile
		projectile.move();
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player->draw();
	for (Projectile& projectile : projectiles) {  // Iterates directly over each projectile
		projectile.draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete player; // Free player memory
	player = nullptr;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}