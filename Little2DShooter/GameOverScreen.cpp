#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::init(SDL_Renderer* renderer, TTF_Font* font, int width, int height) {
	this->renderer = renderer;
	this->font = font;

	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", white);
	if (!surface) {
		std::cout << "Failed to create surface: " << TTF_GetError() << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
	}

	messageRect.x = width / 2 - 150;
	messageRect.y = height / 2 - 100;
	messageRect.w = 300;
	messageRect.h = 200;
	
	SDL_FreeSurface(surface);
}

void GameOverScreen::draw() {
	SDL_RenderCopy(renderer, texture, NULL, &messageRect);
}