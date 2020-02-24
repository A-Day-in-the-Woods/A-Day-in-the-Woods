#pragma once

#include "MovementComponent.h"
#include <vector>
#include "Entity.h"
#include "GameStates.h"


class MovementSystem
{
public:
	MovementSystem(GameState& t_currentState, std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g ) :
		m_gameState(t_currentState),
		m_map(t_map),
		m_graph(t_g)
	{
	}


	void addEntity(Entity* t_e, SDL_Rect & t_rect)
	{
		std::vector<Component*> InputCheck = t_e->getComponents();

		for (int i = 0; i < InputCheck.size(); i++)
		{
			if (InputCheck[i]->getType() == ComponentType::MOVEMENT)
			{
				m_entities.push_back(t_e);
				m_moveComp.push_back(static_cast<MovementComponent*>(InputCheck[i]));
				m_moveComp.back()->setRect(t_rect);
			}
		}
	}

	/// <summary>
	/// Input Rolled num and the index of the moveing
	/// </summary>
	/// <param name="t_diceRoll"></param>
	/// <param name="index"></param>
	/// 
	//void diceRoll(int t_index, int t_rolledNumber)
	//{
	//	if (!m_moveComp[t_index]->getTakeingTurn())
	//	{
	//		m_DiceNumber = t_rolledNumber;
	//		m_moveComp[t_index]->rollForMove();
	//	}
	//}

	/*
	bool getFinishedTurn(int t_index)
	{
		return m_moveComp[t_index]->getFinishedTurn();
	}

	void resetFinishedTurn()
	{
		for (int i = 0; i < m_moveComp.size(); i++)
		{
			m_moveComp[i]->setFinishedTurn(0);
		}
	}
	*/


	bool IsThePlayerMoving(int t_i)
	{
		return m_moveComp[t_i]->getTakeingTurn();
	}

	void leftOrRightChoice(bool t_b, int index)
	{
		m_moveComp[index]->leftOrRightChoice(t_b);
	}


	void updateAll() {
		for (int i = 0; i < m_moveComp.size(); i++)
		{
			m_moveComp[i]->update(m_map, m_graph);
		}
	}

	void update(int t_index) {
		m_moveComp[t_index]->update(m_map, m_graph);
	}

	


private:

	GameState & m_gameState;

	std::vector<Entity*> m_entities;
	std::vector<MovementComponent*> m_moveComp;

	Graph< pair<string, int>, int>& m_graph;
	std::vector<Tile>& m_map;
};