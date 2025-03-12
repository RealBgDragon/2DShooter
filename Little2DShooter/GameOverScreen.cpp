#include "GameOverScreen.h"
#include <string>

GameOverScreen::GameOverScreen()
{
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::init(SDL_Renderer* renderer, TTF_Font* font, int width, int height, int highScore) {
	this->renderer = renderer;
	this->font = font;

	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", white);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = TTF_RenderText_Solid(font, "Press 'r' to restart", white);
	restartTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); 

	std::string highScoreString = "High Score: " + std::to_string(highScore);
	surface = TTF_RenderText_Solid(font, highScoreString.c_str(), white);
	highScoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); 

	messageRect.x = width / 2 - 300;
	messageRect.y = height / 2 - 200;
	messageRect.w = 600;
	messageRect.h = 300;
	
	restartRect.x = width / 2 - 150;
	restartRect.y = height / 2 + 100;
	restartRect.w = 300;
	restartRect.h = 100;

	highScoreRect.x = width / 2 - 175;
	highScoreRect.y = height / 2 - 300;
	highScoreRect.w = 350;
	highScoreRect.h = 150;

}

void GameOverScreen::draw() {
	SDL_RenderCopy(renderer, texture, NULL, &messageRect);
	SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
	SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
}