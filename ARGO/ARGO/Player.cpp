#include "Player.h"

Player::Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int>& t_g):
	m_map(t_map),
	m_graph(t_g),
	Entity(1)
{
	SetUp();
	CurrentGameBoardIndex = 0;
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
	setPosition(m_map[CurrentGameBoardIndex].getPosition().x - (rect.w / 4.0f), m_map[CurrentGameBoardIndex].getPosition().y - (rect.h / 4.0f));
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

SDL_Rect Player::getPosition()
{
	return rect;
}

void Player::nodeNavigation(int t_diceRoll)
{
	int temp = t_diceRoll;
	
	for (int x = 0; x < t_diceRoll; x++)
	{

		std::list<GraphArc<std::pair<std::string, int>, int>> p;

		p = m_graph.nodeIndex(CurrentGameBoardIndex)->arcList();

		if (p.size() > 1)
		{ // direction choice
			bool ChoicMade = false;
			bool choice = false;

			while (!ChoicMade)
			{
				SDL_Event(event);
				SDL_PollEvent(&event);
				
				if (SDLK_a == event.key.keysym.sym)
				{
					choice = false;
					ChoicMade = !ChoicMade;
				}
				if (SDLK_s == event.key.keysym.sym)
				{
					choice = true;
					ChoicMade = !ChoicMade;
				}
			}

			if (!choice)
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
		else
		{ // only one way to go
			playerNodeChange(p);
		}
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
			CurrentGameBoardIndex = i;
			//setPosition(m_map[CurrentGameBoardIndex].getPosition().x - (rect.w / 4.0f), m_map[CurrentGameBoardIndex].getPosition().y - (rect.h / 4.0f));
		}

	}
}

void Player::rollForMove()
{
	m_DiceNumber = randomNumber(6, 1);
	std::cout << "DICE rolled a " << m_DiceNumber << std::endl;
	nodeNavigation(m_DiceNumber);
}

void Player::AButtonPressed(bool t_state)
{
	m_Abutton = t_state;
}

void Player::BButtonPressed(bool t_state)
{
	m_Bbutton = t_state;
}

void Player::XButtonPressed(bool t_state)
{
	m_Xbutton = t_state;
}

void Player::YButtonPressed(bool t_state)
{
	m_Ybutton = t_state;
}

bool Player::isAButtonPressed()
{
	return m_Abutton;
}

bool Player::isBButtonPressed()
{
	return m_Bbutton;
}

bool Player::isXButtonPressed()
{
	return m_Xbutton;
}

bool Player::isYButtonPressed()
{
	return m_Ybutton;
}

int Player::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}
