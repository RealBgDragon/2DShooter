#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <string>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "GameOverScreen.h"
#include "PowerUp.h"
#include "map"

class Game
{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void textureInit();

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	void renderScore();

	void renderFps();

	static SDL_Renderer* renderer;

	Player* player;
	Enemy* enemy;

	std::vector<Projectile> projectiles;
	std::vector<PowerUp> powerUps;

	template <typename Obj1, typename Obj2>
	bool hitReg(Obj1* obj1, Obj2* obj2) {
		int x1 = obj1->getX();
		int y1 = obj1->getY();
		int w1 = obj1->getSize();
		int h1 = obj1->getSize();

		int x2 = obj2->getX();
		int y2 = obj2->getY();
		int w2 = obj2->getSize();
		int h2 = obj2->getSize();

		return (x1 < x2 + w2) && (x1 + w1 > x2) &&
			(y1 < y2 + h2) && (y1 + h1 > y2);
	}

	void projectileHitReg(Uint32 currnetTime);

	void spawnPowerUp();

	void powerUpHitReg();

	void restartGame(Uint32 currentTime);

private:
	int cnt = 0;
	bool isRunning;
	bool isGameOver = false;

	SDL_Texture* player_tex;
	SDL_Texture* bullet_tex;
	SDL_Texture* backgroundTex;
	std::map<std::string, SDL_Texture*> powerUpTextures;

	TTF_Font* font;
	SDL_Texture* scoreTexture;
	SDL_Texture* fpsTexture;
	SDL_Rect scoreRect;
	SDL_Rect fpsRect;
	int score = 0;

	Uint32 frameStart;
	int frameTime;
	int lastTime = 0, frameCount = 0;

	Uint32 lastMoveTime = 0;
	const Uint32 moveDelay = 25;

	Uint32 deadTime = 0;
	Uint32 respawnTime = 500;

	Uint32 lastPowerUpTime = 0;
	const Uint32 powerUpDelay = 5000;
	const Uint32 powerUpLifetime = 5000;

	Uint32 restartTime = 0;
	const Uint32 restartTimeout = 500;

	std::array<std::string, 3> powerUpTypes = { "shot_size", "player_speed", "shot_speed" };

	bool isEnemyAlive = true;

	int width;
	int height;
	int speed = 32;
	int enemyXStart = 0;
	int enemyYStart = 0;
	int xstart = 0;
	int ystart = 0;
	int size = 64;
	int highScore = 0;

	SDL_Window* window;

	GameOverScreen* gameOverScreen;
};

