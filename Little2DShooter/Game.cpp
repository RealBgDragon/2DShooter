#include "Game.h"


SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	this->width = width;
	this->height = height;

	int xstart = (width / 2) - ((width / 2) % size);
	int ystart = (height / 2) - ((height / 2) % size);

	do {
		enemyXStart = (rand() % (width / size)) * size;
		enemyYStart = (rand() % (height / size)) * size;
	} while (abs(enemyXStart - xstart) < 100 || abs(enemyYStart - ystart) < 100);

	player = new Player(this);
	enemy = new Enemy(player);

	player->init(xstart, ystart, size, width, height, speed);
	enemy->init(enemyXStart, enemyYStart, size, width, height, speed);

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

	if (TTF_Init() == -1) {
		std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont("PIXEAB__.ttf", 24); // Ensure "arial.ttf" or another font is in your project folder
	if (!font) {
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
	}


}

void Game::projectileHitReg(Uint32 currentTime) {
	if (!projectiles.empty()) {
		for (auto it = projectiles.begin(); it != projectiles.end(); ) {
			it->move();

			if (isEnemyAlive && hitReg(&(*it), enemy)) {
				score++;
				std::cout << "Score: " << score << std::endl;
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
}

void Game::renderScore() {
	SDL_Color white = { 255, 255, 255, 255 }; // White text
	std::string scoreText = "Score: " + std::to_string(score);

	SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
	if (!surface) {
		std::cout << "Failed to create surface: " << TTF_GetError() << std::endl;
		return;
	}

	scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!scoreTexture) {
		std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
	}

	scoreRect = { 10, 10, surface->w, surface->h }; // Position at (10,10)

	SDL_FreeSurface(surface);
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
	Uint32 currentTime = SDL_GetTicks();
	if (isEnemyAlive) {
		if (hitReg(player, enemy)) {
			//isRunning = false;
			isGameOver = true;
		}
	}

	if (isEnemyAlive) {
		enemy->moveAi();
	}

	projectileHitReg(currentTime);

	if (!isEnemyAlive) {
		if (currentTime - deadTime > respawnTime) {
			do {
				enemyXStart = (rand() % (height / size)) * size;
				enemyYStart = (rand() % (width / size)) * size;
			} while (abs(enemyXStart - player->getX()) < 100 || abs(enemyYStart - player->getY()) < 100);
			std::cout << "Respawning enemy at: " << enemyXStart << ", " << enemyYStart << std::endl;
			enemy = new Enemy(player);
			enemy->init(enemyYStart, enemyXStart, size, width, height, speed);
			isEnemyAlive = true;
		}
	}

}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (isGameOver) {
		if (!gameOverScreen) {
			gameOverScreen = new GameOverScreen();
			gameOverScreen->init(renderer, font, width, height);
		}
		renderScore();
		gameOverScreen->draw();
		SDL_RenderPresent(renderer);
		return;
	}
	else {

		player->draw();
		if (isEnemyAlive) {
			enemy->draw();
		}
		for (Projectile& projectile : projectiles) {  // Iterates directly over each projectile
			projectile.draw();
		}

		renderScore(); // Render the score

		if (scoreTexture) {
			SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
		}

		frameCount++;
		int currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000) {  // Update every second
			std::cout << "FPS: " << frameCount << std::endl;
			lastTime = currentTime;
			frameCount = 0;
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete player; // Free player memory
	player = nullptr;
	delete enemy; // Free enemy memory
	enemy = nullptr;
	delete gameOverScreen; // Free enemy memory
	gameOverScreen = nullptr;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	TTF_CloseFont(font);
	SDL_DestroyTexture(scoreTexture);
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}