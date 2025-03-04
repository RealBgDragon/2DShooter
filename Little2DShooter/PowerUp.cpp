#include "PowerUp.h"
#include "Game.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::init(int xpos, int ypos, int size, int speed, std::string powerupType, SDL_Texture* powerup_tex) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->powerupType = powerupType;
	this->speed = speed;
	this->powerup_tex = powerup_tex;
	std::cout << "Powerup type: " << powerupType << std::endl;
}

void PowerUp::draw() {
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::renderer, powerup_tex, NULL, &rect, 0, NULL, flip);

	/*SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);*/
}

void PowerUp::addEffect(Player* player) {
	if (powerupType == "shot_size") {
		std::cout << "Shot size powerup collected" << std::endl;
		player->activePowerUps.push_back({ powerupType, SDL_GetTicks() + duration });
		player->setShotSize(size * 2);
	}
	else if (powerupType == "player_speed") {
		std::cout << "Player speed powerup collected" << std::endl;
		player->activePowerUps.push_back({ powerupType, SDL_GetTicks() + duration });
		player->setSpeed(speed * 2);
	}
	else if (powerupType == "shot_speed") {
		std::cout << "Shot speed powerup collected" << std::endl;
		player->activePowerUps.push_back({ powerupType, SDL_GetTicks() + duration });
		//TODO add this
	}
}