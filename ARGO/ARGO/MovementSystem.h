#pragma once

#include "MovementComponent.h"
#include <vector>
#include "Entity.h"
#include "GameStates.h"


class movementSystem
{
public:
	movementSystem(GameState& t_currentState, std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g ) :
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
	void diceRoll(int index)
	{
		m_DiceNumber = randomNumber(6, 1);
		m_moveComp[index]->rollForMove(m_DiceNumber);
	}

	void leftOrRightChoice(bool t_b, int index)
	{
		m_moveComp[index]->leftOrRightChoice(t_b);
	}

	void update() {
		for (int i = 0; i < m_moveComp.size(); i++)
		{
			m_moveComp[i]->update(m_map, m_graph);
		}
	}


	int randomNumber(int t_max, int t_min)
	{
		std::random_device device;
		std::mt19937 rng(device());
		std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
		return dist(rng);
	}

	int getDiceRoll()
	{
		return m_DiceNumber;
	}

private:

	GameState & m_gameState;

	std::vector<Entity*> m_entities;
	std::vector<MovementComponent*> m_moveComp;

	Graph< pair<string, int>, int>& m_graph;
	std::vector<Tile>& m_map;
	int m_DiceNumber{ 1 };
};