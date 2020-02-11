#include "CreditsScreen.h"

CreditScreen::CreditScreen(Game& game, SDL_Renderer* t_renderer) :
	m_game(game),
	m_renderer(t_renderer)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic3.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);
}

CreditScreen::~CreditScreen()
{
}

void CreditScreen::update()
{
	
}

void CreditScreen::render()
{
	
	//SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

	//SDL_RenderPresent(m_renderer);
}

void CreditScreen::setGameState()
{
	m_game.setGameState(GameState::Minigame);
}
