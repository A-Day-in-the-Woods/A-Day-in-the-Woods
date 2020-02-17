#pragma once


#define SCREEN_WIDTH		1820 
#define SCREEN_HEIGHT		980
#define LEVEL_WIDTH			200
#define LEVEL_HEIGHT		200

#define CHARACTER_WIDTH		16
#define CHARACTER_HEIGHT	16

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

		//Set the Camera Bounding Box (this box is bound of GameObjects)
		this->camera->x = (focus->x + focus->w / 2) - SCREEN_WIDTH / 2;
		this->camera->y = (focus->y + focus->y / 2) - SCREEN_HEIGHT / 2;


		if (this->camera->x < 0) {this->camera->x = 0;}
		if (this->camera->y < 0) {this->camera->y = 0;}



		if (this->camera->x > this->camera->w)
		{
			this->camera->x = LEVEL_WIDTH - this->camera->w;
		}
		if (this->camera->y > this->camera->h) {
			this->camera->y = LEVEL_HEIGHT - this->camera->h;
		}
	}

	SDL_Rect* getCamera() { return this->camera; }
	SDL_Rect* getLookAt() { return this->lookAt; }

	// The SDL_Rect enclosing the four players
	SDL_Rect* focus(Player* t_player) {
		min_x = t_player->getPosition().x;
		min_y = t_player->getPosition().y;
		max_x = t_player->getPosition().x + 0;
		max_y = t_player->getPosition().y + 0;

		lookAt->x = min_x;
		lookAt->y = min_y;
		lookAt->w = max_x - min_x;
		lookAt->h = max_y - min_y;

		return lookAt;
	}
};
