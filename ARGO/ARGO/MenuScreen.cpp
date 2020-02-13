#include "MenuScreen.h"

MenuScreen::MenuScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS\\IMAGES\\pic.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	SDL_Surface* tempButton = IMG_Load("ASSETS\\IMAGES\\temp_button.png");
	m_buttonTexture = SDL_CreateTextureFromSurface(m_renderer, tempButton);
	SDL_FreeSurface(tempButton);
	m_buttonPos = { 50,50,100,100 };

	
	menu[0] = IMG_Load("ASSETS\\IMAGES\\game.png");
	menu[1] = IMG_Load("ASSETS\\IMAGES\\options.png");
	menu[2] = IMG_Load("ASSETS\\IMAGES\\credits.png");
	menu[3] = IMG_Load("ASSETS\\IMAGES\\quit.png");

	for (int i = 0; i < MENU_NUM; i++)
	{
		m_menuTexture[i] = SDL_CreateTextureFromSurface(m_renderer, menu[i]);
		SDL_FreeSurface(menu[i]);
	}
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::update()
{
	
	

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
			button++;
			if (button >= 4)
			{
				button = 0;
			}
		}
		
		if (m_event.key.keysym.sym == SDLK_UP)
		{
			SDL_Delay(200);
			button--;
			if (button <= -1)
			{
				button = 3;
			}
		}
	}

	if (button == 0)
	{
		m_buttonPos.x = 650;
		m_buttonPos.y = 100;
	}
	else if (button == 1)
	{
		m_buttonPos.x = 650;
		m_buttonPos.y = 300;
	}
	else if (button == 2)
	{
		m_buttonPos.x = 650;
		m_buttonPos.y = 500;
	}
	else if (button == 3)
	{
		m_buttonPos.x = 700;
		m_buttonPos.y = 700;
	}
	std::cout << button << std::endl;

}

void MenuScreen::render()
{
	
	//SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
	
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &m_buttonPos);
	for (int i = 0; i < MENU_NUM; i++)
	{
		SDL_RenderCopy(m_renderer, m_menuTexture[i], NULL, &m_textPos[i]);
	}
}

void MenuScreen::setGameState()
{
	if (button == 0)
	{
		m_game.setGameState(GameState::Gameplay);
	
	}
	else if (button == 1)
	{
		m_game.setGameState(GameState::Options);
	}
	else if (button == 2)
	{
		m_game.setGameState(GameState::Credit);
	}
	else if (button == 3)
	{
		m_game.setGameState(GameState::Quit);
	}
}
