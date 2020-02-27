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

void Player::render(SDL_Renderer* t_renderer, int t_rotation)
{

	SDL_SetRenderDrawColor(t_renderer, 0, 155, 255, 255);
	SDL_RenderCopyEx(t_renderer, m_PlayerTexture, NULL, &m_spriteBody, t_rotation, NULL, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void Player::setPosition(float t_x, float t_y)
{
	rect.x = t_x;
	rect.y = t_y;
}

SDL_Rect * Player::getPlayerRectRef()
{
	return & rect;
}
