#include "Game.h"



/// <summary>
/// Constructor for the game class.
/// </summary>
Game::Game()
{


	try
	{
		// Try to initalise SDL in general
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw "Error Loading SDL";
		
		// Create SDL Window Centred in Middle Of Screen
		m_window = SDL_CreateWindow("Bear Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1900, 1000, NULL);
		// Check if window was created correctly
		if (!m_window) throw "Error Loading Window";

		//Create the SDL Renderer 
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		//Check if the renderer was created correclty
		if (!m_renderer) throw "Error Loading Renderer";

		// Sets clear colour of renderer to black and the color of any primitives
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

		m_menuscreen = new MenuScreen(*this, m_renderer);
		m_optionscreen = new OptionScreen(*this, m_renderer);
		m_gameplayscreen = new Gameplay(*this, m_renderer);
		m_creditscreen = new CreditScreen(*this, m_renderer);
		m_minigamescreen = new MinigameScreen(*this, m_renderer);

		// Game is running
		m_isRunning = true;
	}
	catch (std::string error)
	{
		// output error if any part above doesnt load correctly
		std::cout << error << std::endl;
		// game doesnt run
		m_isRunning = false;
	}





	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);


	m_testEntity->addComponent(new HealthComponent());
	m_testEntity->addComponent(new PositionComponent(SDL_Rect{ 100,100,100,100 }));
	m_testEntity->addComponent(new InputComponent());
	m_healthSystem.addEntity(m_testEntity);
	m_inputSystem.addEntity(m_testEntity);
}

/// <summary>
/// destructor for game class
/// </summary>
Game::~Game()
{
	clean();
}

/// <summary>
/// function for the main game update loop
/// </summary>
void Game::run()
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	while (m_isRunning)
	{
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;
		processEvent();
		update();
		render();
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

/// <summary>
/// Processes SDL event
/// </summary>
void Game::processEvent()
{
	SDL_Event(event);
	SDL_PollEvent(&event);

	m_inputSystem.update(event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	case SDL_KEYDOWN:
		// Press Escape to close screen
		
		if (SDLK_ESCAPE == event.key.keysym.sym)
		{
			m_isRunning = false;

		}
		
		break;
	case SDL_MOUSEBUTTONUP:
		if (m_currentState == GameState::Menu)
		{
			m_menuscreen->setGameState();
		}
		else if (m_currentState == GameState::Options)
		{
			m_optionscreen->setGameState();
		}
		else if (m_currentState == GameState::Gameplay)
		{
			m_gameplayscreen->setGameState();
		}
		else if (m_currentState == GameState::Credit)
		{
			m_creditscreen->setGameState();
		}
		else if (m_currentState == GameState::Minigame)
		{
			m_minigamescreen->setGameState();
		}
		break;
	default:
		break;
	}


}

/// <summary>
/// Update function
/// </summary>
void Game::update()
{

	m_player.update();
	//graph.nodeIndex(1)->m_x;
	//graph.nodeIndex(1)->m_Y;

	switch (m_currentState)
	{
	case GameState::Menu:
		m_menuscreen->update();
		break;
	case GameState::Options:
		m_optionscreen->update();
		break;
	case GameState::Gameplay:
		m_gameplayscreen->update();
		break;
	case GameState::Credit:
		m_creditscreen->update();
		break;
	case GameState::Minigame:
		m_minigamescreen->update();
		break;
	case GameState::Quit:
		m_isRunning = false;
	default:
		break;
	}

	m_healthSystem.update();
}

/// <summary>
/// Render function
/// </summary>
void Game::render()
{
	//SDL_RenderClear(m_renderer);
	//Draw Here
	switch (m_currentState)
	{
	case GameState::Menu:
		m_menuscreen->render();
		break;
	case GameState::Options:
		m_optionscreen->render();
		break;
	case GameState::Gameplay:
		m_gameplayscreen->render();
		break;
	case GameState::Credit:
		m_creditscreen->render();
		break;
	case GameState::Minigame:
		m_minigamescreen->render();
		break;
	case GameState::Quit:
		m_isRunning = false;
	default:
		break;
	}

	//SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
	m_player.render(m_renderer);

	SDL_RenderPresent(m_renderer);

}

/// <summary>
/// Cleans up what is needed to be deleted
/// </summary>
void Game::clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_QUIT;
}

