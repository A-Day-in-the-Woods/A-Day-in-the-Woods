#pragma once
#include "SDL.h"

#include<vector>
#include"Tile.h"
#include "iostream"
#include"Graph.h"
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
	Player(std::vector<Tile> & t_map, Graph< pair<string, int>, int> & t_g);
	~Player();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);
	
	void setPosition(float t_x, float t_y);
	SDL_Rect getPosition();

	void nodeNavigation(int t_diceRoll);

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

private:
	
	int randomNumber(int t_max, int t_min);
	int m_DiceNumber = 1;


	bool m_Abutton = false;
	bool m_Bbutton = false;
	bool m_Xbutton = false;
	bool m_Ybutton = false;

	std::vector<Tile> & m_map;


	int CurrentGameBoardIndex;

	Graph< pair<string, int>, int>& m_graph;


	SDL_Rect rect;//temp rect for a player square 
};
