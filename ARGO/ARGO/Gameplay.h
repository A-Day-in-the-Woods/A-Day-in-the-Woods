
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
	void update(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, MovementSystem & t_move);
	void render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, Graph< pair<string, int>, int>& graph);
	void processEvent(MovementSystem& t_move);
	void setGameState();
	int randomNumber(int t_max, int t_min);
	
	int m_npcCount = 0;

	int m_turnOrder{ 0 };

private:
	int m_numberPlayers;
	
	float calculateScale(float width, float height, float maxWidth, float maxHeight);
	SDL_Window* m_window;

	void setDiceTexture(int m_playerID);

	int m_rotation = 0;






	//------------ Camera -------------
	float scale = .9f;
	Camera * camera = new Camera();	//camera
	SDL_Rect* focus = new SDL_Rect();
	SDL_Rect* offset = new SDL_Rect();




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
	
	std::vector<SDL_Texture*>m_PlayerShadowUITexture; // Player Shadow UI texture
	std::vector<SDL_Rect> m_PlayerShadowUIRect;
	SDL_Surface* m_PlayerShadowUISurface;

	//tile	
	std::vector<Tile> m_tile;
	SDL_Texture* m_TileTexture; // tile texture
	SDL_Surface* m_TileSurface;

	//Clouds
	std::vector<SDL_Rect> m_clouds;
	SDL_Texture* m_CloudTexture; // Clouds texture
	SDL_Surface* m_CloudSurface;

	//Outline
	std::vector<SDL_Rect> m_outLine;
	SDL_Texture* m_outLineTexture; // outline texture
	SDL_Surface* m_outLineSurface;
	
	// ------ A* stuff ----------
	//void aStar();


	
	bool setUp{ false };
	bool startAstar{ false };
	//------! A* stuff ------------


	bool m_flipUIBear{ false };

	Game& m_game;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	std::vector<Player*> m_entity;

	GameState& m_currentState;
	InputSystem& m_inputSystem;



	
};

#endif // !GAMEPLAY