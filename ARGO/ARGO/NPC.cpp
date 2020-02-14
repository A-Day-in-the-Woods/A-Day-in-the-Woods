#include "NPC.h"

NPC::NPC(std::vector<Tile>& t_map, Graph<pair<string, int>, int>& t_g, int t_aiBehaviour, std::function<void(Node*)> t_visit) :
	m_map(t_map),
	m_graph(t_g),
	m_aiBehaviour(t_aiBehaviour),
	m_visit(t_visit),
	Entity(2)
{
	npc.x = 0;
	npc.y = 0;
	npc.h = 20;
	npc.w = 20;
}

NPC::~NPC()
{
}

void NPC::update()
{
	setPosition(m_map[currentGameBoardIndex].getPosition().x, m_map[currentGameBoardIndex].getPosition().y);
}

void NPC::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 211, 15, 0, 255);
	SDL_RenderFillRect(t_renderer, &npc);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void NPC::setPosition(float t_x, float t_y)
{
	npc.x = t_x;
	npc.y = t_y;
}

void NPC::decision()
{
	if (m_aiBehaviour == 1)
	{
		std::vector<Node*> path;
		m_graph.aStar(m_graph.nodeIndex(0), m_graph.nodeIndex(41), m_visit, path);
	}
	else if (m_aiBehaviour == 2)
	{
		//std::vector<Node*> path;
		m_graph.adaptedBreadthFirst(m_graph.nodeIndex(0), m_graph.nodeIndex(41));
	}
	else 
	{
		std::vector<Node*> path;
		m_graph.aStar(m_graph.nodeIndex(0), m_graph.nodeIndex(41), m_visit, path);
	}
}

