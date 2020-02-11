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
	Gameplay(Game& game, SDL_Renderer* t_renderer);
	~Gameplay();
	void update();
	void render();
	void setGameState();
private:
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
};

#endif // !GAMEPLAY
