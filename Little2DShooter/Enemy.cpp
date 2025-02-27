#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Player* player)
{
	this->player = player;
}

Enemy::~Enemy()
{
}

void Enemy::init(int xpos, int ypos, int size, int max_x, int max_y, int speed) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->max_x = max_x;
	this->max_y = max_y;
	this->speed = speed;
}

void Enemy::draw() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 1);
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Enemy::move(char direction) {
	if (direction == 'l' && xpos > 0) {
		xpos -= speed;
	}
	else if (direction == 'r' && xpos < max_x) {
		xpos += speed;
	}
	else if (direction == 'u' && ypos > 0) {
		ypos -= speed;
	}
	else if (direction == 'd' && ypos < max_y) {
		ypos += speed;
	}
}

void Enemy::moveAi() {

	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastMoveTime < moveDelay) {
		return; // Skip movement if not enough time has passed
	}

	lastMoveTime = currentTime;

	int random = rand() % 2;
	if (random == 0) {

		if (xpos > player->getX()) {
			direction = 'l';
			move(direction);
		}
		else if (xpos < player->getX()) {
			direction = 'r';
			move(direction);
		}
	}
	else if (random == 1) {
		if (ypos > player->getY()) {
			direction = 'u';
			move(direction);
		}
		else if (ypos < player->getY()) {
			direction = 'd';
			move(direction);
		}
	}


}