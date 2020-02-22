
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
	int randomNumber(int t_max, int t_min);
	void drawLines(Graph< pair<string, int>, int>& graph, std::vector<Player*>& t_player);



	int m_numberPlayers = 4;

private:
	
	float calculateScale(float width, float height, float maxWidth, float maxHeight);
	SDL_Window* m_window;

	void setDiceTexture(int m_playerID);

	//------------ Camera -------------
	float scale = .9f;
	Camera * camera = new Camera();	//camera
	SDL_Rect* focus = new SDL_Rect();
	SDL_Rect* offset = new SDL_Rect();


	std::vector<Tile> m_tile;
	std::vector<SDL_Rect> m_clouds;

	//background
	SDL_Surface* m_backgroundSurface;
	SDL_Texture* m_backgroundTexture;
	SDL_Rect m_backgroundRect;

	SDL_Texture* m_backgroundTextureTwo;

	

	//Dice
	std::vector <SDL_Texture*> m_DiceTexture; // Dice texture
	std::vector<SDL_Rect> m_DiceRect;
	std::vector <SDL_Surface*> m_DiceSurface;

	//player UI
	std::vector<SDL_Texture*>m_PlayerUITexture; // Player UI texture
	std::vector<SDL_Rect> m_PlayerUIRect;
	SDL_Surface* m_PlayerUISurface;
	

	//tile
	SDL_Texture* m_TileTexture; // tile texture
	SDL_Surface* m_TileSurface;

	//Clouds
	SDL_Texture* m_CloudTexture; // tile texture
	SDL_Surface* m_CloudSurface;
	
	// ------ A* stuff ----------
	//void aStar();


	


	bool startAstar{ false };
	//------! A* stuff ------------

	Game& m_game;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	std::vector<Player*> m_entity;

	GameState& m_currentState;
	InputSystem& m_inputSystem;
};

#endif // !GAMEPLAY
