#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void init(SDL_Renderer* renderer, TTF_Font* font,int width, int height, int highScore);

	void draw();

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Texture* restartTexture;
	SDL_Texture* highScoreTexture;
	SDL_Rect messageRect;
	SDL_Rect restartRect;
	SDL_Rect highScoreRect;
};

