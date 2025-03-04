#pragma once
#include "SDL.h"
#include <vector>

class Player;

class Enemy
{
public:
	Enemy(Player* player);
	~Enemy();

	void init(int xpos, int ypos, int size, int max_x, int max_y, int speed); // May have to add a refference to the game

	void draw();

	int getX() { return xpos; }
	int getY() { return ypos; }

	void move(char direction);

	void moveAi();

	int getSize() { return size; } // temporary

	//void shoot(char direction);

	//void createProjectile(int xpos, int ypos, char direction);

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int max_x;
	int max_y;
	int speed;

	Uint32 lastMoveTime = 0;
	const Uint32 moveDelay = 40;

	char direction;

	Player* player;
};

