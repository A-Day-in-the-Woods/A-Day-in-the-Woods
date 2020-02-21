
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
#include "NPC.h"
#include <InputSystem.h>
#include "Entity.h"
#include "MovementSystem.h"
#include "MovementComponent.h"
#include "Camera.h"


class Game;


class Gameplay
{
public:
	Gameplay(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState , SDL_Window* t_window, InputSystem& t_input, std::vector<Player*> t_entity);
	~Gameplay();
	void update(std::vector<Player*>& t_player, MovementSystem & t_move);
	void render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, Graph< pair<string, int>, int>& graph);
	void processEvent();
	void setGameState();
	void drawLines(Graph< pair<string, int>, int>& graph, std::vector<Player*>& t_player);


	//camera
	Camera * camera = new Camera();
	// Initialize Focus, where camera will look
	SDL_Rect* focus = new SDL_Rect();
	// Initialize Offset
	SDL_Rect* offset = new SDL_Rect();
	
	NPC m_npcOne;
	NPC m_npcTwo;
	NPC m_npcThree;





private:
	
	float calculateScale(float width, float height, float maxWidth, float maxHeight);


	SDL_Window* m_window;

	void setDiceTexture();	

	//------------ Camera -------------
	SDL_Rect cameraBox = {0,0, 0,0};
	float scale = 1;


	SDL_Texture* m_DiceTexture; // Dice texture
	SDL_Surface* m_DiceSurface;
	SDL_Rect m_DiceRect;
	int m_diceRoll = 1;


	// ------ A* stuff ----------
	//void aStar();


	

	bool startAstar{ false };
	//------! A* stuff ------------

	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	std::vector<Player*> m_entity;
	GameState& m_currentState;
	InputSystem& m_inputSystem;
};

#endif // !GAMEPLAY