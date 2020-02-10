#include "Player.h"

Player::Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int>& t_g):
	m_map(t_map),
	m_graph(t_g)
{
	dice = 2;
	SetUp();
}

Player::~Player()
{
}

void Player::SetUp()
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 20;
	rect.h = 20;
}

void Player::update()
{
	movePlayerOnBoard();
}

void Player::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 155, 255, 255);
	SDL_RenderFillRect(t_renderer, &rect);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void Player::setPosition(float t_x, float t_y)
{
	rect.x = t_x;
	rect.y = t_y;
}

void Player::getPosition()
{
}

void Player::movePlayerOnBoard()
{

	CurrentGameBoardIndex = 27;

	for (int i = 0; i < dice; i++)
	{

	}

	auto d = m_graph.getArc(0, 1);

	auto c = m_graph.nodeIndex(27)->arcList().begin();

	std::list<GraphArc<std::pair<std::string, int>, int>> p;

	p = m_graph.nodeIndex(CurrentGameBoardIndex)->arcList();

	//m_tempGraph = m_graph.nodeIndex(CurrentGameBoardIndex)->arcList();

	//auto f = m_graph.nodeIndex(30)->getArc(m_graph.nodeIndex(31));

	if (p.size() > 1)
	{ // direction choice
	}
	else
	{ // only one way to go

		for (int i = 0; i < m_map.size(); i++)
		{
			if (p.front().node()->m_x == m_graph.nodeIndex(i)->m_x && 
				p.front().node()->m_y == m_graph.nodeIndex(i)->m_y)
			{
				CurrentGameBoardIndex = i;

			}
		}
	}

	//setPosition(m_map[CurrentGameBoardIndex].getPosition().x - (rect.w / 4.0f), m_map[CurrentGameBoardIndex].getPosition().y - (rect.h / 4.0f));
	//CurrentGameBoardIndex++;

	//m_map[0].getPosition
}
