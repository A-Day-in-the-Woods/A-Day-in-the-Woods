#ifndef ENTITY_H

#define ENTITY_H


#include <vector>
#include "Component.h"

class Entity
{
public:
	Entity(int t_idNum) : m_id(t_idNum) {};
	void addComponent(Component* t_c) { m_components.push_back(t_c); }
	void removeComponent(ComponentType t_c) { 
		for (int i = 0; i < m_components.size(); i++)
		{
			if (t_c == m_components[i]->getType())
			{
				m_components.erase(m_components.begin() + i);
				break;
			}
		}
	}

	std::vector<Component*> getComponents() { return m_components; }
	int getId() { return m_id; }

	Entity * getEntity(){
		return this;
	}

private:
	std::vector<Component*> m_components;
	int m_id;
};

#endif // !ENTITY_H