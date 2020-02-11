/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#pragma once


#include"CommandManager.h"



#include <stack>
#include <SDL.h>

class InputHandler
{
public: 
	void inputHandle(SDL_Event &event);

private:
	//Handles the action of the inputs
	CommandManager m_manager;

	//Each Button used
	Command* buttonUp = new UpOutput();
	Command* buttonDown = new DownOutput();
	Command* buttonEnter = new EnterOutput();
	Command* buttonSpace = new SpaceOutput();
	Command* buttonLeft = new LeftOutput();
	Command* buttonRight = new RightOutput();

	
};

void InputHandler::inputHandle(SDL_Event &event)
{
	//SDL_Event event;
	//SDL_PollEvent(&event);

	
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (SDLK_UP == event.key.keysym.sym)
		{
			m_manager.addCmd(buttonUp);
		}
		if (SDLK_DOWN == event.key.keysym.sym)
		{
			m_manager.addCmd(buttonDown);
		}
		if (SDLK_RETURN == event.key.keysym.sym)
		{
			m_manager.addCmd(buttonEnter);
		}
		if (SDLK_SPACE == event.key.keysym.sym)
		{
			m_manager.addCmd(buttonSpace);
		}
		if (SDLK_LEFT == event.key.keysym.sym)
		{
			m_manager.addCmd(buttonLeft);
		}
		if (SDLK_RIGHT == event.key.keysym.sym)
		{
			m_manager.addCmd(buttonRight);
		}
		break;
	default:
		break;
	}
	
}
