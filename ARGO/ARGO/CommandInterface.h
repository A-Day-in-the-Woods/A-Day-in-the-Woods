/// <summary>
/// @author: Jack Fennell
/// @date 06/02/2020
/// </summary>

#pragma once

//Template that each command will take
class Command
{
public:
	virtual ~Command() {};
	virtual void execute() = 0;
protected:
	Command() {};

};
