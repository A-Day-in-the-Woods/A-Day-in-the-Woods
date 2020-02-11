#include "Gameplay.h"

Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer, SDL_Event& event) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic2.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);
}

Gameplay::~Gameplay()
{
}

void Gameplay::update()
{
	std::cout << "Gameplay update" << std::endl;
	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}
}

void Gameplay::render()
{
	std::cout << "Gameplay render" << std::endl;
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
}

void Gameplay::setGameState()
{
	m_game.setGameState(GameState::Minigame);
}
