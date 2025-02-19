#include "Game.h"
#include "Player.h"


SDL_Renderer* Game::renderer = nullptr;


Game::Game()
{}

Game::~Game()
{}

Player* player = new Player();

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	player->init(width / 2, height / 2, 32, width, height);

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
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_w:
			player->move(0, -32);   // Move up
			break;
		case SDLK_s:
			player->move(0, 32);    // Move down
			break;
		case SDLK_a:
			player->move(-32, 0);   // Move left
			break;
		case SDLK_d:
			player->move(32, 0);    // Move right
			break;
		default:
			break;
		}

	default:
		break;
	}
}

void Game::update() {
	cnt++;
	std::cout << cnt << std::endl;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}