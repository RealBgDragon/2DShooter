#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <string>

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

	std::vector<std::string> projectiles;

private:
	int cnt = 0;
	bool isRunning;

	Uint32 lastMoveTime = 0;
	const Uint32 moveDelay = 40;


	SDL_Window* window;
};

