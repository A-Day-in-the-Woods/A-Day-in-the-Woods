#pragma once
#include "SDL.h"

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 

class Player
{
public:
	Player();
	~Player();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);
	
	void setPosition();
	void getPosition();

private:
	
	



	SDL_Rect rect;//temp rect for a player square 


};
