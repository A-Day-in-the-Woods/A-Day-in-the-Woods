#include "Game.h"

/// <summary>
/// Function for visiting nodes, used in A*
/// </summary>
/// <param name="node"></param>
void visit(Node* node) {
	cout << "Visiting: " << node->data().first << endl;
}

Graph< pair<string, int>, int> graph(4); // A* Graph


/// <summary>
/// Constructor for the game class.
/// </summary>
Game::Game()
{
	initNodeFiles();

	try
	{
		// Try to initalise SDL in general
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw "Error Loading SDL";
		
		// Create SDL Window Centred in Middle Of Screen
		m_window = SDL_CreateWindow("Bear Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, NULL);
		// Check if window was created correctly
		if (!m_window) throw "Error Loading Window";

		//Create the SDL Renderer 
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		//Check if the renderer was created correclty
		if (!m_renderer) throw "Error Loading Renderer";

		// Sets clear colour of renderer to black and the color of any primitives
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
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

	m_healthSystem.addEntity(m_testEntity);

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
	SDL_Event event;
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
	m_healthSystem.update();

	if (!startAstar)
	{
		
		aStar();
		startAstar = !startAstar;

		m_healthSystem.removeEntityFromSystem(0);
		//m_testEntity->removeComponent(ComponentType::HEALTH);

		//std::cout << graph.nodeIndex(1)->m_x;

	}
	m_healthSystem.update();
}

/// <summary>
/// Render function
/// </summary>
void Game::render()
{
	SDL_RenderClear(m_renderer);
	//Draw Here

	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

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
/// Uses A* From one node to another
/// </summary>
void Game::aStar()
{
	vector<Node*> nodeVector;
	graph.aStar(graph.nodeIndex(nodemap["a"]), graph.nodeIndex(nodemap["d"]), visit, nodeVector);

	cout << "The node path taken is :" << endl;

	for (int i = nodeVector.size() - 1; i > -1; i--)
	{
		cout << nodeVector[i]->data().first << endl;
	}
}

/// <summary>
/// Loades in files for A*
/// </summary>
void Game::initNodeFiles()
{
	myfile.open("Nodes.txt");	// nodes
	while (myfile >> nodeLabel.first >> posX >> posY)
	{
		graph.addNode(nodeLabel, posX, posY, index);
		nodemap[nodeLabel.first] = index;
		index++;
	}
	myfile.close();


	myfile.open("NodeDistances.txt");	// arcs
	while (myfile >> from >> to >> weight) {
		graph.addArc(nodemap[from], nodemap[to], weight);
	}
	myfile.close();
}
