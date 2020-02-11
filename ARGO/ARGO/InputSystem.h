#pragma once
#include "InputComponent.h"
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Entity.h"


class InputSystem {
public:
	void addEntity(Entity* t_e)
	{
		m_entities.push_back(t_e);
		std::vector<Component*> InputCheck = t_e->getComponents();

		for (int i = 0; i < InputCheck.size(); i++)
		{
			if (InputCheck[i]->getType() == ComponentType::POSITION)
			{
				m_inputComp.push_back(static_cast<InputComponent*>(InputCheck[i]));
			}
		}
	}

	void update(SDL_Event &event)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					std::cout << "Up ";
					break;	
				case SDLK_DOWN:
					std::cout << "Down ";
					break;
				case SDLK_RETURN:
					std::cout << "Enter ";
					break;
				case SDLK_SPACE:
					std::cout << "Space ";
					break;
				case SDLK_LEFT:
					std::cout << "Left ";
					break;
				case SDLK_RIGHT:
					std::cout << "Right ";
					break;
				default:
					break;
				}
			}
		}
	}

private:
	std::vector<Entity*> m_entities;
	std::vector<InputComponent*> m_inputComp;
};