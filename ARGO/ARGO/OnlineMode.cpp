#include "OnlineMode.h"

OnlineMode::OnlineMode(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity)
{

	

	m_client = new Client("149.153.106.155", 1111, m_entity);
	m_numberPlayers = m_entity.size();
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic1.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	if (!m_client->Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;

	}

}

OnlineMode::~OnlineMode()
{
}

void OnlineMode::update()
{
	
	int x = numFromString(m_client->getOtherPos()).at(0);



	if (m_entity[0]->m_lastButtonPressed == 4)
	{
		m_entity[0]->setLastButton(NULL);
		SDL_Delay(200);
		setGameState();
	}
}

void OnlineMode::render()
{
	
	//SDL_RenderClear(m_renderer);

	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
}

void OnlineMode::processEvent()
{
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
		m_client->SendString(m_entity[i]->GetValueAsString());
		
	}
	
}

void OnlineMode::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
