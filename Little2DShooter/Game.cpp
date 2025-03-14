#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	this->width = width - 32;
	this->height = height - 32;

	xstart = (width / 2) - ((width / 2) % size);
	ystart = (height / 2) - ((height / 2) % size);

	do {
		enemyXStart = (rand() % (width / size)) * size;
		enemyYStart = (rand() % (height / size)) * size;
	} while (abs(enemyXStart - xstart) < 100 || abs(enemyYStart - ystart) < 100);

	player = new Player(this);
	enemy = new Enemy(player);

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

	// Player image
	textureInit();

	player->init(xstart, ystart, size, this->width, this->height, speed, player_tex);
	enemy->init(enemyXStart, enemyYStart, size, this->width, this->height, speed);

	if (TTF_Init() == -1) {
		std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont("PIXEAB__.ttf", 24); // Ensure "arial.ttf" or another font is in your project folder
	if (!font) {
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
	}


}

void Game::textureInit() {
	SDL_Surface* player_sur = IMG_Load("C:\\Users\\Martin\\Desktop\\Mycraft\\Player.png");  // Player model
	player_tex = SDL_CreateTextureFromSurface(renderer, player_sur);
	SDL_FreeSurface(player_sur);

	SDL_Surface* bullet_sur = IMG_Load("C:\\Users\\Martin\\Desktop\\Mycraft\\bullet.png");	// Projectile model
	bullet_tex = SDL_CreateTextureFromSurface(renderer, bullet_sur);
	SDL_FreeSurface(bullet_sur);

	SDL_Surface* tempSurface = IMG_Load("C:\\Users\\Martin\\Desktop\\Mycraft\\shot_size_powerup.png");
	powerUpTextures["shot_size"] = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	tempSurface = IMG_Load("C:\\Users\\Martin\\Desktop\\Mycraft\\movement_speed.png");
	powerUpTextures["player_speed"] = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	tempSurface = IMG_Load("C:\\Users\\Martin\\Desktop\\Mycraft\\shot_speed.png");
	powerUpTextures["shot_speed"] = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	tempSurface = IMG_Load("C:\\Users\\Martin\\Desktop\\Mycraft\\background.png");
	backgroundTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

// Projectile hit registration
void Game::projectileHitReg(Uint32 currentTime) {
	if (!projectiles.empty()) {
		for (auto it = projectiles.begin(); it != projectiles.end(); ) {
			it->move();

			if (isEnemyAlive && hitReg(&(*it), enemy)) {
				score++;
				isEnemyAlive = false;
				delete enemy;  // Free enemy memory
				enemy = nullptr;
				deadTime = currentTime;
				it = projectiles.erase(it);  // Erase and get next valid iterator
			}
			else if (it->getX() <= 0 || it->getX() >= width ||
				it->getY() <= 0 || it->getY() >= height) {

				it = projectiles.erase(it);  // Erase and get next valid iterator
			}
			else {
				++it;  // Move iterator forward only if no erase happened
			}
		}
	}
}

void Game::powerUpHitReg() {
	if (!powerUps.empty()) {
		for (auto it = powerUps.begin(); it != powerUps.end(); ) {
			if (hitReg(player, &(*it))) {
				it->addEffect(player);
				it = powerUps.erase(it);  // Erase and get next valid iterator
			}
			else {
				++it;  // Move iterator forward only if no erase happened
			}
		}
	}
}

// Power up spawn
void Game::spawnPowerUp() {
	PowerUp powerUp;
	int powerUpXStart, powerUpYStart;
	do {
		powerUpXStart = (rand() % (width / size)) * size;
		powerUpYStart = (rand() % (height / size)) * size;
	} while (abs(powerUpXStart - player->getX()) < 100 || abs(powerUpYStart - player->getY()) < 100);
	int random = rand() % powerUpTypes.size();
	std::string powerUpType = powerUpTypes[random];
	powerUp.init(powerUpXStart, powerUpYStart, size, speed, powerUpType, powerUpTextures[powerUpType]);
	powerUps.emplace_back(powerUp);

}

// Score rendering
void Game::renderScore() {
	if (scoreTexture) {
		SDL_DestroyTexture(scoreTexture);
		scoreTexture = nullptr;
	}
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

void Game::renderFps() {
	frameCount++;
	int currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 1000) {  // Update every second
		if (fpsTexture) {  // Destroy old FPS texture
			SDL_DestroyTexture(fpsTexture);
			fpsTexture = nullptr;
		}

		SDL_Color white = { 255, 255, 255, 255 }; // White text
		std::string fpsText = "FPS: " + std::to_string(frameCount);

		SDL_Surface* surface = TTF_RenderText_Solid(font, fpsText.c_str(), white);
		if (!surface) {
			std::cout << "Failed to create surface: " << TTF_GetError() << std::endl;
			return;
		}

		fpsTexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!fpsTexture) {
			std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
		}

		fpsRect = { 1920 - (surface->w + 10), 10, surface->w, surface->h }; // Position at top-right

		SDL_FreeSurface(surface);
		lastTime = currentTime;
		frameCount = 0;
	}
}

// Function handling game restart
void Game::restartGame(Uint32 currentTime) {
	score = 0;
	isGameOver = false;
	restartTime = currentTime;	// for enemy ai delay
	enemy->setX(enemyXStart);
	enemy->setY(enemyYStart);
	player->setX(xstart);
	player->setY(ystart);
	projectiles.clear();
	powerUps.clear();
	if (gameOverScreen) {
		delete gameOverScreen; // Free gameOverScreen memory
		gameOverScreen = nullptr;
	}
}

void Game::handleEvents() {
	SDL_Event event;
	Uint32 currentTime = SDL_GetTicks();

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
			restartGame(currentTime);
		}
	}

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

	if (keystates[SDL_SCANCODE_UP]) {
		player->shoot('u', bullet_tex, currentTime);
	}
	else if (keystates[SDL_SCANCODE_DOWN]) {
		player->shoot('d', bullet_tex, currentTime);
	}
	else if (keystates[SDL_SCANCODE_LEFT]) {
		player->shoot('l', bullet_tex, currentTime);
	}
	else if (keystates[SDL_SCANCODE_RIGHT]) {
		player->shoot('r', bullet_tex, currentTime);
	}

}

void Game::update() {

	if (!isGameOver) {
		Uint32 currentTime = SDL_GetTicks();
		if (isEnemyAlive) {
			if (hitReg(player, enemy)) {
				if (score > highScore) {
					highScore = score;
				}
				isGameOver = true;
			}
		}

		if (isEnemyAlive) {
			if (currentTime - restartTime > restartTimeout) {
				enemy->moveAi();	// Enemy movement ai
			}
		}

		projectileHitReg(currentTime);
		powerUpHitReg();
		player->update(currentTime);


		if (currentTime - lastPowerUpTime > powerUpDelay) {
			spawnPowerUp();
			lastPowerUpTime = currentTime;
		}

		if (!isEnemyAlive) {
			if (currentTime - deadTime > respawnTime) {
				do {
					enemyXStart = (rand() % (width / size)) * size;
					enemyYStart = (rand() % (height / size)) * size;
				} while (abs(enemyXStart - player->getX()) < 100 || abs(enemyYStart - player->getY()) < 100);
				enemy = new Enemy(player);
				enemy->init(enemyXStart, enemyYStart, size, width, height, speed);
				isEnemyAlive = true;
			}
		}
	}

}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);

	if (isGameOver) {
		if (!gameOverScreen) {
			gameOverScreen = new GameOverScreen();
			gameOverScreen->init(renderer, font, width, height, highScore);
		}
		renderScore();
		if (scoreTexture) {
			SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
		}
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
		for (PowerUp& powerUp : powerUps) {  // Iterates directly over each power up
			powerUp.draw();
		}

		renderScore();	// Render the score

		if (scoreTexture) {
			SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
		}

		renderFps();	// Render the fps
		SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);

	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	if (player) {
		delete player; // Free player memory
		player = nullptr;
	}
	if (enemy) {
		delete enemy; // Free enemy memory
		enemy = nullptr;
	}
	if (gameOverScreen) {
		delete gameOverScreen; // Free gameOverScreen memory
		gameOverScreen = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (font) {
		TTF_CloseFont(font);
		font = nullptr;
	}
	if (scoreTexture) {
		SDL_DestroyTexture(scoreTexture);
		scoreTexture = nullptr;
	}
	if (fpsTexture) {
		SDL_DestroyTexture(fpsTexture);
		fpsTexture = nullptr;
	}
	if (player_tex) {
		SDL_DestroyTexture(player_tex);
		player_tex = nullptr;
	}
	if (bullet_tex) {
		SDL_DestroyTexture(bullet_tex);
		bullet_tex = nullptr;
	}
	// Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}
