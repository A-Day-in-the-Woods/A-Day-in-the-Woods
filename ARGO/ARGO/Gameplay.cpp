#include "Gameplay.h"

Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer,SDL_Event& event, GameState& t_currentState ,SDL_Window* t_window, InputSystem & t_input, std::vector<Player*> t_entity):
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_window(t_window),
	m_inputSystem(t_input),
	m_entity(t_entity),
	m_currentState(t_currentState)
{
	m_numberPlayers = m_entity.size();


	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceOne.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceTwo.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceThree.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceFour.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceFive.png"));
	m_DiceSurface.push_back(IMG_Load("ASSETS/IMAGES/Dice/DiceSix.png"));

	m_PlayerUIRect.push_back(SDL_Rect{ 100,0,300,400 });
	m_PlayerUIRect.push_back(SDL_Rect{ 1600,0,300,400 });
	m_PlayerUIRect.push_back(SDL_Rect{ 100,600,300,400 });
	m_PlayerUIRect.push_back(SDL_Rect{ 1600,600,300,400 });

	m_PlayerShadowUIRect.push_back(SDL_Rect{ 110,10,300,400 });
	m_PlayerShadowUIRect.push_back(SDL_Rect{ 1610,10,300,400 });
	m_PlayerShadowUIRect.push_back(SDL_Rect{ 110,610,300,400 });
	m_PlayerShadowUIRect.push_back(SDL_Rect{ 1610,610,300,400 });

	m_DiceRect.push_back(SDL_Rect{ 195,210,120,120 });
	m_DiceRect.push_back(SDL_Rect{ 1695,210,120,120 });
	m_DiceRect.push_back(SDL_Rect{ 195,810,120,120 });
	m_DiceRect.push_back(SDL_Rect{ 1695,810,120,120 });

	m_PlayerShadowUISurface = IMG_Load("ASSETS/IMAGES/Players/bearShadow.png");
	// Initialize GameObject Positions
	for (int i = 0; i < m_numberPlayers ;i++) 
	{
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
		m_PlayerShadowUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerShadowUISurface));

		m_DiceTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface[0]));

		m_entity[i]->assignSprite(m_PlayerUITexture[i]);
	}
	


		m_turnOrder = 0;

	m_clouds.reserve(100);
	m_tile.reserve(200);
	for (int i = 0; i < 100; i++)
	{
		m_clouds.push_back(SDL_Rect{ randomNumber(1300,500),randomNumber(900,100),150,100 });
	}

	for (int i = 0; i < 4 ; i++)
	{
		m_outLine.push_back(SDL_Rect{ -60,(i*200)-100,200,700 });
		m_outLine.push_back(SDL_Rect{ 1860,(i * 200)-100,250,700 });
	}

	for (int i = 0; i < 4; i++)
	{
		m_outLine.push_back(SDL_Rect{ i*550,820 - 100,150,700 });
	}

	m_CloudSurface = IMG_Load("ASSETS/IMAGES/cloud.png");
	m_CloudTexture = SDL_CreateTextureFromSurface(m_renderer, m_CloudSurface);


	m_outLineSurface = IMG_Load("ASSETS/IMAGES/UI/hedge.png");
	m_outLineTexture = SDL_CreateTextureFromSurface(m_renderer, m_outLineSurface);
	

	m_backgroundSurface = IMG_Load("ASSETS/IMAGES/Board.png");
	m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);

	m_backgroundRect={ 75,-10,1920,1080};


	m_backgroundSurface = IMG_Load("ASSETS/IMAGES/pic2.png");
	m_backgroundTextureTwo = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);
}

Gameplay::~Gameplay()
{
}

void Gameplay::update(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, MovementSystem& t_move)
{
	if (!setUp)
	{
		t_npc[0]->turn = true;
		setUp = true;
	}
	
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		t_move.update(i);
		m_entity[i]->update(t_move);
	}


	for (int i = 0; i < m_clouds.size(); i++)
	{
		int temp = randomNumber(80, 0);
		if (temp == 0)
		{
			m_clouds[i].x += 5;
		}
		else if (temp == 1)
		{
			m_clouds[i].x -= 5;
		}

	}

	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_RETURN)
		{
			setGameState();
		}
	}


/*
	if (t_npc[0]->turn)
	{
		t_npc[m_npcCount]->update();
		if (t_npc[m_npcCount]->m_diceNumber == 0)
		{
			if (t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 1 tile" << std::endl;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count++;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].update();
				SDL_Delay(200);
			}
			if (!t_npc[m_npcCount]->stuck)
			{
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count = 0;
			}
			t_npc[0]->turn = false;
			t_npc[1]->turn = true;
			m_npcCount++;
		}
	}
	else if (t_npc[1]->turn)
	{
		t_npc[m_npcCount]->update();
		if (t_npc[m_npcCount]->m_diceNumber == 0)
		{
			if (t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 2 tile" << std::endl;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count++;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].update();
				SDL_Delay(200);
			}
			if (!t_npc[m_npcCount]->stuck)
			{
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count = 0;
			}
			t_npc[1]->turn = false;
			t_npc[2]->turn = true;
			m_npcCount++;
		}
	}
	else if (t_npc[2]->turn)
	{
		t_npc[m_npcCount]->update();
		if (t_npc[m_npcCount]->m_diceNumber == 0)
		{
			if (t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 3 tile" << std::endl;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count++;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].update();
				SDL_Delay(200);
			}
			if (!t_npc[m_npcCount]->stuck)
			{
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count = 0;
			}
			t_npc[2]->turn = false;
			t_npc[0]->turn = true;
			m_npcCount++;
		}
	}

	if (m_npcCount >= t_npc.size())
	{
		m_npcCount = 0;
	}
	*/
	// SDL_Rect to focus on
	focus = camera->focus(m_entity);
	// Update Camera based on new focus
	camera->update(focus);
}

void Gameplay::render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, Graph< pair<string, int>, int>& graph)
{
	SDL_RenderClear(m_renderer);
	SDL_RenderSetScale(m_renderer, scale, scale);

	SDL_RenderCopy(m_renderer, m_backgroundTextureTwo, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, &m_backgroundRect);


	//drawLines(graph, t_player, t_npc);// can remove --------------

	offset->x = focus->x - camera->getCamera()->x;
	offset->y = focus->y - camera->getCamera()->y;
	offset->w = focus->w;
	offset->h = focus->h;
	
	//SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF); // can remove --------------
	//SDL_RenderDrawRect(m_renderer, offset);
	
	for (int i = 0; i < m_clouds.size(); i++)
	{
		if ((m_clouds[i].x > offset->x) + m_clouds[i].w/2){
			if(m_clouds[i].x < (offset->x + offset->w)){
				if (m_clouds[i].y > (offset->y) - m_clouds[i].h / 1.9){
					if (m_clouds[i].y < (offset->y + offset->h)) {m_clouds.erase(m_clouds.begin() + i);}}}}
	}

	for (int i = 0; i < m_outLine.size()-4; i++) { SDL_RenderCopy(m_renderer, m_outLineTexture, NULL, &m_outLine[i]); }
	for (int i = m_outLine.size() - 4; i < m_outLine.size(); i++) {SDL_RenderCopyEx(m_renderer, m_outLineTexture, NULL, &m_outLine[i],90, NULL, SDL_FLIP_NONE);}


	// Little target Box in middle of Focus
	//offset->w = CHARACTER_WIDTH ;
	//offset->h = CHARACTER_HEIGHT ;
	//offset->x = (((focus->x + focus->w / 2) - offset->w / 2) - camera->getCamera()->x);
	//offset->y = (((focus->y + focus->h / 2) - offset->h / 2) - camera->getCamera()->y);
	//SDL_RenderDrawRect(m_renderer, offset);



	m_rotation = m_rotation + 1;
	


	for (int i = 0; i < m_numberPlayers ;i++)
	{
		m_entity[i]->render(m_renderer);
		SDL_RenderCopyEx(m_renderer, m_PlayerShadowUITexture[i], NULL, &m_PlayerShadowUIRect[i], 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(m_renderer, m_PlayerUITexture[i], NULL, &m_PlayerUIRect[i], 0, NULL, SDL_FLIP_NONE);

		if (i == m_turnOrder) {
			setDiceTexture(i);
			SDL_RenderCopyEx(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i], m_rotation, NULL, SDL_FLIP_NONE);
		}
		else
		{SDL_RenderCopyEx(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i], 0, NULL, SDL_FLIP_NONE);}
	}

	for (int i = 0; i < m_clouds.size(); i++) {SDL_RenderCopy(m_renderer, m_CloudTexture, NULL, &m_clouds[i]);}

	SDL_RenderPresent(m_renderer);
}

void Gameplay::processEvent(MovementSystem & t_move)
{
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		if (m_turnOrder == m_entity[i]->getId())
		{

			if (m_entity[i]->getLastButtonPressed() == 1 && !t_move.IsThePlayerMoving(i))
			{
				m_turnOrder++;
				if (m_turnOrder == m_entity.size())
					m_turnOrder = 0;
				m_entity[i]->setLastButton(NULL);
			}
			else
			{
				m_inputSystem.update(m_event, m_currentState, m_entity[i]);

			}
		}
	}

}

void Gameplay::setGameState()
{
	SDL_RenderSetScale(m_renderer, 1, 1);
	m_game.startMinGame();
	m_game.setGameState(GameState::Minigame);
}

void Gameplay::drawLines(Graph< pair<string, int>, int>& graph, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc)
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

	for (int i = 0; i < t_npc.size(); i++)
	{
		t_npc[i]->render(m_renderer);
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