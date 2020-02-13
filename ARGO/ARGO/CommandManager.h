/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#ifndef COMMANDMANGER_H
#define COMMANDMANGER_H

#include <stack>

#include <ConcreteCommands.h>

class CommandManager
{
public: 
	virtual void addCmd(Command* t_input);
	virtual void execute();

private: 
	std::stack<Command*> m_commands;
	
};


#endif // !COMMANDMANGER_H