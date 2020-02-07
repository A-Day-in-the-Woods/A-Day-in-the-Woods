#pragma once
#include "SDL.h"

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 

class Tile
{
public:
	Tile(float t_x , float t_y);
	~Tile();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);

	void setPosition();
	void getPosition();

private:




	SDL_Rect rect;//temp rect for a tile square 


};
