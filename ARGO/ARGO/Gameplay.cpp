#include "Gameplay.h"

Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer,SDL_Event& event, GameState& t_currentState ,SDL_Window* t_window, InputSystem & t_input, std::vector<Player*> t_entity, AudioManager& t_audioManager):
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_window(t_window),
	m_inputSystem(t_input),
	m_entity(t_entity),
	m_currentState(t_currentState),
	m_audioManager(t_audioManager)
{
	m_numberPlayers = m_entity.size();
	
	//SDL_LoadWAV("ASSETS/AUDIO/intro.wav", &wavSpec, &wavBuffer, &wavLength);
	//deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);

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

	m_DiceRect.push_back(SDL_Rect{ 205,220,100,100 });
	m_DiceRect.push_back(SDL_Rect{ 1705,220,100,100 });
	m_DiceRect.push_back(SDL_Rect{ 205,820,100,100 });
	m_DiceRect.push_back(SDL_Rect{ 1705,820,100,100 });

	SDL_Surface* WinSurface;
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP1.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP2.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP3.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP4.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/pic2Glass.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));

	m_Winsscreen.h = 1080;
	m_Winsscreen.w = 1920;
	m_Winsscreen.x = 0;
	m_Winsscreen.y = 0;

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

	for (int i = 0; i < 100; i++) {m_clouds.push_back(SDL_Rect{ randomNumber(1300,500),randomNumber(900,100),150,100 });} //make 100 clouds

	for (int i = 0; i < 4 ; i++)
	{
		m_outLine.push_back(SDL_Rect{ -60,(i*200)-100,200,700 });
		m_outLine.push_back(SDL_Rect{ 1860,(i * 200)-100,250,700 });
	}

	for (int i = 0; i < 4; i++) {m_outLine.push_back(SDL_Rect{ i*550,820 - 100,150,700 });} //make out line of bushes 

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
	SDL_Delay(3000);
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);

	//AudioManager::Release();
	//m_audioManager = NULL;
}

void Gameplay::update(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, MovementSystem& t_move)
{

	if (!setUp)
	{
		m_audioManager.PlayMusic("testSong.wav",10);
		m_audioManager.PlaySfx("s_intro.wav", 75);
		//SDL_PauseAudioDevice(deviceId, 0);
		t_npc[0]->turn = true;
		setUp = true;
	}
	
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		t_move.update(i);
		m_entity[i]->update(t_move);
		//m_entity[i]->setTileType(t_tile[t_move.getIndex(i)].getType(), t_move.getIndex(i));
	}

	for (int i = 0; i < m_clouds.size(); i++)
	{
		int temp = randomNumber(80, 0);

		if (temp == 0){
		m_clouds[i].x += 10;
		m_clouds[i].h -= 10;
		m_clouds[i].w -= 15;}

		else if (temp == 1){
		m_clouds[i].x -= 10;
		m_clouds[i].h += 10;
		m_clouds[i].w += 15;}

		if (m_clouds[i].x > 1500 || m_clouds[i].x < 300 || m_clouds[i].y > 950 || m_clouds[i].y < 0 || m_clouds[i].h > 150 || m_clouds[i].h < 50) {
			m_clouds.erase(m_clouds.begin() + i);
			m_clouds.push_back(SDL_Rect{ randomNumber(1300,500),randomNumber(900,100),150,100 });
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
		if (t_npc[m_npcCount]->end)
		{
			m_npcCount++;
			if (m_npcCount >= t_npc.size())
			{
				m_npcCount = 0;
			}
			t_npc[m_npcCount]->end = false;
			t_npc[m_npcCount]->turn = true;
		}
	}*/
	
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



	offset->x = focus->x - camera->getCamera()->x;
	offset->y = focus->y - camera->getCamera()->y;
	offset->w = focus->w;
	offset->h = focus->h;

	
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
	
	if (m_flipUIBear)
	{
		m_rotation -= 1;
		if (m_rotation < -5) { m_flipUIBear = false; }
	}
	else
	{
		m_rotation += 1;
		if (m_rotation > 5) { m_flipUIBear = true; }
	}


	for (int i = 0; i < t_tile.size(); i++)
	{
		t_tile[i].render(m_renderer);
	}

	for (int i = 0; i < m_numberPlayers ;i++)
	{
		if (i == m_turnOrder) {
			if(m_entity[m_turnOrder]->getLastButtonPressed() == 1) {setDiceTexture(i);}
			m_entity[i]->render(m_renderer, m_rotation);
			SDL_RenderCopyEx(m_renderer, m_PlayerShadowUITexture[i], NULL, &m_PlayerShadowUIRect[i], m_rotation, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_PlayerUITexture[i], NULL, &m_PlayerUIRect[i], m_rotation, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i], m_rotation, NULL, SDL_FLIP_NONE);
		}
		else
		{
			m_entity[i]->render(m_renderer, 0);
			SDL_RenderCopyEx(m_renderer, m_PlayerShadowUITexture[i], NULL, &m_PlayerShadowUIRect[i], 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_PlayerUITexture[i], NULL, &m_PlayerUIRect[i], 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i], 0, NULL, SDL_FLIP_NONE);
		}
	}





	for (int i = 0; i < m_clouds.size(); i++) {SDL_RenderCopyEx(m_renderer, m_CloudTexture, NULL, &m_clouds[i], 0, NULL, SDL_FLIP_NONE);}

	for (int i = 0; i < t_npc.size(); i++) {t_npc[i]->render(m_renderer);}

	SDL_RenderPresent(m_renderer);
}

void Gameplay::renderWin(int index)
{
	SDL_RenderClear(m_renderer);

	switch (index)
	{
	case 0:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, &m_Winsscreen);
		break;
	case 1:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, &m_Winsscreen);
		break;
	case 2:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, &m_Winsscreen);
		break;
	case 3:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, &m_Winsscreen);
		break;
	default:
		break;
	}

	SDL_RenderPresent(m_renderer);
	SDL_Delay(500);
	setGameState();

}


void Gameplay::processEvent(MovementSystem & t_move)
{

	for (int i = 0; i < m_numberPlayers; i++)
	{
		if (m_turnOrder == m_entity[i]->getId())
		{
			if (t_move.getPlayerDiceValue(i) == -2)
			{
				m_inputSystem.update(m_event, m_currentState, m_entity[i], i);
			}
			else if (t_move.getPlayerDiceValue(i) == -3)
			{
				m_turnOrder++;
				if (m_turnOrder == m_entity.size())
					m_turnOrder = 0;
				t_move.setPlayerDiceValue(i, -1);
			}
			else
			{
				if (t_move.getPlayerDiceValue(i) == -1 && !t_move.IsThePlayerMoving(i))
				{
					t_move.setPlayerDiceValue(i, 0);
					m_turnOrder++;
					if (m_turnOrder == m_entity.size())
						m_turnOrder = 0;
					m_entity[i]->setLastButton(NULL);
				}
				else
				{
					m_inputSystem.update(m_event, m_currentState, m_entity[i], i);
				}
			}
		}
	}
}

void Gameplay::setGameState()
{
	//SDL_RenderSetScale(m_renderer, 1, 1);
	//m_game.startMinGame();
	m_game.setGameState(GameState::Menu);
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