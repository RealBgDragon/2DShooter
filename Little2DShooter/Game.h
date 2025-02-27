#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"

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

	static SDL_Renderer* renderer;

	Player* player;
	Enemy* enemy;

	std::vector<Projectile> projectiles;

private:
	int cnt = 0;
	bool isRunning;

	Uint32 frameStart;
	int frameTime;
	int lastTime = 0, frameCount = 0;

	Uint32 lastMoveTime = 0;
	Uint32 lastShootTime = 0;
	const Uint32 moveDelay = 50;
	const Uint32 shootDelay = 500;


	SDL_Window* window;
};

