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
	virtual void execute() { std::cout << "Up Dpad " << std::endl; }
};

class DownOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Down Dpad " << std::endl; }
};



class LeftOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left Dpad " << std::endl; }
};

class RightOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right Dpad " << std::endl; }
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
	virtual void execute() { std::cout << "A Controller " << std::endl; }
};

class BOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "B Controller " << std::endl; }
};

class XOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "X Controller " << std::endl; }
};

class YOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Y Controller " << std::endl; }
};

class BackOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Back Button Controller " << std::endl; }
};

class StartOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Start Button Controller " << std::endl; }
};

class LeftShoulderOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left Shoulder Controller " << std::endl; }
};

class RightShoulderOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right Shoulder Controller " << std::endl; }
};

class LeftStickOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left Stick Controller " << std::endl; }
};

class RightStickOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right Stick Controller " << std::endl; }
};
#endif // !CONCRETECOMMANDS_H