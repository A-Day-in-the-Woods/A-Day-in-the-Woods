#include "MenuScreen.h"

MenuScreen::MenuScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity)
{
	m_backgroundSurface = IMG_Load("ASSETS\\IMAGES\\pic3.png");
	m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);


	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\game.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\options.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\credits.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\quit.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));

	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/ABluePawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/AGreenPawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/APinkPawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/APurplePawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));


	for (int i = 0; i < MENU_NUM; i++)
	{
		m_buttonSelectorRect.push_back(SDL_Rect{ 550 ,(i*250),200,200 });
		m_menuButtonPositionSelected.push_back(SDL_Rect{ 750 ,(i * 250),400,200 });
		m_menuButtonPosition.push_back(SDL_Rect{ 750 ,(i * 250),350,150 });
	}
	


}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::update()
{

		if (flip)
		{
			m_buttonSelectorRect[m_currentButton].w += 1;
			m_buttonSelectorRect[m_currentButton].h += 1;
			if (m_buttonSelectorRect[m_currentButton].w >= 450 || m_buttonSelectorRect[m_currentButton].h >= 250) { flip = false; }
		}
		else
		{
			m_buttonSelectorRect[m_currentButton].w -= 1;
			m_buttonSelectorRect[m_currentButton].h -= 1;
			if (m_buttonSelectorRect[m_currentButton].w >= 400 || m_buttonSelectorRect[m_currentButton].h <= 200) { flip = true; }
		}
	
	
	


		if (m_entity[0]->m_lastButtonPressed == 1)
		{
			m_entity[0]->setLastButton(NULL);
			setGameState();
		}
	
		if (m_entity[0]->m_lastButtonPressed == 3)
		{
			m_entity[0]->setLastButton(NULL);
			m_currentButton++;
			if (m_currentButton >= 4) {m_currentButton = 0;}
		}
		
		if (m_entity[0]->m_lastButtonPressed == 2)
		{
			m_entity[0]->setLastButton(NULL);
			m_currentButton--;
			if (m_currentButton <= -1) {m_currentButton = 3;}
		}
		
}

void MenuScreen::render()
{
	SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
	
	for (int i = 0; i < MENU_NUM; i++)
	{
		if (i == m_currentButton)
		{
			SDL_RenderCopy(m_renderer, m_menuButtonTexture[i], NULL, &m_menuButtonPositionSelected[i]);
		}
		else
		{
			SDL_RenderCopy(m_renderer, m_menuButtonTexture[i], NULL, &m_menuButtonPosition[i]);
		}
	}

	SDL_RenderCopyEx(m_renderer, m_buttonSelectorTexture[m_currentButton], NULL, &m_buttonSelectorRect[m_currentButton], 90, NULL, SDL_FLIP_NONE);

}

void MenuScreen::processEvent()
{
	for (int i = 0; i < m_entity.size(); i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}
}

void MenuScreen::setGameState()
{

	switch (m_currentButton)
	{
	default:
		m_game.setGameState(GameState::Gameplay);
		std::cout << "error on Menu select" << std::endl;
		break;
	case 0:
		m_game.setGameState(GameState::Gameplay);
		break;
	case 1:
		m_game.setGameState(GameState::Options);
		break;
	case 2:
		m_game.setGameState(GameState::Credit);
		break;
	case 3:
		m_game.setGameState(GameState::Quit);
		break;
	}
}
