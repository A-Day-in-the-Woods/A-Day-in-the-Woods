#include "Gameplay.h"

Gameplay::Gameplay(Game& game) :
	m_game(game)
{
}

Gameplay::~Gameplay()
{
}

void Gameplay::update()
{
	std::cout << "Gameplay update" << std::endl;
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		m_game.newGameState(GameState::Credit);
	}
}

void Gameplay::render()
{
	std::cout << "Gameplay render" << std::endl;
}
