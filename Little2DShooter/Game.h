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

class Game
{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	void renderScore();

	static SDL_Renderer* renderer;

	Player* player;
	Enemy* enemy;

	std::vector<Projectile> projectiles;

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

private:
	int cnt = 0;
	bool isRunning;
	bool isGameOver = false;

	TTF_Font* font;
	SDL_Texture* scoreTexture;
	SDL_Rect scoreRect;
	int score = 0;

	Uint32 frameStart;
	int frameTime;
	int lastTime = 0, frameCount = 0;

	Uint32 lastMoveTime = 0;
	Uint32 lastShootTime = 0;
	const Uint32 moveDelay = 50;
	const Uint32 shootDelay = 500;

	bool isEnemyAlive = true;
	Uint32 deadTime = 0;
	Uint32 respawnTime = 500;

	int width;
	int height;
	int speed = 16;
	int enemyXStart = 0;
	int enemyYStart = 0;
	int size = 32;

	SDL_Window* window;

	GameOverScreen* gameOverScreen;
};

