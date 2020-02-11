#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include "Graph.h"

#include "GameStates.h"
#include "MenuScreen.h"
#include "Options.h"
#include "Gameplay.h"
#include "CreditsScreen.h"
#include "Minigame.h"

#include "Entity.h"
#include "HealthComp.h"
#include "HealthSystem.h"
#include "PositionComp.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "InputSystem.h"
#include "Player.h"


class MenuScreen;
class OptionScreen;
class Gameplay;
class CreditScreen;
class MinigameScreen;




/// <summary>
/// Main Game Class
/// </summary>
class Game
{
public:
	Game();
	~Game();
	void run();
	GameState m_currentState{ GameState::Menu };
	void setGameState(GameState t_newState) { m_currentState = t_newState; };

private:
	void processEvent();
	void update();
	void render();
	void clean();

	MenuScreen* m_menuscreen;
	OptionScreen* m_optionscreen;
	Gameplay* m_gameplayscreen;
	CreditScreen* m_creditscreen;
	MinigameScreen* m_minigamescreen;
	
	SDL_Window* m_window;	// game window
	SDL_Renderer* m_renderer;	// game renderer

	Player m_player;

	bool m_isRunning;	// is game running?


	SDL_Texture* m_TestingTexture;
	SDL_Event event;



	//---------Entity + Components-----------
	Entity* m_testEntity = new Entity(0);
	
	HealthSystem m_healthSystem;
	InputSystem m_inputSystem;
};

