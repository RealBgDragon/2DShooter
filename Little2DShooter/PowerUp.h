#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <array>
#include "Player.h"

class PowerUp
{

public:
	PowerUp();
	~PowerUp();

	void init(int xpos, int ypos, int size, int speed, std::string powerupType, SDL_Texture* powerup_tex);

	void draw();

	void addEffect(Player* player);

	int getX() { return xpos; }
	int getY() { return ypos; }

	int getSize() { return size; } // temporary

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int speed;
	std::string powerupType = "";
	int duration = 5000;
	SDL_Texture* powerup_tex;
};

