#include "Game.h"




void visit(Node* node) {
	std::cout << "Visiting " << node->data().first << std::endl;
}

Graph< pair<string, int>, int> graph(172); // A* Graph


/// <summary>
/// Constructor for the game class.
/// </summary>
Game::Game() :
	m_inputSystem(),
	m_movementSystem(m_currentState, m_tile, graph)
{
	m_tile.reserve(200);
	initNodeFiles();


	try
	{
		// Try to initalise SDL in general
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw "Error Loading SDL";

		// Create SDL Window Centred in Middle Of Screen

		m_window = SDL_CreateWindow("Bear Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1820, 980, NULL);

		// Check if window was created correctly
		if (!m_window) throw "Error Loading Window";

		//Create the SDL Renderer 
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		//Check if the renderer was created correctly
		if (!m_renderer) throw "Error Loading Renderer";

		// Sets clear colour of renderer to black and the color of any primitives
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);



		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			m_player.push_back(new Player(i));
		}
		//for (int i = m_player.size(); i < 4; i++)
		//{

		//	//add ai here 
		//	m_player.push_back(new Player(i));
		//	m_player[i]->IsAI = true;
		//		
		//}


		m_npc.push_back(new NPC(m_tile, graph, 1));
		m_npc.push_back(new NPC(m_tile, graph, 2));
		m_npc.push_back(new NPC(m_tile, graph, 3));



		for (int i = 0; i < m_player.size(); i++)
		{
			m_player[i]->addComponent(new InputComponent());
			m_player[i]->addComponent(new MovementComponent());
			m_movementSystem.addEntity(m_player[i]->getEntity(), *m_player[i]->getPlayerRectRef(), m_player[i]->IsAI);
			m_inputSystem.addEntity(m_player[i]);
		}

		m_menuscreen = new MenuScreen(*this, m_renderer, event,m_currentState, m_inputSystem,m_player);
		m_optionscreen = new OptionScreen(*this, m_renderer, event, m_currentState, m_inputSystem, m_player);
		m_gameplayscreen = new Gameplay(*this, m_renderer, event, m_currentState , m_window, m_inputSystem,m_player);
		m_creditscreen = new CreditScreen(*this, m_renderer, event, m_currentState, m_inputSystem, m_player);
		m_minigamescreen = new MinigameScreen(*this, m_renderer, event, m_currentState, m_inputSystem,m_player);

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

void Game::startMinGame()
{
	m_minigamescreen->startMinGame(1);
}

/// <summary>
/// Processes SDL event
/// </summary>
void Game::processEvent()
{
	//SDL_Event(event);
	
	SDL_PollEvent(&event);
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
		switch (m_currentState)
		{
		case GameState::Menu:
			m_menuscreen->processEvent();
			break;
		case GameState::Options:
			m_optionscreen->processEvent();
			break;
		case GameState::Gameplay:
			m_gameplayscreen->processEvent(m_movementSystem);
			break;
		case GameState::Credit:
			m_creditscreen->processEvent();
			break;
		case GameState::Minigame:
			m_minigamescreen->processEvent();
			break;
		case GameState::Quit:
			m_isRunning = false;
		default:
			break;
		}
		break;
	}

	switch (m_currentState)
	{
	case GameState::Menu:
		m_menuscreen->processEvent();
		break;
	case GameState::Options:
		m_optionscreen->processEvent();
		break;
	case GameState::Gameplay:
		m_gameplayscreen->processEvent(m_movementSystem);
		break;
	case GameState::Credit:
		m_creditscreen->processEvent();
		break;
	case GameState::Minigame:
		m_minigamescreen->processEvent();
		break;
	case GameState::Quit:
		m_isRunning = false;
	default:
		break;
	}

}

/// <summary>
/// 
/// Update function
/// </summary>
void Game::update()
{
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
		m_gameplayscreen->update(m_tile, m_player, m_npc, m_movementSystem);
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
		m_gameplayscreen->render(m_tile, m_player, m_npc, graph);
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

	SDL_RenderPresent(m_renderer);

}
void Game::renderNOW()
{
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


/// <summary>
/// Loades in files for A*
/// </summary>
void Game::initNodeFiles()
{
	myfile.open("Nodes.txt");	// nodes
	while (myfile >> nodeLabel.first >> posX >> posY >> type)
	{
		graph.addNode(nodeLabel, posX, posY, type, index);
		nodemap[nodeLabel.first] = index;
		index++;

		m_tile.push_back(Tile(posX, posY, type));
	}
	myfile.close();


	myfile.open("NodeLinks.txt");	// arcs
	while (myfile >> from >> to >> weight) {
		graph.addArc(nodemap[from], nodemap[to], weight);

	}

	myfile.close();
}
