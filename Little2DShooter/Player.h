#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class Player
{

public:
	Player();
	~Player();

	void init(int xpos, int ypos, int size, int max_x, int max_y); // May have to add a refference to the game

	void draw();

	int getX() { return xpos; }
	int getY() { return ypos; }

	void move(int x, int y);

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int max_x;
	int max_y;

};

