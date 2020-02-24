#pragma once

#include "Component.h"
#include <vector>
#include "Tile.h"
#include "iostream"
#include "Graph.h"


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

	//void setTurnIndex(int & t_turnIndex)
	//{
	//	m_turnIndex = &t_turnIndex;
	//}


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

				if (!choiceLoop)
				{

					if (!LeftOrRight)
					{
						//----------------------------Point 1 ------------------------------------------
						if (p.front().node()->m_x == t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y > t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	// p1 Down
							playerNodeChange(p, t_map, t_g);
						}

						if (p.front().node()->m_x == t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y < t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	// p1 Up
							playerNodeChange(p, t_map, t_g);
						}

						if (p.front().node()->m_x > t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y == t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	//p1 Right
							playerNodeChange(p, t_map, t_g);
						}

						if (p.front().node()->m_x < t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y == t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	//p1 Left
							playerNodeChange(p, t_map, t_g);
						}

					}
					else
					{
						p.reverse();

						//----------------------------Point 2 ------------------------------------------
						if (p.front().node()->m_x == t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y > t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	// p2 Down
							playerNodeChange(p, t_map, t_g);

						}

						if (p.front().node()->m_x == t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y < t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	// p2 Up
							playerNodeChange(p, t_map, t_g);
						}

						if (p.front().node()->m_x > t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y == t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	//p2 Right
							playerNodeChange(p, t_map, t_g);
						}

						if (p.front().node()->m_x < t_g.nodeIndex(CurrentGameBoardIndex)->m_x &&
							p.front().node()->m_y == t_g.nodeIndex(CurrentGameBoardIndex)->m_y)
						{	//p2 Left
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
			//if (m_takeingTurn)
			//{
			//	m_finishedTurn = true;
			//}

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


	bool getTakeingTurn(){
		return m_takeingTurn;
	}

	/*
	bool getFinishedTurn() {
		return m_finishedTurn;
	}

	void setFinishedTurn(bool t_b)
	{
		m_finishedTurn = t_b;
	}
	*/

private:


	int CurrentGameBoardIndex;


	SDL_Rect * rect;

	bool choiceLoop;
	bool LeftOrRight = false;

	bool m_takeingTurn;
	//bool m_finishedTurn;

	float m_movementSpeed;

	int m_diceRoll;

	//int * m_turnIndex;
};