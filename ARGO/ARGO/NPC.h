#pragma once
#include "SDL.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include "Tile.h"
#include "iostream"
#include "Graph.h"
#include "Entity.h"


typedef GraphArc<pair<std::string, int>, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;

class NPC : public Entity
{
public:
	NPC(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g, int t_aiBehaviour, std::function<void(Node*)> f_visit);
	~NPC();
	void update();
	void render(SDL_Renderer* t_renderer);
	void setPosition(float t_x, float t_y);
	void navigateNodes();
	void nodeChange(std::list<GraphArc<pair<std::string, int>, int>> newPoint);
	void rollDice();

	void addItem();
	void removeItem();

	int m_diceNumber;
	bool turn;
private:
	void decision();
	std::function<void(Node*)> m_visit;
	std::vector<Tile>& m_map;
	int currentGameBoardIndex;
	Graph< pair<string, int>, int>& m_graph;
	int m_aiBehaviour;
	SDL_Rect npc;
	int items;
	int m_pathDecision;
};