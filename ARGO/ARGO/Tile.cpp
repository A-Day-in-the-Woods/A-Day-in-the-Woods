#include "Tile.h"

Tile::Tile(float t_x, float t_y)
{
	rect.x = t_x;
	rect.y = t_y;
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
	SDL_SetRenderDrawColor(t_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(t_renderer, &rect);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void Tile::setPosition()
{
}

void Tile::getPosition()
{
}
