/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#ifndef INPUTHANDLER_H



#define INPUTHANDLER_H


#include <CommandManager.h>
#include <Controller.h>
#include <stack>
#include <SDL.h>


class InputHandler
{
public: 
	InputHandler();
	void inputHandle(SDL_Event &event);

private:
	//Handles the action of the inputs
	CommandManager m_manager;
	Controller* m_controller;

	//Each Button used
	/*Command* buttonUp = new UpOutput();
	Command* buttonDown = new DownOutput();
	Command* buttonEnter = new EnterOutput();
	Command* buttonSpace = new SpaceOutput();
	Command* buttonLeft = new LeftOutput();
	Command* buttonRight = new RightOutput();*/
	
	//Controller buttons
	Command* buttonA = new AOutput();
	Command* buttonB = new BOutput();
	Command* buttonX = new XOutput();
	Command* buttonY = new YOutput();
	Command* buttonBack = new BackOutput();
	Command* buttonStart = new StartOutput();
	Command* leftShoulder = new LeftShoulderOutput();
	Command* rightShoulder = new RightShoulderOutput();
	Command* leftStick = new LeftStickOutput();
	Command* rightStick = new RightStickOutput();

	//Controller dpad
	Command* DpadUp = new UpOutput();
	Command* DpadDown = new DownOutput();
	Command* DpadRight = new RightOutput();
	Command* DpadLeft = new LeftOutput();
};


#endif // !INPUTHANDLER_H