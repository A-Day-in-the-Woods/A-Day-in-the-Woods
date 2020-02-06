#pragma once
#ifndef MENU
#define MENU

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"

class Game;

class MenuScreen
{
public:
	MenuScreen(Game& game);
	~MenuScreen();
	void update();
	void render();
private:
	SDL_Event event;
	Game& m_game;

};
#endif // MENU
