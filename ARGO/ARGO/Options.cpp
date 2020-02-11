#include "Options.h"

OptionScreen::OptionScreen(Game& game, SDL_Renderer* t_renderer) :
	m_game(game),
	m_renderer(t_renderer)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic1.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);
}

OptionScreen::~OptionScreen()
{
}

void OptionScreen::update()
{
	
}

void OptionScreen::render()
{
	
	//SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

	//SDL_RenderPresent(m_renderer);
}

void OptionScreen::setGameState()
{
	m_game.setGameState(GameState::Gameplay);
}
