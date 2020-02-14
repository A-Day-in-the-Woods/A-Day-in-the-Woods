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
					if (m_currentState == GameState::Gameplay)
					{
						t_player.rollForMove(3);
						//SDL_Delay(500);
						std::cout << "Up ";
					}
					else if (m_currentState == GameState::Minigame)
					{
						std::cout << "l";
						//input?
					}
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
					if (m_currentState == GameState::Gameplay)
					{
						t_player.leftOrRightChoice(0);
					}
					std::cout << "Left ";
					break;
				case SDLK_RIGHT:
					if (m_currentState == GameState::Gameplay)
					{
						t_player.leftOrRightChoice(1);
					}
					std::cout << "Right ";
					break;
				case SDLK_a:
					switch (m_currentState)
					{
					case GameState::Minigame:
						
						break;
					default:
						break;
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