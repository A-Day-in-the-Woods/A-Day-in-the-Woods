/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#ifndef INPUTHANDLER_H



#define INPUTHANDLER_H


#include <CommandManager.h>
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
	Command* buttonA = new AOutput();
	
};


#endif // !INPUTHANDLER_H