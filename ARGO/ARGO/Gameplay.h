#pragma once
#ifndef GAMEPLAY
#define GAMEPLAY
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"

class Game;

class Gameplay
{
public:
	Gameplay(Game& game);
	~Gameplay();
	void update();
	void render();
private:
	SDL_Event event;
	Game& m_game;
};

#endif // !GAMEPLAY
