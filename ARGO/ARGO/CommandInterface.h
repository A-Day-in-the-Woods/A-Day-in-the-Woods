/// <summary>
/// @author: Jack Fennell
/// @date 06/02/2020
/// </summary>

#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H



//Template that each command will take
class Command
{
public:
	virtual ~Command() {};
	virtual void execute() = 0;
protected:
	Command() {};

};

#endif // !COMMANDINTERFACE_H