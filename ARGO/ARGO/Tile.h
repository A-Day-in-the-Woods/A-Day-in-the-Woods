#ifndef TILE_H
#define TILE_H

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 
#include <SDL.h>

class Tile
{
public:
	Tile(float t_x , float t_y, int t_type);
	~Tile();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);

	void setPosition();
	SDL_Rect & getPosition();

	int count;
private:

	SDL_Rect rect;//temp rect for a tile square 
	int m_type;

	void green();
	void purple();
	void pink();
	void blue();
	void navy();
	void orange();
	void red();
	void yellow();
};

#endif // !TILE_H