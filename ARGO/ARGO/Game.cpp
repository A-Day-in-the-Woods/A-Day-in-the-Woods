#include "Game.h"

/// <summary>
/// Function for visiting nodes, used in A*
/// </summary>
/// <param name="node"></param>
void visit(Node* node) {
	cout << "Visiting: " << node->data().first << endl;
}

Graph< pair<string, int>, int> graph(172); // A* Graph


/// <summary>
/// Constructor for the game class.
/// </summary>
Game::Game()
{
	m_tile.reserve(200);
	
	initNodeFiles();

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

	m_player.update();
	//graph.nodeIndex(1)->m_x;
	//graph.nodeIndex(1)->m_Y;

	if (!startAstar)
	{
		
		aStar();
		startAstar = !startAstar;

		m_healthSystem.removeEntityFromSystem(0);
		//m_testEntity->removeComponent(ComponentType::HEALTH);

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
	m_player.render(m_renderer);



	for (int i = 0; i < m_tile.size() ; i++)
	{
		m_tile[i].render(m_renderer);
	}



	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int i = 0; i < 41; i ++)
	{

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x+5, graph.nodeIndex(i)->m_y+5, graph.nodeIndex(i + 1)->m_x+5, graph.nodeIndex(i + 1)->m_y+5);

	}

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(39)->m_x + 5, graph.nodeIndex(39)->m_y+5, graph.nodeIndex(42)->m_x + 5, graph.nodeIndex(42)->m_y+5);


	for (int i = 42; i < 54; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y+5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y+5);
	}

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(54)->m_x + 5, graph.nodeIndex(54)->m_y + 5, graph.nodeIndex(37)->m_x + 5, graph.nodeIndex(37)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(35)->m_x + 5, graph.nodeIndex(35)->m_y + 5, graph.nodeIndex(55)->m_x + 5, graph.nodeIndex(55)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(30)->m_x + 5, graph.nodeIndex(30)->m_y + 5, graph.nodeIndex(56)->m_x + 5, graph.nodeIndex(56)->m_y + 5);

	for (int i = 55; i < 101; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(51)->m_x + 5, graph.nodeIndex(51)->m_y + 5, graph.nodeIndex(43)->m_x + 5, graph.nodeIndex(43)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(101)->m_x + 5, graph.nodeIndex(101)->m_y + 5, graph.nodeIndex(4)->m_x + 5, graph.nodeIndex(4)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(108)->m_x + 5, graph.nodeIndex(108)->m_y + 5, graph.nodeIndex(11)->m_x + 5, graph.nodeIndex(11)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(107)->m_x + 5, graph.nodeIndex(107)->m_y + 5, graph.nodeIndex(8)->m_x + 5, graph.nodeIndex(8)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(107)->m_x + 5, graph.nodeIndex(107)->m_y + 5, graph.nodeIndex(108)->m_x + 5, graph.nodeIndex(108)->m_y + 5);

	for (int i = 101; i < 106; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(106)->m_x + 5, graph.nodeIndex(106)->m_y + 5, graph.nodeIndex(99)->m_x + 5, graph.nodeIndex(99)->m_y + 5);

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(127)->m_x + 5, graph.nodeIndex(127)->m_y + 5, graph.nodeIndex(97)->m_x + 5, graph.nodeIndex(97)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(128)->m_x + 5, graph.nodeIndex(128)->m_y + 5, graph.nodeIndex(83)->m_x + 5, graph.nodeIndex(83)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(128)->m_x + 5, graph.nodeIndex(128)->m_y + 5, graph.nodeIndex(127)->m_x + 5, graph.nodeIndex(127)->m_y + 5);



	for (int i = 124; i < 126; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(124)->m_x + 5, graph.nodeIndex(124)->m_y + 5, graph.nodeIndex(93)->m_x + 5, graph.nodeIndex(93)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(126)->m_x + 5, graph.nodeIndex(126)->m_y + 5, graph.nodeIndex(91)->m_x + 5, graph.nodeIndex(91)->m_y + 5);


	for (int i = 109; i < 112; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}

	for (int i = 113; i < 115; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(109)->m_x + 5, graph.nodeIndex(109)->m_y + 5, graph.nodeIndex(14)->m_x + 5, graph.nodeIndex(14)->m_y + 5);

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(112)->m_x + 5, graph.nodeIndex(112)->m_y + 5, graph.nodeIndex(17)->m_x + 5, graph.nodeIndex(17)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(13)->m_x + 5, graph.nodeIndex(13)->m_y + 5, graph.nodeIndex(113)->m_x + 5, graph.nodeIndex(113)->m_y + 5);

	for (int i = 116; i < 121; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(121)->m_x + 5, graph.nodeIndex(121)->m_y + 5, graph.nodeIndex(21)->m_x + 5, graph.nodeIndex(21)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(115)->m_x + 5, graph.nodeIndex(115)->m_y + 5, graph.nodeIndex(116)->m_x + 5, graph.nodeIndex(116)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(114)->m_x + 5, graph.nodeIndex(114)->m_y + 5, graph.nodeIndex(137)->m_x + 5, graph.nodeIndex(137)->m_y + 5);

	for (int i = 129; i < 137; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}




	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(138)->m_x + 5, graph.nodeIndex(138)->m_y + 5, graph.nodeIndex(134)->m_x + 5, graph.nodeIndex(134)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(138)->m_x + 5, graph.nodeIndex(138)->m_y + 5, graph.nodeIndex(115)->m_x + 5, graph.nodeIndex(115)->m_y + 5);

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(135)->m_x + 5, graph.nodeIndex(135)->m_y + 5, graph.nodeIndex(81)->m_x + 5, graph.nodeIndex(81)->m_y + 5);




	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(122)->m_x + 5, graph.nodeIndex(122)->m_y + 5, graph.nodeIndex(123)->m_x + 5, graph.nodeIndex(123)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(122)->m_x + 5, graph.nodeIndex(122)->m_y + 5, graph.nodeIndex(22)->m_x + 5, graph.nodeIndex(22)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(123)->m_x + 5, graph.nodeIndex(123)->m_y + 5, graph.nodeIndex(25)->m_x + 5, graph.nodeIndex(25)->m_y + 5);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);





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

		m_tile.push_back(Tile(posX, posY));
	}
	myfile.close();


	myfile.open("NodeDistances.txt");	// arcs
	while (myfile >> from >> to >> weight) {
		graph.addArc(nodemap[from], nodemap[to], weight);

	}

	myfile.close();
}
