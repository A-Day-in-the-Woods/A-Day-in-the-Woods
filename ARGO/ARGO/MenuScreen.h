
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
	int button = 0;
	SDL_Texture* m_TestingTexture;
	SDL_Texture* m_buttonTexture;
	SDL_Rect m_buttonPos;

	SDL_Surface* menu[4];
	SDL_Rect m_textPos[4] = { { 800,100,300,100 },{ 800,300,300,100 },{ 800,500,300,100 },{ 850,700,200,100 } };
	SDL_Texture* m_menuTexture[4];
};
#endif // MENU
