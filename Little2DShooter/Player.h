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

	void init(int xpos, int ypos, int size, int max_x, int max_y, int speed, SDL_Texture* player_tex);

	void draw();

	int getX() { return xpos; }
	int getY() { return ypos; }

	void setX(int newX) { xpos = newX; }
	void setY(int newY) { ypos = newY; }

	void setShotSize(int newSize) { shotSize = newSize; }

	void setSpeed(int newSpeed) { speed = newSpeed; }

	void setShootDelay(int newShootDelay) { shootDelay = newShootDelay; }
	Uint32 getShootDelay() { return shootDelay; }

	int getSize() { return size; } // temporary

	void move(char direction);

	void shoot(char direction, SDL_Texture* bullet_tex, Uint32 currentTime);

	void update(Uint32 currentTime);

	struct ActivePowerUp {
		std::string type;
		Uint32 expirationTime;
	};

	std::vector<ActivePowerUp> activePowerUps;

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int max_x;
	int max_y;
	int speed;
	int startSpeed;
	int startShotSize;
	int shotSize;
	int angle = 0;
	Uint32 lastShootTime = 0;
	Uint32 shootDelay = 500;
	const Uint32 intialShootDelay = shootDelay;


	Game* game; // needs to be a pointer to the game object. If its an object, it will create a new game object
	SDL_Texture* player_tex;

};

