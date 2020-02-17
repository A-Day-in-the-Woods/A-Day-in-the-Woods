
#ifndef GAMEPLAY
#define GAMEPLAY
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include "Tile.h"
#include <map>
#include "Graph.h"
#include "Player.h"
#include <InputSystem.h>
#include "Entity.h"
#include "Camera.h"


class Game;


typedef GraphArc<pair<std::string, int>, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;




class Gameplay
{
public:
	Gameplay(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState , SDL_Window* t_window);
	~Gameplay();
	void update();
	void render();
	void processEvent();
	void setGameState();
	void drawLines();


	//camera
	Camera * camera = new Camera();
	// Initialize Focus, where camera will look
	SDL_Rect* focus = new SDL_Rect();
	// Initialize Offset
	SDL_Rect* offset = new SDL_Rect();



	Player m_player;

private:
	
	float calculateScale(float width, float height, float maxWidth, float maxHeight);


	SDL_Window* m_window;

	void setDiceTexture();	

	//------------ Camera -------------
	SDL_Rect cameraBox = {0,0, 0,0};
	float scale = 1;




	std::vector<Tile> m_tile;

	SDL_Texture* m_DiceTexture; // Dice texture
	SDL_Surface* m_DiceSurface;
	SDL_Rect m_DiceRect;
	int m_diceRoll = 1;


	// ------ A* stuff ----------
	void aStar();

	void initNodeFiles();

	map<string, int> nodemap;
	pair<string, int> nodeLabel;

	int posX = 0;
	int posY = 0;
	int index = 0;
	ifstream myfile;


	string from, to;
	int weight;


	bool startAstar{ false };
	//------! A* stuff ------------

	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	InputSystem m_inputSystem;


};

#endif // !GAMEPLAY
