
#ifndef PLAYER_H
#define PLAYER_H


#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include "Tile.h"
#include <iostream>
#include "Graph.h"
#include "Entity.h"
#include <random>

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 



class Player : public Entity 
{
public:
	Player(int entityIdNum);
	Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int> & t_g);
	~Player();

	void assignSprite(SDL_Texture* t_PlayerTexture);
	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);
	
	void setPosition(float t_x, float t_y);
	SDL_Rect * getPlayerRectRef();

	SDL_Rect getPosition() { return rect; };

	/*
	void nodeNavigation();

	void playerNodeChange(std::list<GraphArc<std::pair<std::string, int>, int>> & newPoint);

	void rollForMove();

	void AButtonPressed(bool t_state);
	void BButtonPressed(bool t_state);
	void XButtonPressed(bool t_state);
	void YButtonPressed(bool t_state);

	bool isAButtonPressed();
	bool isBButtonPressed();
	bool isXButtonPressed();
	bool isYButtonPressed();

	int getDiceRoll() { return m_DiceNumber; };

	bool animateMovingToPoint(float t_DestX, float t_DestY);

	void normalize(float & t_x, float & t_y);
	float length(float t_x, float t_y);


	void leftOrRightChoice(bool t_choice);
	*/


private:
	SDL_Rect rect;//temp rect for a player square 

	int m_diceValue{ 0 };


};
#endif // !PLAYER_H