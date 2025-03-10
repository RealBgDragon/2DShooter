#pragma once
#include "SDL.h"
#include <vector>

class Projectile
{
public:
	Projectile();
	~Projectile();

	void init(int xpos, int ypos, int size, int max_x, int max_y, char direction, int speed, SDL_Texture* bullet_tex);

	void draw();

	int getX() { return xpos; }
	int getY() { return ypos; }

	int getSize() { return size; } // temporary

	void move();

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int max_x;
	int max_y;
	int speed;
	int angle;
	char direction;

	SDL_Texture* bullet_tex;
};

