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
	CreditScreen(Game& game, SDL_Renderer* t_renderer);
	~CreditScreen();
	void update();
	void render();
	void setGameState();
private:
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
};

#endif // !CREDIT
