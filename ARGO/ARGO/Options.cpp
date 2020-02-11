#include "Options.h"

OptionScreen::OptionScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event) :
	m_game(game),
	m_event(event),
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
	std::cout << "Options update" << std::endl;
	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}
}

void OptionScreen::render()
{
	std::cout << "Options render" << std::endl;
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
}

void OptionScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
