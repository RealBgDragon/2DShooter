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

void Player::init(int xpos, int ypos, int size, int max_x, int max_y, int speed, SDL_Texture* player_tex) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->max_x = max_x;
	this->max_y = max_y;
	this->startSpeed = speed;
	this->speed = speed;
	this->startShotSize = size;
	this->shotSize = size;
	this->player_tex = player_tex;
}

void Player::draw() {
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::renderer, player_tex, NULL, &rect, angle, NULL, flip);
}

void Player::move(char direction) {

	if (direction == 'l' && xpos > 0) {
		angle = 270;
		xpos -= speed;
	}
	else if (direction == 'r' && xpos < max_x) {
		angle = 90;
		xpos += speed;
	}
	else if (direction == 'u' && ypos > 0) {
		angle = 0;
		ypos -= speed;
	}
	else if (direction == 'd' && ypos < max_y) {
		angle = 180;
		ypos += speed;
	}

}

void Player::shoot(char direction, SDL_Texture* bullet_tex) {
	Projectile projectile;
	projectile.init(xpos, ypos, shotSize, max_x, max_y, direction, speed, bullet_tex);
	game->projectiles.emplace_back(projectile);
}

void Player::update(Uint32 currentTime) {
	int speedCount = 0;
	int shotCount = 0;
	int shotSpeedCount = 0;
	for (auto it = activePowerUps.begin(); it != activePowerUps.end(); ) {
		if (currentTime >= it->expirationTime) {

			if (it->type == "player_speed") {
				speedCount++;
				//speed = startSpeed;
			}
			else if (it->type == "shot_size") {
				shotCount++;
				//shotSize = startShotSize;
			}
			else if (it->type == "shot_speed") {
				shotSpeedCount++;
			}

			it = activePowerUps.erase(it);  // Remove and get next valid iterator
		}
		else {
			++it;
		}
	}
	if (speedCount == 1) {
		speed = startSpeed;
	}
	if (shotCount == 1) {
		shotSize = startShotSize;
	}

	//TODO find a solution (the new powerup dissapears alongside the old)
}