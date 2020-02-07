#include "Minigame.h"

MinigameScreen::MinigameScreen(Game& game, SDL_Renderer* t_renderer) :
	m_game(game),
	m_renderer(t_renderer)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic4.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);
}

MinigameScreen::~MinigameScreen()
{
}

void MinigameScreen::update()
{
	std::cout << "Minigame update" << std::endl;
}

void MinigameScreen::render()
{
	std::cout << "Minigame render" << std::endl;
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

	SDL_RenderPresent(m_renderer);
}

void MinigameScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
