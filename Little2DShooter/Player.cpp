#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include "Game.h"

Player::Player(Game* game)
{
	this->game = game;
}

Player::~Player()
{}

void Player::init(int xpos, int ypos, int size, int max_x, int max_y, int speed) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->max_x = max_x;
	this->max_y = max_y;
	this->speed = speed;
}

void Player::draw() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Player::move(char direction) {

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

void Player::shoot(char direction) {
	std::cout << "Shooting in direction: " << direction << std::endl;
	createProjectile(xpos, ypos, direction);
}

void Player::createProjectile(int xpos, int ypos, char direction) {
	Projectile projectile;
	projectile.init(xpos, ypos, size, max_x, max_y, direction, speed);
	game->projectiles.emplace_back(projectile);

	std::cout << "Creating projectile at: " << xpos << ", " << ypos << std::endl;
}