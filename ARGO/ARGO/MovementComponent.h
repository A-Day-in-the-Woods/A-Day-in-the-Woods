#pragma once

#include "Component.h"
#include <vector>
#include "Tile.h"
#include "iostream"
#include "Graph.h"
#include <random>

class MovementComponent : public Component
{

public:

	MovementComponent() : Component(ComponentType::MOVEMENT)
	{
		setUp();
	}

	/// <summary>
	/// Set the body that will be moved
	/// </summary>
	/// <param name="t_rect"></param>
	void setRect(SDL_Rect & t_rect) {
		rect = &t_rect;
	}
	void setAiCheck(bool &t_IsAi) {
		m_IsAi = &t_IsAi;
	}


	int randomNumber(int t_max, int t_min)
	{
		std::random_device device;
		std::mt19937 rng(device());
		std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
		return dist(rng);
	}

	void setUp(){
		CurrentGameBoardIndex = 0;
		m_movementSpeed = -1;
		m_takeingTurn = false;
		choiceLoop = true;
	}

	void update(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g) {
		if (m_takeingTurn)
		{
			nodeNavigation(t_map, t_g);
		}
		else
		{
			rect->x = t_map[CurrentGameBoardIndex].getPosition().x - (rect->w / 4.0f);
			rect->y	= t_map[CurrentGameBoardIndex].getPosition().y - (rect->h / 4.0f);
		}
	}

	void nodeNavigation(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g) {
		if (m_diceRoll > 0)
		{

			std::list<GraphArc<std::pair<std::string, int>, int>> p;

			p = t_g.nodeIndex(CurrentGameBoardIndex)->arcList();

			SDL_Event(event);
			SDL_PollEvent(&event);


			if (p.size() > 1)
			{ // direction choice
				if (*m_IsAi == true && choiceLoop ==true)
				{
					m_DirectionChoiceNum = randomNumber(6,1);
					choiceLoop = false;
				}
				if (!choiceLoop)
				{
		

					if (m_DirectionChoiceNum == nodeDirectionCheck(
							p.front().node()->m_x,
							p.front().node()->m_y,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_y))
					{
						playerNodeChange(p, t_map, t_g);
					}
					else if (*m_IsAi == true)
					{
						m_DirectionChoiceNum = randomNumber(6, 1);

					}
					else
					{
			
						p.reverse();
						if (m_DirectionChoiceNum == nodeDirectionCheck(
							p.front().node()->m_x,
							p.front().node()->m_y,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_y))
						{
							playerNodeChange(p, t_map, t_g);
						}
					}
				}
			}
			else
			{ // only one way to go
				playerNodeChange(p, t_map, t_g);
			}
		}
		else
		{
			m_takeingTurn = false;			
		}
	}



	void playerNodeChange(std::list<GraphArc<std::pair<std::string, int>, int>>& newPoint, 
							std::vector<Tile>& t_map,
							Graph< pair<string, int>, int>& t_g) {
		for (int i = 0; i < t_map.size(); i++)
		{
			if (newPoint.front().node()->m_x == t_g.nodeIndex(i)->m_x &&
				newPoint.front().node()->m_y == t_g.nodeIndex(i)->m_y)
			{
				// this is then the next tile index to go to

				if (animateMovingToPoint(t_map[i].getPosition().x - (rect->w / 4.0f), t_map[i].getPosition().y - (rect->h / 4.0f)))
				{
					CurrentGameBoardIndex = i;
					m_diceRoll--;
					choiceLoop = true;
					// direction check here;
				}
			}
		}
	}

	void rollForMove(int t_diceRolled) {

		if (!m_takeingTurn)
		{
			m_diceRoll = t_diceRolled;
			m_takeingTurn = true;
			//m_finishedTurn = false;
		}
	}

	bool animateMovingToPoint(float t_DestX, float t_DestY) {
		float tempX = rect->x - t_DestX;
		float tempY = rect->y - t_DestY;

		if (rect->x == t_DestX && rect->y == t_DestY)
			return true;

		normalize(tempX, tempY);

		rect->x += (tempX * m_movementSpeed);
		rect->y += (tempY * m_movementSpeed);

		return false;
	}


	void normalize(float& t_x, float& t_y) {
		float len = sqrt(t_x * t_x + t_y * t_y);

		t_x /= len;
		t_y /= len;
	}

	void leftOrRightChoice(bool t_choice) {
		LeftOrRight = t_choice;
		choiceLoop = false;
	}

	void directionChoice(int t_choice) {
		m_DirectionChoiceNum = t_choice;
		choiceLoop = false;
	}


	bool getTakeingTurn(){
		return m_takeingTurn;
	}


	int nodeDirectionCheck(int x1, int y1, int x2, int y2)
	{
		if (x1 == x2 && y1 > y2)
		{	// p2 Down
			return 1;
		}
		else if (x1 == x2 && y1 < y2)
		{	// p2 Up
			return 6;
		}
		else if (x1 > x2 && y1 == y2)
		{	// p2 Right
			return 4;
		}
		else if (x1 < x2 && y1 == y2)
		{	// p2 Left
			return 5;
		}

		return -1;
	}


private:


	int CurrentGameBoardIndex;


	SDL_Rect * rect;
	bool * m_IsAi;

	bool choiceLoop;
	bool LeftOrRight = false;

	bool m_takeingTurn;

	float m_movementSpeed;

	int m_diceRoll;

	int m_DirectionChoiceNum = -1;
};