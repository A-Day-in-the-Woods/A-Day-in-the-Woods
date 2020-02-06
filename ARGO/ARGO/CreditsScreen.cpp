#include "CreditsScreen.h"

CreditScreen::CreditScreen(Game& game) :
	m_game(game)
{
}

CreditScreen::~CreditScreen()
{
}

void CreditScreen::update()
{
	std::cout << "Credits update" << std::endl;
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		m_game.newGameState(GameState::Menu);
	}
}

void CreditScreen::render()
{
	std::cout << "Credits render" << std::endl;
}
