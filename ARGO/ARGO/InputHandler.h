/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#ifndef INPUTHANDLER_H



#define INPUTHANDLER_H

#include "GameStates.h"
#include <CommandManager.h>
#include <Controller.h>
#include <vector>
#include <stack>
#include <SDL.h>



static int noOfControl;

class InputHandler
{
public: 
	InputHandler();
	void inputHandle(SDL_Event &event, GameState& t_currentState);
	
private:
	//Handles the action of the inputs
	CommandManager m_manager;
	Controller* m_controller;
	
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
	int controlNumber;
	
};


#endif // !INPUTHANDLER_H