#include "SplashScreen.h"

SplashScreen::SplashScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity):
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity)
{
	m_numberPlayers = m_entity.size();
	SDL_Surface* m_titleSurface = IMG_Load("ASSETS/IMAGES/titleScreen.png");
	m_splashTexture = SDL_CreateTextureFromSurface(m_renderer, m_titleSurface);
	SDL_FreeSurface(m_titleSurface);


	SDL_Surface* m_buttonSelectorSurface;
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/ABluePawButton.png");
	m_buttonSelectorTexture = (SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	SDL_FreeSurface(m_buttonSelectorSurface);

	m_buttonSelectorRect= { 800 ,700,200,200 };
	m_titleRect = { -200,0,2200,1100 };

}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::update()
{
	if (flip)
	{
		m_buttonSelectorRect.w += 1;
		m_buttonSelectorRect.h += 1;

		if (m_buttonSelectorRect.w >= 450 || m_buttonSelectorRect.h >= 250) { flip = false; }
	}
	else
	{
		m_buttonSelectorRect.w -= 1;
		m_buttonSelectorRect.h -= 1;
		if (m_buttonSelectorRect.w >= 400 || m_buttonSelectorRect.h <= 200) { flip = true; }
	}



	if (m_entity[0]->m_lastButtonPressed == 1)
	{
		m_entity[0]->setLastButton(NULL);
		setGameState();
	}

	if (m_entity[0]->IsAI == true)
	{
		m_entity[0]->setLastButton(NULL);
		setGameState();
	}
}

void SplashScreen::render()
{
	SDL_RenderCopy(m_renderer, m_splashTexture, NULL, &m_titleRect);
	SDL_RenderCopyEx(m_renderer, m_buttonSelectorTexture, NULL, &m_buttonSelectorRect, 0, NULL, SDL_FLIP_NONE);

}

void SplashScreen::processEvent()
{
	for (int i = 0; i < m_numberPlayers; i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}
}

void SplashScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
