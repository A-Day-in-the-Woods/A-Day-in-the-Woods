#include "Options.h"

Option::Option(Game& game) :
	m_game(game)
{
}

Option::~Option()
{
}

void Option::update()
{
	std::cout << "Options update" << std::endl;
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		m_game.newGameState(GameState::Gameplay);
	}
}

void Option::render()
{
	std::cout << "Options render" << std::endl;
}
