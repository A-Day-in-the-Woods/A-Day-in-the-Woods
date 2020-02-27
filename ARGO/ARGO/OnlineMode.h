
#ifndef ONLINEMODE_H
#define ONLINEMODE_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include <string>
#include <InputSystem.h>
#include "NumFromString.cpp"
//#include "Client.h"

class Game;

class OnlineMode
{
public:
	OnlineMode(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity);
	~OnlineMode();
	void update();
	void render();
	void processEvent();
	void setGameState();
private:
	int m_numberPlayers;
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	//Client* m_client;
	

	GameState& m_currentState;
	InputSystem m_inputSystem;
	std::vector<Player*> m_entity;
};
#endif // OPTIONS
