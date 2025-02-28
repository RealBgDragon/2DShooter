#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void init(SDL_Renderer* renderer, TTF_Font* font,int width, int height);

	void draw();

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Rect messageRect;
};

