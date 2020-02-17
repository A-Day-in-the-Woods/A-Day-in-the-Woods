#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "InputComponent.h"


class InputSystem {
public:
	InputSystem(GameState & t_currentState) :
		m_currentState(t_currentState)
	{}

	void addEntity(Entity* t_e)
	{
		m_entities.push_back(t_e);
		std::vector<Component*> InputCheck = t_e->getComponents();

		for (int i = 0; i < InputCheck.size(); i++)
		{
			if (InputCheck[i]->getType() == ComponentType::INPUT)
			{
				m_inputComp.push_back(static_cast<InputComponent*>(InputCheck[i]));
				m_inputComp[0]->m_input;
			}
		}
	}
	
	void update(SDL_Event &event, Player & t_player)
	{
		
		m_inputComp[0]->m_input.inputHandle(event);
		
	}
	
private:
	GameState & m_currentState;

	//Game& game;
	std::vector<Entity*> m_entities;
	std::vector<InputComponent*> m_inputComp;
};

#endif // !INPUTSYSTEM_H
