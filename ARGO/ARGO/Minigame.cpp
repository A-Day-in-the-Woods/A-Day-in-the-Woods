#include "Minigame.h"

MinigameScreen::MinigameScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_currentState)
{	
	SDL_Surface* m_backgroundImage = IMG_Load("ASSETS/IMAGES/BG.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundImage);
	SDL_FreeSurface(m_backgroundImage);

	SDL_Surface* tempGlass = IMG_Load("ASSETS/IMAGES/pic2Glass.png");
	m_TestingTextureTwo = SDL_CreateTextureFromSurface(m_renderer, tempGlass);
	SDL_SetTextureBlendMode(m_TestingTextureTwo, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_TestingTextureTwo, 150);
	SDL_FreeSurface(tempGlass);

	SDL_Surface* reticleSurface = IMG_Load("ASSETS/IMAGES/reticle.png");
	m_reticleTexture = SDL_CreateTextureFromSurface(m_renderer, reticleSurface);
	SDL_FreeSurface(reticleSurface);

	SDL_Surface* buttonSurfaceOne = IMG_Load("ASSETS/IMAGES/buttons/ABluePawButton.png");
	m_AbuttonTextureOne = SDL_CreateTextureFromSurface(m_renderer, buttonSurfaceOne);
	SDL_SetTextureBlendMode(m_AbuttonTextureOne, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(buttonSurfaceOne);

	SDL_Surface* buttonSurfaceTwo = IMG_Load("ASSETS/IMAGES/buttons/AGreenPawButton.png");
	SDL_SetTextureBlendMode(m_AbuttonTextureTwo, SDL_BLENDMODE_BLEND);
	m_AbuttonTextureTwo = SDL_CreateTextureFromSurface(m_renderer, buttonSurfaceTwo);
	SDL_FreeSurface(buttonSurfaceTwo);

	SDL_Surface* buttonSurfaceThree = IMG_Load("ASSETS/IMAGES/buttons/APinkPawButton.png");
	SDL_SetTextureBlendMode(m_AbuttonTextureThree, SDL_BLENDMODE_BLEND);
	m_AbuttonTextureThree = SDL_CreateTextureFromSurface(m_renderer, buttonSurfaceThree);
	SDL_FreeSurface(buttonSurfaceThree);

	SDL_Surface* buttonSurfaceFour = IMG_Load("ASSETS/IMAGES/buttons/APurplePawButton.png");
	SDL_SetTextureBlendMode(m_AbuttonTextureFour, SDL_BLENDMODE_BLEND);
	m_AbuttonTextureFour = SDL_CreateTextureFromSurface(m_renderer, buttonSurfaceFour);
	SDL_FreeSurface(buttonSurfaceFour);



	SDL_Surface* potSurface = IMG_Load("ASSETS/IMAGES/HoneyBig.png");
	m_honeyPotTexture = SDL_CreateTextureFromSurface(m_renderer, potSurface);
	SDL_FreeSurface(potSurface);

	m_Winsscreen.h = 1080;
	m_Winsscreen.w = 1920;
	m_Winsscreen.x = 0;
	m_Winsscreen.y = -400;

	reticleRectangle.h = 200;
	reticleRectangle.w = 200;
	reticleRectangle.x = 800;
	reticleRectangle.y = 350;

	buttonRectangle.h = 400;
	buttonRectangle.w = 400;
	buttonRectangle.x = 40;
	buttonRectangle.y = 600;

	buttonRectangle2.h = 400;
	buttonRectangle2.w = 400;
	buttonRectangle2.x = 420;
	buttonRectangle2.y = 600;

	buttonRectangle3.h = 400;
	buttonRectangle3.w = 400;
	buttonRectangle3.x = 1000;
	buttonRectangle3.y = 600;
	
	buttonRectangle4.h = 400;
	buttonRectangle4.w = 400;
	buttonRectangle4.x = 1380;
	buttonRectangle4.y = 600;

	honeyRectangle.h = 150;
	honeyRectangle.w = 150;
}

MinigameScreen::~MinigameScreen()
{
}

void MinigameScreen::processEvent(Player& t_player)
{
	m_inputSystem.update(m_event, t_player);

	if(t_player.isAButtonPressed() == true && m_playerOneAnswerd == false)
	{
		m_ApressedTimeOne = (std::chrono::high_resolution_clock::now() - m_startTime)-m_randTime;
		m_playerOneAnswerd = true;
		SDL_SetTextureColorMod(m_AbuttonTextureOne, 100, 100, 100);

	}
	
	else if (t_player.isBButtonPressed() == true && m_playerTwoAnswerd == false)
	{
		m_ApressedTimeTwo = (std::chrono::high_resolution_clock::now() - m_startTime) - m_randTime;
		m_playerTwoAnswerd = true;
		SDL_SetTextureColorMod(m_AbuttonTextureTwo, 100, 100, 100);
		
	}
	else if (t_player.isXButtonPressed() == true && m_playerThreeAnswerd == false)
	{
		m_ApressedTimeThree = (std::chrono::high_resolution_clock::now() - m_startTime) - m_randTime;
		m_playerThreeAnswerd = true;
		SDL_SetTextureColorMod(m_AbuttonTextureThree, 100, 100, 100);

	}
	else if (t_player.isYButtonPressed() == true && m_playerFourAnswerd == false)
	{
		m_ApressedTimeFour = (std::chrono::high_resolution_clock::now() - m_startTime) - m_randTime;
		m_playerFourAnswerd = true;
		SDL_SetTextureColorMod(m_AbuttonTextureFour, 100, 100, 100);

	}


	if (EndPictureminiGame == true)
	{
		if (m_event.type == SDL_KEYDOWN)
		{
			if (m_event.key.keysym.sym == SDLK_SPACE)
			{
				m_playerFourAnswerd = false;
				m_playerThreeAnswerd = false;
				m_playerTwoAnswerd = false;
				m_playerOneAnswerd = false;
				EndPictureminiGame = false;
				setGameState();
			}
		}
	}
}

void MinigameScreen::update()
{
	


	switch (m_miniGameID)
	{
	default:
		break;

	case 1:
		m_runningTime = std::chrono::high_resolution_clock::now() - m_startTime;

	
		if (m_playerFourAnswerd == true && m_playerThreeAnswerd == true && m_playerTwoAnswerd == true && m_playerOneAnswerd == true)
		{
			SDL_Delay(500);
			GetWinnerPicture();
			EndPictureminiGame = true;
		}
		else if (m_runningTime > m_randTime)
		{
			honeyRectangle.x -= m_velocityX;
			honeyRectangle.y -= m_velocityY;
		}

		if (m_runningTime >= m_randTime + std::chrono::seconds(2)) 
		{
			SDL_Delay(500);
			GetWinnerPicture();
			EndPictureminiGame = true;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
}



void MinigameScreen::render()
{
	
	if (EndPictureminiGame == true)
	{		
		SDL_RenderCopy(m_renderer, m_WinScreenTexture, NULL, &m_Winsscreen);
	}

	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);



	SDL_RenderCopy(m_renderer, m_TestingTextureTwo, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_honeyPotTexture, NULL, &honeyRectangle);// honey pot thatmoves accross the screen


	SDL_RenderCopy(m_renderer, m_reticleTexture, NULL, &reticleRectangle);

	SDL_RenderCopy(m_renderer, m_AbuttonTextureOne, NULL, &buttonRectangle);
	SDL_RenderCopy(m_renderer, m_AbuttonTextureTwo, NULL, &buttonRectangle2);
	SDL_RenderCopy(m_renderer, m_AbuttonTextureThree, NULL, &buttonRectangle3);
	SDL_RenderCopy(m_renderer, m_AbuttonTextureFour, NULL, &buttonRectangle4);


}

void MinigameScreen::spriteMove()
{

	m_directionX = (honeyRectangle.x  - reticleRectangle.x);
	m_directionY = (honeyRectangle.y - reticleRectangle.y);

	distance = sqrt((m_directionX) * (m_directionX) + (m_directionY) * (m_directionY));

	//m_angle = std::atan(m_directionY / m_directionX) * (180 / 3.141592);

	m_velocityX = m_directionX / (distance * 0.04);
	m_velocityY = m_directionY / (distance * 0.04);

}

void MinigameScreen::startMinGame(int t_mineGameID)
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_miniGameID = t_mineGameID;


	switch (t_mineGameID)
	{
	default:
		break;

	case 1:
		m_spawn = randomNumber(4, 1);
		m_randomNumber = randomNumber(5, 1);
		m_randTime = std::chrono::seconds(m_randomNumber);
		SDL_SetTextureColorMod(m_AbuttonTextureOne, 255, 255, 255);
		SDL_SetTextureColorMod(m_AbuttonTextureTwo, 255, 255, 255);
		SDL_SetTextureColorMod(m_AbuttonTextureThree, 255, 255, 255);
		SDL_SetTextureColorMod(m_AbuttonTextureFour, 255, 255, 255);



		switch (m_spawn)
		{
		case 1:

			
			honeyRectangle.x = -200;
			honeyRectangle.y = randomNumber(1080, 0);
			break;
		case 2:

		
			honeyRectangle.x = 2160;
			honeyRectangle.y = randomNumber(1080, 0);
			break;
		case 3:
			

			honeyRectangle.x = randomNumber(1960, 0);
			honeyRectangle.y = -200;
			break;
		case 4:
			honeyRectangle.x = randomNumber(1960, 0);
			honeyRectangle.y = 1280;
			break;
		default:
			break;
		}
		
		
		spriteMove();
	break;
	case 2:
	break;

	}


	
}

void MinigameScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);

}

void MinigameScreen::addPlayer(Player& t_player)
{
	m_inputSystem.addEntity(t_player.getEntity());
}

void MinigameScreen::GetWinnerPicture()
{	
		std::cout << "all answered" << std::endl;
		SDL_Surface* WinSurface;
		if (m_ApressedTimeOne < m_ApressedTimeTwo && m_ApressedTimeOne < m_ApressedTimeThree && m_ApressedTimeOne < m_ApressedTimeFour)
		{
			std::cout << "1 wins " << std::endl;
			WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP1.png");		
		}
		else if (m_ApressedTimeTwo < m_ApressedTimeOne && m_ApressedTimeTwo < m_ApressedTimeThree && m_ApressedTimeTwo < m_ApressedTimeFour)
		{
			std::cout << "2 wins " << std::endl;
			WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP2.png");


		}
		else if (m_ApressedTimeThree < m_ApressedTimeOne && m_ApressedTimeThree < m_ApressedTimeTwo && m_ApressedTimeThree < m_ApressedTimeFour)
		{
			std::cout << "3 wins " << std::endl;
			WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP3.png");

		}
		else if (m_ApressedTimeFour  < m_ApressedTimeOne && m_ApressedTimeFour < m_ApressedTimeTwo && m_ApressedTimeFour < m_ApressedTimeThree)
		{
			std::cout << "4 wins " << std::endl;
			WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP4.png");
		}
		else
		{
			std::cout << "NO ONE Wins" << std::endl;
			WinSurface = IMG_Load("ASSETS/IMAGES/pic2Glass.png");
		}
		m_WinScreenTexture = SDL_CreateTextureFromSurface(m_renderer, WinSurface);
		SDL_FreeSurface(WinSurface);
}

int MinigameScreen::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}
