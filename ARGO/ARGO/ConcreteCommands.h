/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>

#ifndef CONCRETECOMMANDS_H
#define CONCRETECOMMANDS_H



#include "CommandInterface.h"
#include <iostream>

//Command list for inputs

class UpOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Up Dpad "; }
};

class DownOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Down Dpad "; }
};



class LeftOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left Dpad "; }
};

class RightOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right Dpad "; }
};

//class EnterOutput : public Command
//{
//public:
//	//placeholder for actual function prints out to command window
//	virtual void execute() { std::cout << "Enter "; }
//};
//
//class SpaceOutput : public Command
//{
//public:
//	//placeholder for actual function prints out to command window
//	virtual void execute() { std::cout << "Space "; }
//};

//Controller Commands
class AOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "A Controller "; }
};

class BOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "B Controller "; }
};

class XOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "X Controller "; }
};

class YOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Y Controller "; }
};

class BackOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Back Button Controller "; }
};

class StartOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Start Button Controller "; }
};

class LeftShoulderOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left Shoulder Controller "; }
};

class RightShoulderOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right Shoulder Controller "; }
};

class LeftStickOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left Stick Controller "; }
};

class RightStickOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right Stick Controller "; }
};
#endif // !CONCRETECOMMANDS_H