#include "MenuScreen.h"

MenuScreen::MenuScreen(Game& game) :
	m_game( game )
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::update()
{
	std::cout << "Menu update" << std::endl;
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		m_game.newGameState(GameState::Options);
	}
}

void MenuScreen::render()
{
	std::cout << "Menu render" << std::endl;
}
