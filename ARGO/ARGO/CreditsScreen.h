#pragma once
#ifndef CREDIT
#define CREDIT
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"

class Game;

class CreditScreen
{
public:
	CreditScreen(Game& game);
	~CreditScreen();
	void update();
	void render();
private:
	SDL_Event event;
	Game& m_game;

};

#endif // !CREDIT
