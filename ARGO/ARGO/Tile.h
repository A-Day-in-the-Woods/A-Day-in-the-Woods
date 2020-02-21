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
	Tile(float t_x , float t_y);
	~Tile();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);

	void setPosition();
	SDL_Rect & getPosition();

private:




	SDL_Rect rect;//temp rect for a tile square 


};

#endif // !TILE_H