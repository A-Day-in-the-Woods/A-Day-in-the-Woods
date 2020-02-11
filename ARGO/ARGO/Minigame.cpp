#include "Minigame.h"

MinigameScreen::MinigameScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer)
{
	
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic4.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	SDL_Surface* reticleSurface = IMG_Load("ASSETS/IMAGES/reticle.png");
	m_reticleTexture = SDL_CreateTextureFromSurface(m_renderer, reticleSurface);
	SDL_FreeSurface(reticleSurface);

	SDL_Surface* buttonSurface = IMG_Load("ASSETS/IMAGES/button.png");
	m_buttonTexture = SDL_CreateTextureFromSurface(m_renderer, buttonSurface);
	SDL_FreeSurface(buttonSurface);

	SDL_Surface* potSurface = IMG_Load("ASSETS/IMAGES/honeyPot.png");
	m_honeyPotTexture = SDL_CreateTextureFromSurface(m_renderer, potSurface);
	SDL_FreeSurface(potSurface);


	reticleRectangle.h = 200;
	reticleRectangle.w = 200;
	reticleRectangle.x = 800;
	reticleRectangle.y = 350;

	buttonRectangle.h = 150;
	buttonRectangle.w = 150;
	buttonRectangle.x = 250;
	buttonRectangle.y = 800;

	buttonRectangle2.h = 150;
	buttonRectangle2.w = 150;
	buttonRectangle2.x = 650;
	buttonRectangle2.y = 800;

	buttonRectangle3.h = 150;
	buttonRectangle3.w = 150;
	buttonRectangle3.x = 1050;
	buttonRectangle3.y = 800;
	
	buttonRectangle4.h = 150;
	buttonRectangle4.w = 150;
	buttonRectangle4.x = 1450;
	buttonRectangle4.y = 800;

	honeyRectangle.h = 150;
	honeyRectangle.w = 150;

}

MinigameScreen::~MinigameScreen()
{
}

void MinigameScreen::update()
{
	


	switch (m_miniGameID)
	{
	default:
		break;

	case 1:
		m_runningTime = std::chrono::high_resolution_clock::now() - m_startTime;
		if (m_runningTime > m_randTime)
		{
			honeyRectangle.x -= m_velocityX;
			honeyRectangle.y -= m_velocityY;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}



	std::cout << "Minigame update" << std::endl;
	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}
}



void MinigameScreen::render()
{
	
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_reticleTexture, NULL, &reticleRectangle);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &buttonRectangle);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &buttonRectangle2);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &buttonRectangle3);
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &buttonRectangle4);
	SDL_RenderCopy(m_renderer, m_honeyPotTexture, NULL, &honeyRectangle);
	
	//SDL_RenderPresent(m_renderer);
	std::cout << "Minigame render" << std::endl;
}

void MinigameScreen::spriteMove()
{
	
	m_directionX = (honeyRectangle.x - reticleRectangle.x);
	m_directionY = (honeyRectangle.y - reticleRectangle.y);


	distance = sqrt((m_directionX) * (m_directionX) + (m_directionY) * (m_directionY));

	//m_angle = std::atan(m_directionY / m_directionX) * (180 / 3.141592);

	m_velocityX = m_directionX / (distance * 0.06);
	m_velocityY = m_directionY / (distance * 0.06);

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
		m_randomNumber = randomNumber(6, 1);
		m_randTime = std::chrono::seconds(m_randomNumber);

		switch (m_spawn)
		{
		case 1:
			honeyRectangle.x = -200;
			honeyRectangle.y = 380;
			break;
		case 2:
			honeyRectangle.x = 2100;
			honeyRectangle.y = 380;
			break;
		case 3:
			honeyRectangle.x = 830;
			honeyRectangle.y = -200;
			break;
		case 4:
			honeyRectangle.x = 830;
			honeyRectangle.y = 1200;
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

int MinigameScreen::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}
