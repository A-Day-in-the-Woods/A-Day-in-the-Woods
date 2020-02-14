#pragma once
#include "SDL.h"

#include<vector>
#include"Tile.h"
#include "iostream"
#include"Graph.h"
#include "Entity.h"


/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 



class Player : public Entity 
{
public:
	Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int> & t_g);
	~Player();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);
	
	void setPosition(float t_x, float t_y);
	void getPosition();

	void nodeNavigation();

	void playerNodeChange(std::list<GraphArc<std::pair<std::string, int>, int>> & newPoint);


	void rollForMove(int t_diceRoll);

	bool animateMovingToPoint(float t_DestX, float t_DestY);

	void normalize(float & t_x, float & t_y);
	float length(float t_x, float t_y);


	void leftOrRightChoice(bool t_choice);

private:

	std::vector<Tile> & m_map;

	int CurrentGameBoardIndex;

	Graph< pair<string, int>, int>& m_graph;


	SDL_Rect rect;//temp rect for a player square 

	bool choiceLoop;
	bool LeftOrRight = false;

	bool m_takeingTurn;
	float m_movementSpeed;
	int m_diceRoll;
};
