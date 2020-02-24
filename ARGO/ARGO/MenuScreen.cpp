#include "MenuScreen.h"

MenuScreen::MenuScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer)
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
	
	switch (m_currentButton)
	{
	default:
		break;
	case 0:
		if (flip)
		{
			m_buttonSelectorRect[0].w += 1;
			m_buttonSelectorRect[0].h += 1;
			if (m_buttonSelectorRect[0].w >= 450 || m_buttonSelectorRect[0].h >= 250) { flip = false; }
		}
		else
		{
			m_buttonSelectorRect[0].w -= 1;
			m_buttonSelectorRect[0].h -= 1;
			if (m_buttonSelectorRect[0].w >= 400 || m_buttonSelectorRect[0].h <= 200) { flip = true; }
		}
		break;
	case 1:
		if (flip)
		{
			m_buttonSelectorRect[1].w += 1;
			m_buttonSelectorRect[1].h += 1;
			if (m_buttonSelectorRect[1].w >= 450 || m_buttonSelectorRect[1].h >= 250) { flip = false; }
		}
		else
		{
			m_buttonSelectorRect[1].w -= 1;
			m_buttonSelectorRect[1].h -= 1;
			if (m_buttonSelectorRect[1].w >= 400 || m_buttonSelectorRect[1].h <= 200) { flip = true; }
		}
		break;
	case 2:
		if (flip)
		{
			m_buttonSelectorRect[2].w += 1;
			m_buttonSelectorRect[2].h += 1;
			if (m_buttonSelectorRect[2].w >= 450 || m_buttonSelectorRect[2].h >= 250) { flip = false; }
		}
		else
		{
			m_buttonSelectorRect[2].w -= 1;
			m_buttonSelectorRect[2].h -= 1;
			if (m_buttonSelectorRect[2].w >= 400 || m_buttonSelectorRect[2].h <= 200) { flip = true; }
		}
		break;
	case 3:
		if (flip)
		{
			m_buttonSelectorRect[3].w += 1;
			m_buttonSelectorRect[3].h += 1;
			if (m_buttonSelectorRect[3].w >= 450 || m_buttonSelectorRect[3].h >= 250) { flip = false; }
		}
		else
		{
			m_buttonSelectorRect[3].w -= 1;
			m_buttonSelectorRect[3].h -= 1;
			if (m_buttonSelectorRect[3].w >= 400 || m_buttonSelectorRect[3].h <= 200) { flip = true; }
		}
		break;
	}

	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
		
		if (m_event.key.keysym.sym == SDLK_DOWN)
		{
			SDL_Delay(200);
			m_currentButton++;
			if (m_currentButton >= 4) {m_currentButton = 0;}
		}
		
		if (m_event.key.keysym.sym == SDLK_UP)
		{
			SDL_Delay(200);
			m_currentButton--;
			if (m_currentButton <= -1) {m_currentButton = 3;}
		}
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
