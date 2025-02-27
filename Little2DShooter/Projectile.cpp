#include "Projectile.h"
#include "Game.h"
#include <vector>

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::init(int xpos, int ypos, int size, int max_x, int max_y, char direction, int speed) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->max_x = max_x;
	this->max_y = max_y;
	this->direction = direction;
	this->speed = speed;
}

void Projectile::draw() {
	SDL_SetRenderDrawColor(Game::renderer, 191, 191, 191, 1);
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Projectile::move() {
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