#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <array>

class PowerUp
{

public:
	PowerUp();
	~PowerUp();

	void init(int xpos, int ypos, int size/*, SDL_Texture* powerup_tex*/);

	void draw();

	void addEffect();

	int getX() { return xpos; }
	int getY() { return ypos; }

	int getSize() { return size; } // temporary


private:
	int xpos;
	int ypos;
	int size;
	int color;
	std::array<std::string, 3> powerUpTypes = { "shot_size", "player_speed", "shot_speed" };
	std::string powerupType = "";
	//SDL_Texture* powerup_tex;
};

