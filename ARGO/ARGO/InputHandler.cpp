#include <InputHandler.h>
InputHandler::InputHandler()
{    
	m_manager = new CommandManager();
	controlNumber = noOfControl++;
	
	m_controller = new Controller(controlNumber);
	
}

void InputHandler::inputHandle(SDL_Event& event, GameState& t_currentState, Player* t_entity)
{
	if (controlNumber == t_entity->getId())
	{
		m_controller->update();

		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (m_controller->m_currentState.A)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					t_entity->setLastButton(1);
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				case GameState::Options:
					break;
				case GameState::Gameplay:	
					t_entity->setLastButton(1);
					m_manager->addCmd(diceRoll, t_entity ,t_entity->randomNumber(6, 1));
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					t_entity->setLastButton(1);
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				default:
					break;
				}

			}

			if (m_controller->m_currentState.B)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					break;
				case GameState::Options:
					t_entity->setLastButton(4);
					m_manager->addCmd(buttonB, t_entity, NULL);
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					t_entity->setLastButton(4);
					m_manager->addCmd(buttonB, t_entity, NULL);
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}

				
			}

			if (m_controller->m_currentState.X)
			{
				m_manager->addCmd(buttonX, t_entity, NULL);
			}

			if (m_controller->m_currentState.Y)
			{
				m_manager->addCmd(buttonY, t_entity, NULL);
			}

			if (m_controller->m_currentState.Back)
			{
				m_manager->addCmd(buttonBack, t_entity, NULL);
			}

			if (m_controller->m_currentState.Start)
			{
				m_manager->addCmd(buttonStart, t_entity, NULL);
			}

			if (m_controller->m_currentState.LB)
			{
				m_manager->addCmd(leftShoulder, t_entity, NULL);
			}

			if (m_controller->m_currentState.RB)
			{
				m_manager->addCmd(rightShoulder, t_entity, NULL);
			}

			if (m_controller->m_currentState.LeftThumbStickClick)
			{
				m_manager->addCmd(leftStick, t_entity, NULL);
			}

			if (m_controller->m_currentState.RightThumbStickClick)
			{
				m_manager->addCmd(rightStick, t_entity, NULL);
			}

			if (m_controller->m_currentState.DpadUp)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					t_entity->setLastButton(2);
					m_manager->addCmd(DpadUp, t_entity, NULL);
					break;
				case GameState::Options:
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
			}

			if (m_controller->m_currentState.DpadDown)
			{
				
				switch (t_currentState)
				{
				case GameState::Menu:
					t_entity->setLastButton(3);
					m_manager->addCmd(DpadDown, t_entity, NULL);
					break;
				case GameState::Options:
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
				
			}

			if (m_controller->m_currentState.DpadRight)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					break;
				case GameState::Options:
					break;
				case GameState::Gameplay:
					m_manager->addCmd(moveRight, t_entity, NULL);
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
				
			}

			if (m_controller->m_currentState.DpadLeft)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					break;
				case GameState::Options:
					break;
				case GameState::Gameplay:
					m_manager->addCmd(moveLeft, t_entity, NULL);
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
			}
		}
	}
}

