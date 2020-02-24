#include "Gameplay.h"





Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer,SDL_Event& event, GameState& t_currentState ,SDL_Window* t_window, InputSystem & t_input, std::vector<Player*> t_entity):
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_window(t_window),
	m_npcOne(m_tile, graph, 1, visit),
	m_npcTwo(m_tile, graph, 2, visit),
	m_npcThree(m_tile, graph, 3, visit),	
	m_inputSystem(t_input),
	m_entity(t_entity),
	m_currentState(t_currentState)
{

	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceOne.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceTwo.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceThree.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceFour.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceFive.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceSix.png"));



	// Initialize GameObject Positions
	for (int i = 0; i < m_numberPlayers; i++) {

		m_PlayerUIRect.push_back(SDL_Rect{ 10,i * 250,200,300 });
		m_DiceRect.push_back(SDL_Rect{ 200,i * 250,300,300 });

		switch (i)
		{
		default:
			break;
		case 0:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear1.png");
			break;
		case 1:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear2.png");
			break;
		case 2:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear3.png");
			break;
		case 3:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear4.png");
			break;
		}
		m_PlayerUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerUISurface));
		m_DiceTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface[0]));

		m_entity[i]->assignSprite(m_PlayerUITexture[i]);

	}
	


	m_clouds.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		m_clouds.push_back(SDL_Rect{ randomNumber(1300,500),randomNumber(900,100),150,100 });
	}


	m_CloudSurface = IMG_Load("ASSETS/IMAGES/cloud.png");
	m_CloudTexture = SDL_CreateTextureFromSurface(m_renderer, m_CloudSurface);

	m_tile.reserve(200);

	m_backgroundSurface = IMG_Load("ASSETS/IMAGES/Board.jpg");
	m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);

	m_backgroundRect.h = 1300;
	m_backgroundRect.w = 900;
	m_backgroundRect.x = 550;
	m_backgroundRect.y = -100;

	m_backgroundSurface = IMG_Load("ASSETS/IMAGES/pic2.png");
	m_backgroundTextureTwo = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);





	m_npcOne.turn = true;
}

Gameplay::~Gameplay()
{
}

void Gameplay::update(std::vector<Player*>& t_player, MovementSystem & t_move)
{

	t_move.update();


	//m_diceRoll = m_moveSystem.getDiceRoll();
	//setDiceTexture();

	for (int i = 0; i < m_numberPlayers; i++)
	{
		m_entity[i]->update();
	}


	for (int i = 0; i < m_clouds.size(); i++)
	{
		int temp = randomNumber(80, 0);
		if (temp == 0)
		{
			m_clouds[i].x += 5;
		}
		else if(temp == 1)
		{
			m_clouds[i].x -= 5;
		}

	}
	
	
	if (m_event.type == SDL_KEYDOWN)
	{

		if ( m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}


		
	if (m_npcOne.turn)
	{
		m_npcOne.update();

		if (m_npcOne.m_diceNumber == 0)
		{
			if (m_tile[m_npcOne.currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 1 tile" << std::endl;
				m_tile[m_npcOne.currentGameBoardIndex].count++;
				m_tile[m_npcOne.currentGameBoardIndex].update();
				SDL_Delay(500);
			}
			if (!m_npcOne.stuck)
			{
				m_tile[m_npcOne.currentGameBoardIndex].count = 0;
			}
			m_npcOne.turn = false;
			m_npcTwo.turn = true;
		}
	}
	else if (m_npcTwo.turn)
	{
		m_npcTwo.update();

		if (m_npcTwo.m_diceNumber == 0)
		{
			if (m_tile[m_npcTwo.currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 2 tile" << std::endl;
				m_tile[m_npcTwo.currentGameBoardIndex].count++;
				m_tile[m_npcTwo.currentGameBoardIndex].update();
				SDL_Delay(500);
			}
			if (!m_npcTwo.stuck)
			{
				m_tile[m_npcTwo.currentGameBoardIndex].count = 0;
			}
			m_npcTwo.turn = false;
			m_npcThree.turn = true;

		}
	}
	else if (m_npcThree.turn)
	{
		m_npcThree.update();
	//m_moveSystem.update();
	//m_player.update();

		if (m_npcThree.m_diceNumber == 0)
		{
			if (m_tile[m_npcThree.currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 3 tile" << std::endl;
				m_tile[m_npcThree.currentGameBoardIndex].count++;
				m_tile[m_npcThree.currentGameBoardIndex].update();
				SDL_Delay(500);
			}

			if (!m_npcThree.stuck)
			{
				m_tile[m_npcThree.currentGameBoardIndex].count = 0;
			}
			m_npcThree.turn = false;
			m_npcOne.turn = true;

		}
	}

	
	// SDL_Rect to focus on
	focus = camera->focus(m_entity);
	// Update Camera based on new focus
	camera->update(focus);


}
void Gameplay::render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, Graph< pair<string, int>, int>& graph)
{

	SDL_RenderClear(m_renderer);
	SDL_RenderSetScale(m_renderer, scale, scale);

	SDL_RenderCopy(m_renderer, m_backgroundTextureTwo, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_backgroundTexture,NULL, &m_backgroundRect);

	drawLines(graph, t_player);


	offset->x = focus->x - camera->getCamera()->x;
	offset->y = focus->y - camera->getCamera()->y;
	offset->w = focus->w;
	offset->h = focus->h;
	
	
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(m_renderer, offset);



	for (int i = 0; i < m_clouds.size(); i++)
	{
		if ((m_clouds[i].x > offset->x) + m_clouds[i].w/2)
		{
			if(m_clouds[i].x < (offset->x + offset->w))
			{
				if (m_clouds[i].y > (offset->y) - m_clouds[i].h / 1.9)
				{
					if (m_clouds[i].y < (offset->y + offset->h))
					{
						m_clouds.erase(m_clouds.begin() + i);
					}
				}
			}
		}
	}

	// Little target Box in middle of Focus
	//offset->w = CHARACTER_WIDTH ;
	//offset->h = CHARACTER_HEIGHT ;
	//offset->x = (((focus->x + focus->w / 2) - offset->w / 2) - camera->getCamera()->x);
	//offset->y = (((focus->y + focus->h / 2) - offset->h / 2) - camera->getCamera()->y);
	//SDL_RenderDrawRect(m_renderer, offset);

	for (int i = 0; i < m_numberPlayers; i++)
	{
		m_entity[i]->render(m_renderer);
		SDL_RenderCopy(m_renderer, m_PlayerUITexture[i], NULL, &m_PlayerUIRect[i]);	

		setDiceTexture(i);
		SDL_RenderCopy(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i]);
	}

	for (int i = 0; i < m_clouds.size(); i++) {SDL_RenderCopy(m_renderer, m_CloudTexture, NULL, &m_clouds[i]);}

	m_npcOne.render(m_renderer);
	m_npcTwo.render(m_renderer);
	m_npcThree.render(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Gameplay::processEvent()
{
	for (int i = 0; i < m_entity.size(); i++) {m_inputSystem.update(m_event, m_currentState, m_entity[i]);}
	
}

void Gameplay::setGameState()
{
	SDL_RenderSetScale(m_renderer, 1, 1);
	m_game.startMinGame();
	m_game.setGameState(GameState::Minigame);
}

void Gameplay::drawLines(Graph< pair<string, int>, int>& graph, std::vector<Player*>& t_player)
{

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

	for (int i = 0; i < t_player.size(); i++)
	{
		t_player[i]->render(m_renderer);
	}

	//SDL_RenderPresent(m_renderer);
}

float Gameplay::calculateScale(float width, float height, float maxWidth, float maxHeight)
{
	return max(maxWidth / width, maxHeight / height);
}

void Gameplay::setDiceTexture(int m_playerID)
{	
	m_DiceTexture[m_playerID] = SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface[m_entity[m_playerID]->getDiceRoll()-1]);
}

int Gameplay::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}


