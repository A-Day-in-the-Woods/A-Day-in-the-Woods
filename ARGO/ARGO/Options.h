
#ifndef OPTIONS
#define OPTIONS

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include <InputSystem.h>

class Game;

class OptionScreen
{
public:
	OptionScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity);
	~OptionScreen();
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

	GameState& m_currentState;
	InputSystem m_inputSystem;
	std::vector<Player*> m_entity;
};
#endif // OPTIONS
