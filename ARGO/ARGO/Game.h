#pragma once
#include <SDL.h>
#include <SDL_image.h>


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

#include "Entity.h"
#include "HealthComp.h"
#include "HealthSystem.h"
#include "PositionComp.h"
#include "RenderSystem.h"

class MenuScreen;
class OptionMenu;
class Gameplay;
class CreditScreen;

typedef GraphArc<pair<std::string, int>, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;


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
	void newGameState(GameState t_newState) { m_currentState = t_newState; };

private:
	void processEvent();
	void update();
	void render();
	void clean();

	MenuScreen* m_menuscreen;
	Option* m_optionscreen;
	Gameplay* m_gameplayscreen;
	CreditScreen* m_creditscreen;
	
	SDL_Window* m_window;	// game window
	SDL_Renderer* m_renderer;	// game renderer
	
	bool m_isRunning;	// is game running?


	SDL_Texture* m_TestingTexture;


	// ------ A* stuff ----------
	void aStar();

	void initNodeFiles();

	map<string, int> nodemap;
	pair<string, int> nodeLabel;

	int posX = 0;
	int posY = 0;
	int index = 0;
	ifstream myfile;


	string from, to;
	int weight;

	bool startAstar{ false };
	//------! A* stuff ------------


	//---------Entity + Components-----------
	Entity* m_testEntity = new Entity(0);

	HealthSystem m_healthSystem;

};

