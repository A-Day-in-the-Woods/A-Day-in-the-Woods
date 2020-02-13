#include "Controller.h"

/// <summary>
/// @author Jack
/// @date 12/02/2020
/// </summary>

int Controller::s_noOfControllers = 0;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::update()
{
	m_previousState = m_currentState;

	//if (isConnected())
	{
		//Controller Buttons
		m_currentState.A = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
		m_currentState.B = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
		m_currentState.X = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
		m_currentState.Y = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
		m_currentState.Back = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
		m_currentState.Start = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
		m_currentState.LB = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		m_currentState.RB = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

		//Thumbstick clicks
		m_currentState.LeftThumbStickClick = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
		m_currentState.RightThumbStickClick = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);


		//D-pad Right
		m_currentState.DpadRight = (SDL_CONTROLLER_BUTTON_DPAD_RIGHT > DPAD_THRESHOLD) ? true : false;
		//D-pad Left
		m_currentState.DpadLeft = (SDL_CONTROLLER_BUTTON_DPAD_LEFT < -DPAD_THRESHOLD) ? true : false;
		//D-pad Up
		m_currentState.DpadUp = (SDL_CONTROLLER_BUTTON_DPAD_UP > DPAD_THRESHOLD) ? true : false;
		//D-pad Down
		m_currentState.DpadDown = (SDL_CONTROLLER_BUTTON_DPAD_DOWN < -DPAD_THRESHOLD) ? true : false;
		//Triggers
		m_currentState.LTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		m_currentState.RTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		//Left Thumbstick
		m_currentState.LeftThumbStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		m_currentState.LeftThumbStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		//Right Thumbstick
		m_currentState.RightThumbStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
		m_currentState.RightThumbStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
	}

}

bool Controller::isConnected()
{
	if (joystick_index<0 || joystick_index > SDL_NumJoysticks())
		return false;
	else
		return SDL_IsGameController(joystick_index);
}

bool Controller::connect()
{

	for (int index = s_noOfControllers; index < SDL_NumJoysticks(); index++)
	{
		if (SDL_IsGameController(index))
		{
			joystick_index = index;
			s_noOfControllers++;
#ifdef _DEBUG
			controller = SDL_GameControllerOpen(index);
#endif // _DEBUG
			return true;
		}
	}
	return false;
}