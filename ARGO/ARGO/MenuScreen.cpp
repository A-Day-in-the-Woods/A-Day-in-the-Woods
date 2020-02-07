#include "MenuScreen.h"

MenuScreen::MenuScreen(Game& game, SDL_Renderer* t_renderer) :
	m_game( game ),
	m_renderer(t_renderer)
{

	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::update()
{
	std::cout << "Menu update" << std::endl;
}

void MenuScreen::render()
{
	std::cout << "Menu render" << std::endl;
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

	SDL_RenderPresent(m_renderer);
}

void MenuScreen::setGameState()
{
	m_game.setGameState(GameState::Options);
}
