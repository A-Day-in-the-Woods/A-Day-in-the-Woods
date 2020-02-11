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
	MinigameScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event);
	~MinigameScreen();
	void update();
	void render();
	void setGameState();
private:
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;
};
#endif // MINIGAME
