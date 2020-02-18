#pragma once
#include "InputComponent.h"
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"
#include "Entity.h"
#include "Player.h"


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
			if (InputCheck[i]->getType() == ComponentType::POSITION)
			{
				m_inputComp.push_back(static_cast<InputComponent*>(InputCheck[i]));
			}
		}
	}
	
	void update(SDL_Event &event, Player & t_player)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					std::cout << "up ";
					break;
				case SDLK_DOWN:
					std::cout << "Down ";
					break;
				case SDLK_RETURN:
					std::cout << "Enter ";
					break;
				case SDLK_LEFT:
					std::cout << "Left ";
					break;
				case SDLK_RIGHT:
					std::cout << "Right ";
					break;
				case SDLK_SPACE:
					std::cout << "space ";
					if (m_currentState == GameState::Gameplay)
					{
						t_player.rollForMove();
						SDL_Delay(500);
					}
					break;
				case SDLK_z:
					if (m_currentState == GameState::Minigame)
					{
						t_player.AButtonPressed(true);
					}					
					break;
				case SDLK_c:
					if (m_currentState == GameState::Minigame)
					{
						t_player.BButtonPressed(true);
					}
					break;
				case SDLK_b:
					if (m_currentState == GameState::Minigame)
					{
						t_player.XButtonPressed(true);
					}
					break;
				case SDLK_m:
					if (m_currentState == GameState::Minigame)
					{
						t_player.YButtonPressed(true);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	
private:
	GameState & m_currentState;

	//Game& game;
	std::vector<Entity*> m_entities;
	std::vector<InputComponent*> m_inputComp;
};