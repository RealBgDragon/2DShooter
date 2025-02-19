#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player()
{}

Player::~Player()
{}

void Player::init(int xpos, int ypos, int size, int max_x, int max_y) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->max_x = max_x;
	this->max_y = max_y;
}

void Player::draw() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
	std::cout << "Drawing player at: " << xpos << ", " << ypos << " " << size << std::endl;
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Player::move(int x, int y) {

	if (xpos < max_x && ypos < max_y) {
		xpos += x;
		ypos += y;
	}
}