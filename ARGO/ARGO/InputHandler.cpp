#include <InputHandler.h>

void InputHandler::inputHandle(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
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
		case SDLK_a:
			m_manager.addCmd(buttonA);
			break;
		default:
			break;
		}
	}
}

