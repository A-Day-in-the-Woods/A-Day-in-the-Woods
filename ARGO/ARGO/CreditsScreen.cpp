#include "CreditsScreen.h"

CreditScreen::CreditScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event) :
	m_game(game),
	m_event(event),
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
	
	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}
}

void CreditScreen::render()
{	
	//SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
}

void CreditScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
