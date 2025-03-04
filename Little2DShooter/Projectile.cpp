#include "Projectile.h"
#include "Game.h"
#include <vector>

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::init(int xpos, int ypos, int size, int max_x, int max_y, char direction, int speed, SDL_Texture* bullet_tex) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->max_x = max_x;
	this->max_y = max_y;
	this->direction = direction;
	this->speed = speed;
	this->bullet_tex = bullet_tex;

	if (direction == 'l') angle = 270;
	else if (direction == 'r') angle = 90;
	else if (direction == 'u') angle = 0;
	else if (direction == 'd') angle = 180;
}

void Projectile::draw() {

	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::renderer, bullet_tex, NULL, &rect, angle, NULL, flip);

	/*SDL_SetRenderDrawColor(Game::renderer, 191, 191, 191, 1);
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);*/
}

void Projectile::move() {
	if (direction == 'l' && xpos > 0) {
		xpos -= speed;
		angle = 270;
	}
	else if (direction == 'r' && xpos < max_x) {
		xpos += speed;
		angle = 90;
	}
	else if (direction == 'u' && ypos > 0) {
		ypos -= speed;
		angle = 0;
	}
	else if (direction == 'd' && ypos < max_y) {
		ypos += speed;
		angle = 180;
	}
}