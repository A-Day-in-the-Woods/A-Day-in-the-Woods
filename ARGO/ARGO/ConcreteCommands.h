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
	virtual void execute() { std::cout << "Up "; }
};

class DownOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Down "; }
};

class EnterOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Enter "; }
};

class SpaceOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Space "; }
};

class LeftOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Left "; }
};

class RightOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "Right "; }
};

class AOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute() { std::cout << "A "; }
};

#endif // !CONCRETECOMMANDS_H