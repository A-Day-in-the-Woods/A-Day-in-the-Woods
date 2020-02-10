#pragma once
#ifndef MINIGAME
#define MINIGAME

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"

class Game;

class MinigameScreen
{
public:
	MinigameScreen(Game& game, SDL_Renderer* t_renderer);
	~MinigameScreen();
	void update();
	void render();
	void setGameState();
private:
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Texture* m_reticleTexture; //camera reticle
	SDL_Rect destR;

	SDL_Texture* m_buttonTexture; //camera reticle
	SDL_Rect destR2;
	SDL_Rect destR3;
	SDL_Rect destR4;
	SDL_Rect destR5;

	SDL_Renderer* m_renderer;	// game renderer
};
#endif // MINIGAME
