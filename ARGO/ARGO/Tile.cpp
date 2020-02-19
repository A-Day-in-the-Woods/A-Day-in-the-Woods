#include "Tile.h"

Tile::Tile(float t_x, float t_y, int t_type)
{
	rect.x = t_x;
	rect.y = t_y;
	m_type = t_type;
	SetUp();
}

Tile::~Tile()
{
}

void Tile::SetUp()
{
	rect.w = 10;
	rect.h = 10;
}

void Tile::update()
{
}

void Tile::render(SDL_Renderer* t_renderer)
{
	if (m_type == 1)
	{
		SDL_SetRenderDrawColor(t_renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(t_renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
}

void Tile::setPosition()
{
}

SDL_Rect & Tile::getPosition()
{
	return rect;
}
