#include "Gameplay.h"

Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer) :
	m_game(game),
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
	
}

void Gameplay::render()
{
	std::cout << "Gameplay render" << std::endl;
	//SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

	//SDL_RenderPresent(m_renderer);
}

void Gameplay::setGameState()
{
	m_game.setGameState(GameState::Credit);
}
