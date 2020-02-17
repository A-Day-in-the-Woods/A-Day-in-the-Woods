#include <InputHandler.h>



InputHandler::InputHandler()
{
	m_controller = new Controller(0);
}

void InputHandler::inputHandle(SDL_Event& event)
{
	/*if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			m_manager.addCmd(buttonUp);
			break;
		case SDLK_DOWN:
			m_manager.addCmd(buttonDown);
			break;
		case SDLK_RETURN:
			m_manager.addCmd(buttonEnter);
			break;
		case SDLK_SPACE:
			m_manager.addCmd(buttonSpace);
			break;
		case SDLK_LEFT:
			m_manager.addCmd(buttonLeft);
			break;
		case SDLK_RIGHT:
			m_manager.addCmd(buttonRight);
			break;
		default:
			break;
		}
	}
*/
	m_controller->update();
	
	if(event.type == SDL_CONTROLLERBUTTONDOWN)
	{
	
		switch (event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			m_manager.addCmd(buttonA);
			break;
		case SDL_CONTROLLER_BUTTON_B:
			m_manager.addCmd(buttonB);
			break;
		case SDL_CONTROLLER_BUTTON_X:
			m_manager.addCmd(buttonX);
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			m_manager.addCmd(buttonY);
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			m_manager.addCmd(buttonBack);
			break;
		case SDL_CONTROLLER_BUTTON_START:
			m_manager.addCmd(buttonStart);
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			m_manager.addCmd(leftShoulder);
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			m_manager.addCmd(rightShoulder);
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSTICK:
			m_manager.addCmd(leftStick);
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
			m_manager.addCmd(rightStick);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			m_manager.addCmd(DpadRight);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			m_manager.addCmd(DpadLeft);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			m_manager.addCmd(DpadUp);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			m_manager.addCmd(DpadDown);
			break;
		default:
			break;
		}
	}
	
}

