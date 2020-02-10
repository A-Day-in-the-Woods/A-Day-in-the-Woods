#pragma once
#include "SDL.h"

#include<vector>
#include"Tile.h"
#include "iostream"
#include"Graph.h"

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 



class Player
{
public:
	Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int> & t_g);
	~Player();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);
	
	void setPosition(float t_x, float t_y);
	void getPosition();

	void movePlayerOnBoard();


private:
	
	int dice;

	std::vector<Tile> & m_map;

	int CurrentGameBoardIndex;

	Graph< pair<string, int>, int>& m_graph;


	SDL_Rect rect;//temp rect for a player square 


};
