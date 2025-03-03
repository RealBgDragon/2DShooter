#include "PowerUp.h"
#include "Game.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::init(int xpos, int ypos, int size/*, SDL_Texture* powerup_tex*/) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	std::cout << "Powerup size: " << powerUpTypes.size() << std::endl;
	int random = rand() % powerUpTypes.size();
	std::cout << "Powerup number: " << random << std::endl;
	this->powerupType = powerUpTypes[random];
	std::cout << "Powerup type: " << powerupType << std::endl;
}

void PowerUp::draw() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
	SDL_Rect rect = { xpos, ypos, size, size };
	SDL_RenderFillRect(Game::renderer, &rect);
}

void PowerUp::addEffect() {
	if (powerupType == "shot_size") {
		std::cout << "Shot size powerup collected" << std::endl;
	}
	else if (powerupType == "player_speed") {
		std::cout << "Player speed powerup collected" << std::endl;
	}
	else if (powerupType == "shot_speed") {
		std::cout << "Shot speed powerup collected" << std::endl;
	}
}