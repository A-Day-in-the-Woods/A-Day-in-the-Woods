#include "Player.h"

Player::Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int>& t_g):
	m_map(t_map),
	m_graph(t_g),
	Entity(1)
{
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

	CurrentGameBoardIndex = 0;
	m_movementSpeed = -1;
	m_takeingTurn = false;
	choiceLoop = true;
}

void Player::update()
{
	if (m_takeingTurn)
	{
		nodeNavigation();
	}
	else
	{
		setPosition(m_map[CurrentGameBoardIndex].getPosition().x - (rect.w / 4.0f), m_map[CurrentGameBoardIndex].getPosition().y - (rect.h / 4.0f));
	}
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

void Player::nodeNavigation()
{
	if (m_diceRoll > 0)
	{

		std::list<GraphArc<std::pair<std::string, int>, int>> p;

		p = m_graph.nodeIndex(CurrentGameBoardIndex)->arcList();

		SDL_Event(event);
		SDL_PollEvent(&event);


		if (p.size() > 1)
		{ // direction choice

			if (!choiceLoop)
			{

				if (!LeftOrRight)
				{
					//----------------------------Point 1 ------------------------------------------
					if (p.front().node()->m_x == m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y > m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	// p1 Down
						playerNodeChange(p);
					}

					if (p.front().node()->m_x == m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y < m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	// p1 Up
						playerNodeChange(p);
					}

					if (p.front().node()->m_x > m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y == m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	//p1 Right
						playerNodeChange(p);
					}

					if (p.front().node()->m_x < m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y == m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	//p1 Left
						playerNodeChange(p);
					}

				}
				else
				{
					p.reverse();

					//----------------------------Point 2 ------------------------------------------
					if (p.front().node()->m_x == m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y > m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	// p2 Down
						playerNodeChange(p);

					}

					if (p.front().node()->m_x == m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y < m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	// p2 Up
						playerNodeChange(p);
					}

					if (p.front().node()->m_x > m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y == m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	//p2 Right
						playerNodeChange(p);
					}

					if (p.front().node()->m_x < m_graph.nodeIndex(CurrentGameBoardIndex)->m_x &&
						p.front().node()->m_y == m_graph.nodeIndex(CurrentGameBoardIndex)->m_y)
					{	//p2 Left
						playerNodeChange(p);
					}
				}
			}
		}
		else
		{ // only one way to go
			playerNodeChange(p);
		}
	}
	else
	{
		m_takeingTurn = false;
	}
}

void Player::playerNodeChange(std::list<GraphArc<std::pair<std::string, int>, int>>& newPoint)
{
	for (int i = 0; i < m_map.size(); i++)
	{
		if (newPoint.front().node()->m_x == m_graph.nodeIndex(i)->m_x &&
			newPoint.front().node()->m_y == m_graph.nodeIndex(i)->m_y)
		{
			// this is then the next tile index to go to
			
			if (animateMovingToPoint(m_map[i].getPosition().x - (rect.w / 4.0f), m_map[i].getPosition().y - (rect.h / 4.0f)))
			{
				CurrentGameBoardIndex = i;
				m_diceRoll--;
				choiceLoop = true;
			}
		}
	}
}

void Player::rollForMove(int t_diceRoll)
{
	if (!m_takeingTurn)
	{
		m_diceRoll = t_diceRoll;
		m_takeingTurn = true;
	}
}

bool Player::animateMovingToPoint(float t_DestX, float t_DestY)
{
	float tempX = rect.x - t_DestX;
	float tempY = rect.y - t_DestY;

	if (rect.x == t_DestX && rect.y == t_DestY)
		return true;

	normalize(tempX, tempY);

	rect.x += (tempX * m_movementSpeed);
	rect.y += (tempY * m_movementSpeed);
	
	return false;
}

void Player::normalize(float & t_x, float & t_y) {

	float len = length(t_x, t_y);

	t_x /= len;
	t_y /= len;
};

float Player::length(float t_x, float t_y) {
	return sqrt(t_x * t_x + t_y * t_y);
}


//false left, true right
void Player::leftOrRightChoice(bool t_choice)
{
	LeftOrRight = t_choice;
	choiceLoop = false;
};