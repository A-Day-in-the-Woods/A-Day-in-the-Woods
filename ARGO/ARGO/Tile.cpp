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
	count = 0;
}

void Tile::update()
{
	switch (m_type)
	{
	case 1:
		green();
		break;
	case 2:
		purple();
		break;
	case 3:
		pink();
		break;
	case 4:
		blue();
		break;
	case 5:
		navy();
		break;
	case 6:
		orange();
		break;
	case 7:
		red();
		break;
	case 8:
		yellow();
		break;
	default:
		break;
	}
}

void Tile::render(SDL_Renderer* t_renderer)
{
	if (m_type == 1)
	{
		SDL_SetRenderDrawColor(t_renderer, 159, 212, 119, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if(m_type == 2)
	{
		SDL_SetRenderDrawColor(t_renderer, 187, 134, 217, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if (m_type == 3)
	{
		SDL_SetRenderDrawColor(t_renderer, 235, 160, 197, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if (m_type == 4)
	{
		SDL_SetRenderDrawColor(t_renderer, 94, 202, 214, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if (m_type == 5)
	{
		SDL_SetRenderDrawColor(t_renderer, 97, 133, 232, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if (m_type == 6)
	{
		SDL_SetRenderDrawColor(t_renderer, 255, 147, 5, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if (m_type == 7)
	{
		SDL_SetRenderDrawColor(t_renderer, 217, 87, 80, 255);
		SDL_RenderFillRect(t_renderer, &rect);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else 
	{
		SDL_SetRenderDrawColor(t_renderer, 245, 243, 142, 255);
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

void Tile::green()
{
	std::cout << "good square" << std::endl;
}

void Tile::purple()
{
	std::cout << "shop" << std::endl;
}

void Tile::pink()
{
	std::cout << "honey item square" << std::endl;
}

void Tile::blue()
{
	std::cout << "dice square" << std::endl;
}

void Tile::navy()
{
	std::cout << "bounce square" << std::endl;

}

void Tile::orange()
{
	std::cout << "honey puddle square" << std::endl;
	//stuck += 1;
}

void Tile::red()
{
	std::cout << "bee square" << std::endl;
}

void Tile::yellow()
{
	std::cout << "bad square" << std::endl;
}
