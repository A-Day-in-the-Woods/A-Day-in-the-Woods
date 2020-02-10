#include "Minigame.h"

MinigameScreen::MinigameScreen(Game& game, SDL_Renderer* t_renderer) :
	m_game(game),
	m_renderer(t_renderer)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic4.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	SDL_Surface* reticleSurface = IMG_Load("ASSETS/IMAGES/reticle.png");
	m_reticleTexture = SDL_CreateTextureFromSurface(m_renderer, reticleSurface);
	SDL_FreeSurface(reticleSurface);

	SDL_Surface* buttonSurface = IMG_Load("ASSETS/IMAGES/button.png");
	m_buttonTexture = SDL_CreateTextureFromSurface(m_renderer, buttonSurface);
	SDL_FreeSurface(buttonSurface);


	destR.h = 200;
	destR.w = 200;
	destR.x = 800;
	destR.y = 350;

	destR2.h = 150;
	destR2.w = 150;
	destR2.x = 250;
	destR2.y = 800;

	destR3.h = 150;
	destR3.w = 150;
	destR3.x = 650;
	destR3.y = 800;

	destR4.h = 150;
	destR4.w = 150;
	destR4.x = 1050;
	destR4.y = 800;
	
	destR5.h = 150;
	destR5.w = 150;
	destR5.x = 1450;
	destR5.y = 800;
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
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_reticleTexture, NULL, &destR);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &destR2);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &destR3);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &destR4);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &destR5);
	//SDL_RenderPresent(m_renderer);
}

void MinigameScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
