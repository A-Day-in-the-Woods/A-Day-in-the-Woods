
#ifndef MENU
#define MENU

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"

class Game;

class MenuScreen
{
public:
	MenuScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event &event);
	~MenuScreen();
	void update();
	void render();
	void setGameState();
private:
	Game& m_game;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	const int MENU_NUM = 4;
	int m_currentButton = 0;

	//Background
	SDL_Texture* m_backgroundTexture;
	SDL_Surface* m_backgroundSurface;

	//Selector for Buttons 
	std::vector <SDL_Texture*> m_buttonSelectorTexture; // button texture
	std::vector<SDL_Rect> m_buttonSelectorRect;
	SDL_Surface* m_buttonSelectorSurface;

	bool flip{true};
	
	//Buttons
	std::vector <SDL_Texture*> m_menuButtonTexture;
	std::vector<SDL_Rect> m_menuButtonPosition;
	std::vector<SDL_Rect> m_menuButtonPositionSelected;
	SDL_Surface* m_menuButtonSurface;

	

};
#endif // MENU
