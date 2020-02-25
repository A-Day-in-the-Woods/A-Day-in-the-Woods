#pragma once


#define SCREEN_WIDTH		1820	 
#define SCREEN_HEIGHT		980
#define LEVEL_WIDTH			1820
#define LEVEL_HEIGHT		980

#define CHARACTER_WIDTH		20
#define CHARACTER_HEIGHT	20

#define MAX					4


// Basic Camera Class using a SDL_Rect
class Camera {
private:
	SDL_Rect* camera;
	SDL_Rect* lookAt;

	int min_x;
	int min_y;
	int max_x;
	int max_y;
	
public:
	Camera()
	{
		camera = new SDL_Rect();
		lookAt = new SDL_Rect();

		this->camera->x = 0;
		this->camera->y = 0;
		this->camera->w = SCREEN_WIDTH;
		this->camera->h = SCREEN_HEIGHT;
	}
	void update(SDL_Rect* focus)
	{
		this->camera->x = ((focus->x + focus->w / 2) - SCREEN_WIDTH / 2) - SCREEN_WIDTH;
		this->camera->y = ((focus->y + focus->y / 2) - SCREEN_HEIGHT / 2) - SCREEN_HEIGHT;

		if (this->camera->x < 100) {
			this->camera->x = 100;}
		if (this->camera->y < 100) {
			this->camera->y = 100;}

		if (this->camera->x > this->camera->w) {this->camera->x = LEVEL_WIDTH - this->camera->w;}

		if (this->camera->y > this->camera->h) {this->camera->y = LEVEL_HEIGHT - this->camera->h;}

	}

	SDL_Rect* getCamera() { return this->camera; }
	SDL_Rect* getLookAt() { return this->lookAt; }

	// The SDL_Rect enclosing the four players
	SDL_Rect* focus(std::vector<Player*> t_players)
	{
		min_x = t_players[0]->getPosition().x;
		min_y = t_players[0]->getPosition().y;
		max_x = t_players[0]->getPosition().x;
		max_y = t_players[0]->getPosition().y;

		for (int i = 1; i < t_players.size(); i++)
		{

			(min_x > t_players[i]->getPosition().x) ? min_x = t_players[i]->getPosition().x : NULL;
			(max_x < t_players[i]->getPosition().x) ? max_x = t_players[i]->getPosition().x + t_players[i]->getPosition().w : NULL;
			(min_y > t_players[i]->getPosition().y) ? min_y = t_players[i]->getPosition().y : NULL;
			(max_y < t_players[i]->getPosition().y) ? max_y = t_players[i]->getPosition().y + t_players[i]->getPosition().h : NULL;
		}

		lookAt->x = min_x;
		lookAt->y = min_y;
		lookAt->w = (max_x - min_x)+200;
		lookAt->h = (max_y - min_y)+200;

		return lookAt;
	}
};
