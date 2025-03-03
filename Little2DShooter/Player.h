#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class Game;

class Player
{

public:
	Player(Game* game);
	~Player();

	void init(int xpos, int ypos, int size, int max_x, int max_y, int speed, SDL_Texture* player_tex); // May have to add a refference to the game

	void draw();

	int getX() { return xpos; }
	int getY() { return ypos; }

	int getSize() { return size; } // temporary

	void move(char direction);

	void shoot(char direction);

	void createProjectile(int xpos, int ypos, char direction);

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int max_x;
	int max_y;
	int speed;
	int angle = 0;

	Game* game; // needs to be a pointer to the game object. If its an object, it will create a new game object
	SDL_Texture* player_tex;

};

