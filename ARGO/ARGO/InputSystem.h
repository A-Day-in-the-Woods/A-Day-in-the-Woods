#pragma once
#include "InputComponent.h"
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "MovementSystem.h"


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
	
	void update(SDL_Event &event, movementSystem & t_move)
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
					}
					else if (m_currentState == GameState::Minigame)
					{
					}
					break;	
				case SDLK_DOWN:
					t_move.diceRoll(1);
					std::cout << "Down ";
					break;
				case SDLK_RETURN:
					std::cout << "Enter ";
					break;
				case SDLK_LEFT:
					if (m_currentState == GameState::Gameplay)
					{
						t_move.leftOrRightChoice(0, 0);
					}
					std::cout << "Left ";
					break;
				case SDLK_RIGHT:
					if (m_currentState == GameState::Gameplay)
					{
						t_move.leftOrRightChoice(1, 0);
					}
					std::cout << "Right ";
					break;
				case SDLK_SPACE:
					std::cout << "space ";
					if (m_currentState == GameState::Gameplay)
					{
						t_move.diceRoll(0);
						//SDL_Delay(500);
					}
					break;
				case SDLK_z:
					if (m_currentState == GameState::Minigame)
					{
						//t_player.AButtonPressed(true);
					}					
					break;
				case SDLK_c:
					if (m_currentState == GameState::Minigame)
					{
						//t_player.BButtonPressed(true);
					}
					break;
				case SDLK_b:
					if (m_currentState == GameState::Minigame)
					{
						//t_player.XButtonPressed(true);
					}
					break;
				case SDLK_m:
					if (m_currentState == GameState::Minigame)
					{
						//t_player.YButtonPressed(true);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	

	void update(SDL_Event& event)
	{
		
	}


private:
	GameState & m_currentState;

	//Game& game;
	std::vector<Entity*> m_entities;
	std::vector<InputComponent*> m_inputComp;
};