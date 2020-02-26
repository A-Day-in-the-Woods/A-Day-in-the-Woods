#include "Player.h"

Player::Player(int entityIdNum) :
	Entity(entityIdNum)
{
	SetUp();
}

Player::~Player()
{
}

void Player::assignSprite(SDL_Texture* t_PlayerTexture)
{
	m_PlayerTexture = t_PlayerTexture;
}

void Player::SetUp()
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 20;
	rect.h = 20;

	m_spriteBody.x = 0;
	m_spriteBody.y = 0;
	m_spriteBody.w = 40;
	m_spriteBody.h = 50;
}

void Player::update(MovementSystem & t_move)
{
	m_spriteBody.x = rect.x - 5.0f;
	m_spriteBody.y = rect.y - 20.0f;

	m_takingTurn = t_move.IsThePlayerMoving(this->getEntity()->getId());
}

void Player::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 155, 255, 255);
	SDL_RenderCopy(t_renderer, m_PlayerTexture, NULL, &m_spriteBody);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void Player::setPosition(float t_x, float t_y)
{
	rect.x = t_x;
	rect.y = t_y;
}

void Player::setTileType(int t_type, int t_index)
{
	tileType = t_type;
	currentIndex = t_index;
}

SDL_Rect * Player::getPlayerRectRef()
{
	return & rect;
}

void Player::tileBehaviour()
{
	switch (tileType)
	{
	case 1:
		SDL_Delay(500);
		std::cout << "good square" << std::endl;
		break;
	case 2:
		switch (currentIndex)
		{
		case 32:
			SDL_Delay(500);
			std::cout << "story 1" << std::endl;
			break;
		case 62:
			SDL_Delay(500);
			std::cout << "story 2" << std::endl;
			break;
		case 104:
			SDL_Delay(500);
			std::cout << "story 3" << std::endl;
			break;
		case 125:
			SDL_Delay(500);
			std::cout << "story 4" << std::endl;
			break;
		default:
			break;
		}
		break;
	case 3:
		SDL_Delay(500);
		std::cout << "bounce square" << std::endl;
		break;
	case 4:
		SDL_Delay(500);
		std::cout << "dice square" << std::endl;
		break;
	case 5:
		SDL_Delay(500);
		std::cout << "honey puddle square" << std::endl;
		stuck = true;
		break;
	case 6:
		SDL_Delay(500);
		std::cout << "tumble square" << std::endl;
		break;
	default:
		break;
	}
}