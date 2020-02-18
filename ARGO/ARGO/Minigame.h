#pragma once
#ifndef MINIGAME
#define MINIGAME

#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Game.h"
#include <random>
#include <math.h>
#include "Player.h"
#include "InputSystem.h"

class Game;

class MinigameScreen
{
public:
	MinigameScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState);
	~MinigameScreen();

	void processEvent();
	void update();
	void render();
	void spriteMove();
	void startMinGame(int t_mineGameID);
	void setGameState();

	void addPlayer(Player * t_player);

private:
	


	int m_directionX = 0;
	int m_directionY = 0;
	int m_angle = 0;
	
	int m_velocityX = 0;
	int m_velocityY = 0;
	int distance = 0;
	int magnitude = 0;

	int randomNumber(int t_max, int t_min);

	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	std::chrono::duration<float> m_runningTime;
	
	std::chrono::duration<float> m_randTime;
	int m_randomNumber;
	int m_spawn;


	int m_miniGameID = 0;

	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Texture* m_reticleTexture; //camera reticle
	SDL_Texture* m_buttonTexture; // button 
	SDL_Texture* m_honeyPotTexture; //honey pot

	SDL_Rect reticleRectangle;
	SDL_Rect buttonRectangle;
	SDL_Rect buttonRectangle2;
	SDL_Rect buttonRectangle3;
	SDL_Rect buttonRectangle4;
	SDL_Rect honeyRectangle;

	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;


	InputSystem m_inputSystem;
};
#endif // MINIGAME
