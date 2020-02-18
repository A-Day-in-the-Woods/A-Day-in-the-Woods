#include <InputHandler.h>



InputHandler::InputHandler()
{    
	controlNumber = noOfControl++;
	m_controller = new Controller(controlNumber);

}

void InputHandler::inputHandle(SDL_Event& event)
{

	m_controller->update();

	if(m_controller->m_currentState.A)
	{
		m_manager.addCmd(buttonA);
	}

	if(m_controller->m_currentState.B)
	{
		m_manager.addCmd(buttonB);
	}

	if(m_controller->m_currentState.X)
	{
		m_manager.addCmd(buttonX);
	}

	if(m_controller->m_currentState.Y)
	{
		m_manager.addCmd(buttonY);
	}

	if(m_controller->m_currentState.Back)
	{
		m_manager.addCmd(buttonBack);
	}

	if (m_controller->m_currentState.Start)
	{
		m_manager.addCmd(buttonStart);
	}
	
	if (m_controller->m_currentState.LB)
	{
		m_manager.addCmd(leftShoulder);
	}

	if (m_controller->m_currentState.RB)
	{
		m_manager.addCmd(rightShoulder);
	}

	if (m_controller->m_currentState.LeftThumbStickClick)
	{
		m_manager.addCmd(leftStick);
	}

	if (m_controller->m_currentState.RightThumbStickClick)
	{
		m_manager.addCmd(rightStick);
	}

	if (m_controller->m_currentState.DpadUp)
	{
		m_manager.addCmd(DpadUp);
	}		

	if (m_controller->m_currentState.DpadDown)
	{
		m_manager.addCmd(DpadDown);
	}
		
	if (m_controller->m_currentState.DpadRight)
	{
		m_manager.addCmd(DpadRight);
	}

	if (m_controller->m_currentState.DpadLeft)
	{
		m_manager.addCmd(DpadLeft);
	}
			
}

