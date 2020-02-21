#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H



#include"Entity.h"
#include <vector>
#include <iostream>
#include "HealthComp.h"


class HealthSystem
{
public:
	void addEntity(Entity* t_e) {
		std::vector<Component*> healthCheck = t_e->getComponents();

		for (int i = 0; i < healthCheck.size(); i++)
		{
			if (healthCheck[i]->getType() == ComponentType::HEALTH)
			{
				m_entities.push_back(t_e);
				m_healthComp.push_back(static_cast<HealthComponent*>(healthCheck[i]));
			}
		}


		for (int i = 0; i < m_entities.size(); i++)
		{
			switch (m_entities[i]->getId())
			{
			case 0:
				m_healthComp[i]->setHealth(200);	//player
				break;
			case 1:
				m_healthComp[i]->setHealth(100);	//alien
				break;
			case 2:
				m_healthComp[i]->setHealth(50);		//dog
				break;
			case 3:
				m_healthComp[i]->setHealth(50);		//cat
				break;
			default:
				std::cout << "Error - addEntity - HealthSystem" << std::endl;
				break;
			}
		}
	}

	void removeEntityFromSystem(int t_entityID){
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i]->getId() == t_entityID)
			{
				m_entities[i]->removeComponent(ComponentType::HEALTH);

				m_entities.erase(m_entities.begin() + i);
				m_healthComp.erase(m_healthComp.begin() + i);
			}
		}
	}

	void update() {
		for (int i = 0; i < m_entities.size(); i++)
		{
			//std::cout << "ID : " << m_entities[i]->getId() << "  Health : " << m_healthComp[i]->getHealth() << std::endl;
			
		}
	}

private:
	std::vector<Entity*> m_entities;
	std::vector<HealthComponent*> m_healthComp;
};
#endif // !HEALTHSYSTEM_H