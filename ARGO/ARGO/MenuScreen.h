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
	MenuScreen(Game& game, SDL_Renderer* t_renderer);
	~MenuScreen();
	void update();
	void render();
	void setGameState();
private:
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer

};
#endif // MENU
