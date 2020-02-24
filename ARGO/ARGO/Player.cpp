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
	rect.w = 30;
	rect.h = 40;
}

void Player::update()
{
}

void Player::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 155, 255, 255);
	SDL_RenderCopy(t_renderer, m_PlayerTexture, NULL, &rect);
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
