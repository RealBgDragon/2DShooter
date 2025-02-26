#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "Player.h"

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

	std::vector<Projectile> projectiles;

private:
	int cnt = 0;
	bool isRunning;

	Uint32 lastMoveTime = 0;
	const Uint32 moveDelay = 50;


	SDL_Window* window;
};

