#include <CommandManager.h>

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