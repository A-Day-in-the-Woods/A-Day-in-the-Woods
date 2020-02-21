#include <CommandManager.h>


CommandManager::CommandManager()
{}

void CommandManager::addCmd(Command* t_input, Entity* t_entity)
{
	m_entity = t_entity;
	//push onto stack then execute
	m_commands.push(t_input);
	execute();
}


void CommandManager::execute()
{
	m_commands.top()->execute(*m_entity);
}