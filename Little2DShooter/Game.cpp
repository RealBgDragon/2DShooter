#include "Game.h"
#include "Player.h"


SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	this->width = width;
	this->height = height;

	int xstart = (width / 2) - ((width / 2) % 32);
	int ystart = (height / 2) - ((height / 2) % 32);

	player = new Player(this);
	enemy = new Enemy(player);

	player->init(xstart, ystart, 32, width, height, speed);
	enemy->init(0, 0, 32, width, height, speed);

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
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (currentTime - lastMoveTime > moveDelay) {
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
	}
	if (currentTime - lastShootTime > shootDelay) {
		if (keystates[SDL_SCANCODE_UP]) {
			player->shoot('u');
			lastShootTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_DOWN]) {
			player->shoot('d');
			lastShootTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_LEFT]) {
			player->shoot('l');
			lastShootTime = currentTime;
		}
		if (keystates[SDL_SCANCODE_RIGHT]) {
			player->shoot('r');
			lastShootTime = currentTime;
		}
	}
}

void Game::update() {
	int currentTime = SDL_GetTicks();
	if (isEnemyAlive) {
		if (hitReg(player, enemy)) {
			isRunning = false;
		}
	}

	if (isEnemyAlive) {
		enemy->moveAi();
	}

	if (!projectiles.empty()) {
		for (auto it = projectiles.begin(); it != projectiles.end(); ) {
			it->move();

			if (isEnemyAlive && hitReg(&(*it), enemy)) {
				isEnemyAlive = false;
				delete enemy;  // Free enemy memory
				enemy = nullptr;
				deadTime = currentTime;
				it = projectiles.erase(it);  // Erase and get next valid iterator
			}
			else if (it->getX() <= 0 || it->getX() >= 800 ||
				it->getY() <= 0 || it->getY() >= 640) {

				it = projectiles.erase(it);  // Erase and get next valid iterator
			}
			else {
				++it;  // Move iterator forward only if no erase happened
			}
		}
	}

	if (!isEnemyAlive) {
		if (currentTime - deadTime > respawnTime) {
			enemy = new Enemy(player);
			enemy->init(0, 0, 32, width, height, speed);
			isEnemyAlive = true;
		}
	}

}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player->draw();
	if (isEnemyAlive) {
		enemy->draw();
	}
	for (Projectile& projectile : projectiles) {  // Iterates directly over each projectile
		projectile.draw();
	}

	frameCount++;
	int currentTime = SDL_GetTicks();
	if (currentTime > lastTime + 1000) {  // Update every second
		std::cout << "FPS: " << frameCount << std::endl;
		lastTime = currentTime;
		frameCount = 0;
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete player; // Free player memory
	player = nullptr;
	delete enemy; // Free enemy memory
	enemy = nullptr;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}