/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#pragma once

#include "ConcreteCommands.h"
#include <stack>

class CommandManager
{
public: 
	virtual void addCmd(Command* t_input);
	virtual void execute();

private: 
	std::stack<Command*> m_commands;
	
};


void CommandManager::addCmd(Command* t_input)
{
	//push onto stack then execute
	m_commands.push(t_input);
	execute();
}


void CommandManager::execute()
{
	m_commands.top()->execute();
}
