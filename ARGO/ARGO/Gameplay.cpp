#include "Gameplay.h"





Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer,SDL_Event& event, GameState& t_currentState ,SDL_Window* t_window, InputSystem & t_input) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_window(t_window),
	m_inputSystem(t_input)
{
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic2.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	m_DiceRect.h = 200;
	m_DiceRect.w = 200;
	m_DiceRect.x = 100;
	m_DiceRect.y = 100;
}



Gameplay::~Gameplay()
{
}

void Gameplay::update(movementSystem & t_move)
{

	m_diceRoll = t_move.getDiceRoll();
	setDiceTexture();

	//focus = camera->focus(m_player[0]);

	// Update Camera based on new focus
	camera->update(focus);


	if (m_event.type == SDL_KEYDOWN)
	{
		if ( m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}


	t_move.update();
	//m_player.update();

	// SDL_Rect to focus on
	//focus = camera->focus(m_player[0]);

	// Update Camera based on new focus
	camera->update(focus);
	
	m_inputSystem.update(m_event, t_move);
}
void Gameplay::render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, Graph< pair<string, int>, int>& graph)
{

	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL );
	SDL_RenderCopy(m_renderer, m_DiceTexture, NULL, &m_DiceRect);

	float width = (float)camera->getLookAt()->w;
	float height = (float)camera->getLookAt()->h;
	float max_width = ((float)SCREEN_WIDTH / (float)camera->getLookAt()->w) * 0.75;
	float max_height = ((float)SCREEN_HEIGHT / (float)camera->getLookAt()->h) * 0.75;

	float ratio = calculateScale(width, height, max_width, max_height);
	SDL_RenderSetScale(m_renderer, scale, scale);


	drawLines(graph, t_player);


	offset->x = focus->x - camera->getCamera()->x;
	offset->y = focus->y - camera->getCamera()->y;
	offset->w = focus->w;
	offset->h = focus->h;
	
	
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(m_renderer, offset);


	// Little target Box in middle of Focus
	offset->w = CHARACTER_WIDTH;
	offset->h = CHARACTER_HEIGHT;
	offset->x = ((focus->x + focus->w / 2) - offset->w / 2) - camera->getCamera()->x;
	offset->y = ((focus->y + focus->h / 2) - offset->h / 2) - camera->getCamera()->y;
	SDL_RenderDrawRect(m_renderer, offset);

	for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
		SDL_RenderDrawPoint(m_renderer, SCREEN_WIDTH / 2, i);
	}

	for (int i = 0; i < SCREEN_WIDTH; i += 4) {
		SDL_RenderDrawPoint(m_renderer, i, SCREEN_HEIGHT / 2);
	}

	// Level Crosshairs
	for (int i = 0; i < LEVEL_HEIGHT; i += 4) {
		SDL_RenderDrawPoint(m_renderer, LEVEL_WIDTH / 2 - camera->getCamera()->x, i);
	}

	for (int i = 0; i < LEVEL_WIDTH; i += 4) {
		SDL_RenderDrawPoint(m_renderer, i, LEVEL_HEIGHT / 2 - camera->getCamera()->y);
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);




	for (int i = 0; i < t_tile.size(); i++) {t_tile[i].render(m_renderer);}


	for (int i = 0; i < t_player.size(); i++)
	{
		t_player[i]->render(m_renderer);
	}

	SDL_RenderPresent(m_renderer);
}

void Gameplay::processEvent(movementSystem & t_move)
{
	m_inputSystem.update(m_event, t_move);

	

	if (m_event.type == SDL_KEYDOWN)
	{
		//if (SDLK_UP == m_event.key.keysym.sym)
		//{
		//	cameraBox.y += 10;			
		//	SDL_RenderSetViewport(m_renderer, &cameraBox);
		//}

		//if (SDLK_DOWN== m_event.key.keysym.sym)
		//{
		//	cameraBox.y -= 10;
		//	SDL_RenderSetViewport(m_renderer, &cameraBox);
		//}

		//if (SDLK_LEFT == m_event.key.keysym.sym)
		//{
		//	cameraBox.h -= 90;
		//	cameraBox.w -= 144;
		//	cameraBox.x += 10;
		//}

		//if (SDLK_RIGHT == m_event.key.keysym.sym)
		//{
		//	cameraBox.h -= 90;
		//	cameraBox.w -= 144;
		//	cameraBox.x -= 10;
		//}


	/*	cameraBox.x = m_player.getPosition().x;
		cameraBox.y = m_player.getPosition().y;
		SDL_RenderSetViewport(m_renderer, &cameraBox);*/


		if (SDLK_w == m_event.key.keysym.sym) 
		{
			scale += .01;
			if (scale > 2) { scale = 2; }
		}
		if (SDLK_s == m_event.key.keysym.sym) 
		{

			scale -= .01;
			if (scale < 1) { scale = 1; }
		}


		std::cout << scale << std::endl;

		
	}
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

void Gameplay::setDiceTexture()
{
	switch (m_diceRoll)
	{
	default:
		break;

	case 1:
		m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceOne.png");

		break;
	case 2:
		m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceTwo.png");

		break;
	case 3:
		m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceThree.png");

		break;
	case 4:
		m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceFour.png");

		break;
	case 5:
		m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceFive.png");

		break;
	case 6:
		m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceSix.png");

		break;
	}
	m_DiceTexture = SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface);
	SDL_FreeSurface(m_DiceSurface);
}