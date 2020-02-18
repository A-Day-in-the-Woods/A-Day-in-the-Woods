#include "Player.h"

Player::Player(int entityIdNum) :
	Entity(entityIdNum)
{
	SetUp();
}

Player::~Player()
{
}

void Player::SetUp()
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 20;
	rect.h = 20;
}

void Player::update()
{
}

void Player::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 155, 255, 255);
	SDL_RenderFillRect(t_renderer, &rect);
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

/*
void Player::AButtonPressed(bool t_state)
{
	m_Abutton = t_state;
}

void Player::BButtonPressed(bool t_state)
{
	m_Bbutton = t_state;
}

void Player::XButtonPressed(bool t_state)
{
	m_Xbutton = t_state;
}

void Player::YButtonPressed(bool t_state)
{
	m_Ybutton = t_state;
}

bool Player::isAButtonPressed()
{
	return m_Abutton;
}

bool Player::isBButtonPressed()
{
	return m_Bbutton;
}

bool Player::isXButtonPressed()
{
	return m_Xbutton;
}

bool Player::isYButtonPressed()
{
	return m_Ybutton;
}

int Player::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}

*/