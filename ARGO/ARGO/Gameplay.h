#pragma once
#ifndef GAMEPLAY
#define GAMEPLAY
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include "Tile.h"
#include <map>
#include "Graph.h"

class Game;


typedef GraphArc<pair<std::string, int>, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;


class Gameplay
{
public:
	Gameplay(Game& game, SDL_Renderer* t_renderer, SDL_Event& event);
	~Gameplay();
	void update();
	void render();
	void setGameState();
private:


	std::vector<Tile> m_tile;


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

	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;
};

#endif // !GAMEPLAY
