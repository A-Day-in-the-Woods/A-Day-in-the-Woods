#include "Gameplay.h"


void visit(Node* node) {
	std::cout << "Visiting " << node->data().first << std::endl;
}

Graph< pair<string, int>, int> graph(172); // A* Graph


Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer,SDL_Event& event, GameState& t_currentState) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_player(m_tile, graph)
	//m_inputSystem(t_currentState)
{
	m_tile.reserve(200);
	initNodeFiles();

	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic2.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	//m_player.addComponent(new InputComponent());
	//m_inputSystem.addEntity(m_player.getEntity());
}



Gameplay::~Gameplay()
{
}

void Gameplay::update()
{

	
	
	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}

	if (!startAstar)
	{

		aStar();
		startAstar = !startAstar;

		//m_healthSystem.removeEntityFromSystem(0);
		//m_testEntity->removeComponent(ComponentType::HEALTH);

	}

	m_player.update();

}

void Gameplay::render()
{

	//SDL_RenderClear(m_renderer);
	
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);



	for (int i = 0; i < m_tile.size(); i++)
	{
		m_tile[i].render(m_renderer);
	}



	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int i = 0; i < 41; i ++)
	{

		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
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
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(130)->m_x + 5, graph.nodeIndex(130)->m_y + 5, graph.nodeIndex(81)->m_x + 5, graph.nodeIndex(81)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(122)->m_x + 5, graph.nodeIndex(122)->m_y + 5, graph.nodeIndex(123)->m_x + 5, graph.nodeIndex(123)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(122)->m_x + 5, graph.nodeIndex(122)->m_y + 5, graph.nodeIndex(22)->m_x + 5, graph.nodeIndex(22)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(123)->m_x + 5, graph.nodeIndex(123)->m_y + 5, graph.nodeIndex(25)->m_x + 5, graph.nodeIndex(25)->m_y + 5);

	for (int i = 148; i < 152; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(148)->m_x + 5, graph.nodeIndex(148)->m_y + 5, graph.nodeIndex(27)->m_x + 5, graph.nodeIndex(27)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(152)->m_x + 5, graph.nodeIndex(152)->m_y + 5, graph.nodeIndex(28)->m_x + 5, graph.nodeIndex(28)->m_y + 5); //weird top right bit


	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(170)->m_x + 5, graph.nodeIndex(170)->m_y + 5, graph.nodeIndex(171)->m_x + 5, graph.nodeIndex(171)->m_y + 5);

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(170)->m_x + 5, graph.nodeIndex(170)->m_y + 5, graph.nodeIndex(76)->m_x + 5, graph.nodeIndex(76)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(171)->m_x + 5, graph.nodeIndex(171)->m_y + 5, graph.nodeIndex(129)->m_x + 5, graph.nodeIndex(129)->m_y + 5);
	

	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(149)->m_x + 5, graph.nodeIndex(149)->m_y + 5, graph.nodeIndex(153)->m_x + 5, graph.nodeIndex(153)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(153)->m_x + 5, graph.nodeIndex(153)->m_y + 5, graph.nodeIndex(154)->m_x + 5, graph.nodeIndex(154)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(154)->m_x + 5, graph.nodeIndex(154)->m_y + 5, graph.nodeIndex(63)->m_x + 5, graph.nodeIndex(63)->m_y + 5);

	for (int i = 162; i < 166; i++)
	{
		SDL_RenderDrawLine(m_renderer, graph.nodeIndex(i)->m_x + 5, graph.nodeIndex(i)->m_y + 5, graph.nodeIndex(i + 1)->m_x + 5, graph.nodeIndex(i + 1)->m_y + 5);
	}
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(166)->m_x + 5, graph.nodeIndex(166)->m_y + 5, graph.nodeIndex(26)->m_x + 5, graph.nodeIndex(26)->m_y + 5);
	SDL_RenderDrawLine(m_renderer, graph.nodeIndex(162)->m_x + 5, graph.nodeIndex(162)->m_y + 5, graph.nodeIndex(75)->m_x + 5, graph.nodeIndex(75)->m_y + 5);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	m_player.render(m_renderer);

	//SDL_RenderPresent(m_renderer);
}

void Gameplay::processEvent()
{
	//m_inputSystem.update(m_event,m_player);

}

void Gameplay::setGameState()
{
	m_game.startMinGame();
	m_game.setGameState(GameState::Minigame);
}


/// <summary>
/// Uses A* From one node to another
/// </summary>
void Gameplay::aStar()
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
void Gameplay::initNodeFiles()
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
