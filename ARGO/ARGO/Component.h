#pragma once

#include <SDL.h>

enum class ComponentType {
	HEALTH,
	POSITION,
	INPUT
};

class Component {

public:

	Component(ComponentType t_type) : m_compType(t_type) {};

	ComponentType getType() { return m_compType; }
	void setType(ComponentType t_type) { m_compType = t_type; }

private:
	ComponentType m_compType;
};