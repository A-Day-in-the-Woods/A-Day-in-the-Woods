#pragma once
#ifndef OPTIONS
#define OPTIONS
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"

class Game;

class Option
{
public:
	Option(Game& game);
	~Option();
	void update();
	void render();
private:
	SDL_Event event;
	Game& m_game;

};
#endif // OPTIONS
