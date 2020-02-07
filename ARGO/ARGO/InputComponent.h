#pragma once

/// <summary>
/// @author Jack Fennell
/// @date 07/02/2020
/// </summary>
#include "Game.h"
#include "Component.h"

class InputComponent : public Component
{
public:
	InputComponent(): Component(ComponentType::INPUT){}
	
	
};
