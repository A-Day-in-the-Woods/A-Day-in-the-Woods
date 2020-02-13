/// <summary>
///	@author Jack Fennell
/// @date 12/02/2020
/// </summary>

#ifndef CONTROLLER
#define CONTROLLER
#include <SDL.h>

struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	float RTrigger;
	float LTrigger;
	float RightThumbStickX;
	float RightThumbStickY;
	float LeftThumbStickX;
	float LeftThumbStickY;

};

class Controller {
private:
	const int DPAD_THRESHOLD = 8000;

public:
	static int s_noOfControllers;

	int joystick_index;

	GamePadState m_currentState;
	GamePadState m_previousState;
	SDL_GameController* controller = NULL;
	Controller();
	~Controller();
	void update();
	bool isConnected();
	bool connect();

};

#endif // !CONTROLLER


