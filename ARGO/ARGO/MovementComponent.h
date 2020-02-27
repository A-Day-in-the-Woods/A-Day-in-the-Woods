#pragma once

#include "Component.h"
#include <vector>
#include "Tile.h"
#include "iostream"
#include "Graph.h"
#include <random>
#include <SDL.h>

class MovementComponent : public Component
{

public:
	/*SDL_AudioSpec wavSpec[10];
	Uint32 wavLength[10];
	Uint8* wavBuffer[10];
	SDL_AudioDeviceID deviceId[10;
	int success;*/
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
	int success;

	MovementComponent() : Component(ComponentType::MOVEMENT)
	{
		setUp();
	}

	/// <summary>
	/// Set the body that will be moved
	/// </summary>
	/// <param name="t_rect"></param>
	void setRect(SDL_Rect & t_rect) {
		rect = &t_rect;
	}
	void setAiCheck(bool &t_IsAi) {
		m_IsAi = &t_IsAi;
	}


	int randomNumber(int t_max, int t_min)
	{
		std::random_device device;
		std::mt19937 rng(device());
		std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
		return dist(rng);
	}

	void setUp(){
		

		//
		//SDL_PauseAudioDevice(deviceId, 0);
		CurrentGameBoardIndex = 0;
		m_movementSpeed = -1;
		m_takeingTurn = false;
		choiceLoop = true;
	}

	void update(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g) {
		if (m_takeingTurn)
		{
			nodeNavigation(t_map, t_g);
		}
		else
		{
			rect->x = t_map[CurrentGameBoardIndex].getPosition().x - (rect->w / 4.0f);
			rect->y	= t_map[CurrentGameBoardIndex].getPosition().y - (rect->h / 4.0f);
		}
	}

	void nodeNavigation(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g) {
		if (m_diceRoll > 0)
		{

			std::list<GraphArc<std::pair<std::string, int>, int>> p;

			p = t_g.nodeIndex(CurrentGameBoardIndex)->arcList();

			SDL_Event(event);
			SDL_PollEvent(&event);

		

			if (p.size() > 1)
			{ // direction choice

	
				if (*m_IsAi == true && choiceLoop ==true && m_randomDirectionDecided == false)
				{
					m_currentDiceRoll = p.size()-1;
					m_DirectionChoiceNum = randomNumber(6,1);
					choiceLoop = false;
				}
				else if (m_currentDiceRoll != p.size() || m_currentDiceRoll == -1)
				{
					m_randomDirectionDecided = false;
				}
			


				if (!choiceLoop)
				{


					if (m_DirectionChoiceNum == nodeDirectionCheck(
						p.front().node()->m_x,
						p.front().node()->m_y,
						t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
						t_g.nodeIndex(CurrentGameBoardIndex)->m_y))
					{
						playerNodeChange(p, t_map, t_g);

						if (*m_IsAi == true)
						{
							m_randomDirectionDecided = true;
						}
					}
					else
					{

						p.reverse();
						if (m_DirectionChoiceNum == nodeDirectionCheck(
							p.front().node()->m_x,
							p.front().node()->m_y,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_y))
						{
							playerNodeChange(p, t_map, t_g);

							if (*m_IsAi == true)
							{
								m_randomDirectionDecided = true;
							}
						}
					}
					if (!m_randomDirectionDecided)
					{
						if (*m_IsAi == true)
						{
							m_DirectionChoiceNum = randomNumber(6, 1);
						}
					}

				}
			}
			else
			{ // only one way to go			
				playerNodeChange(p, t_map, t_g);								
			}
		}
		else
		{

			if (MoveForward)
			{
				if (IndexPlaceHolder == CurrentGameBoardIndex)
				{
					std::list<GraphArc<std::pair<std::string, int>, int>> p;
					p = t_g.nodeIndex(CurrentGameBoardIndex)->arcList();
					playerNodeChange(p, t_map, t_g);
				}
				else
				{
					m_diceRoll = -1;
					choiceLoop = false;
					m_takeingTurn = false;
					MoveForward = false;

					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
				}
			}

			if (MoveBack)
			{
				if (animateMovingToPoint(t_map[PriorGameBoardIndex].getPosition().x - (rect->w / 4.0f), t_map[PriorGameBoardIndex].getPosition().y - (rect->h / 4.0f)))
				{
					int tempIndex = CurrentGameBoardIndex;
					CurrentGameBoardIndex = PriorGameBoardIndex;
					PriorGameBoardIndex = tempIndex;

					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -1;
					choiceLoop = false;
					m_takeingTurn = false;

					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;

					MoveBack = false;
				}
			}


			if (m_takeingTurn)
			{
				switch (tileBehaviour(t_map))
				{
				case 0: // Basic Tile
					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -1;
					choiceLoop = false; 
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					break;
				case 10://pt1
					SDL_LoadWAV("ASSETS/AUDIO/Story/st1.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);
					
					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -1;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					break;
				case 11://pt2
					SDL_LoadWAV("ASSETS/AUDIO/Story/st2.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);
					
					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -1;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					break;
				case 12://pt3
					SDL_LoadWAV("ASSETS/AUDIO/Story/st3.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);
					
					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -1;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					break;
				case 13://pt4
					SDL_LoadWAV("ASSETS/AUDIO/Story/st4.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);
					
					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -1;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					choiceLoop = false;
					break;
				case 2://bounce - forward 1
					SDL_LoadWAV("ASSETS/AUDIO/Tiles/forward.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);					
					SDL_PauseAudioDevice(deviceId, 0);
					SDL_Delay(500);
					
					m_diceRoll = 1;
					break;
				case 3://dice - add TURN
					SDL_LoadWAV("ASSETS/AUDIO/Tiles/add.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);

					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -2;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					break;
				case 4://honey - lose turn
					SDL_LoadWAV("ASSETS/AUDIO/Tiles/miss.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);		

					m_takeingTurn = false;
					std::cout << m_diceRoll << std::endl;
					m_diceRoll = -3;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					break;
				case 5:// tumble - back 1
					SDL_LoadWAV("ASSETS/AUDIO/Tiles/back.wav", &wavSpec, &wavBuffer, &wavLength);
					deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
					success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
					SDL_PauseAudioDevice(deviceId, 0);
	
					MoveBack = true;
					//m_takeingTurn = false;
					break;
				}
			}
		}
	}

	void playerNodeChange(std::list<GraphArc<std::pair<std::string, int>, int>>& newPoint, 
							std::vector<Tile>& t_map,
							Graph< pair<string, int>, int>& t_g) {
		for (int i = 0; i < t_map.size(); i++)
		{
			if (CurrentGameBoardIndex == 41)
			{
				std::cout << "Game Won " << std::endl;
				gameWin = true;
				SDL_LoadWAV("ASSETS/AUDIO/end.wav", &wavSpec, &wavBuffer, &wavLength);
				deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
				success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
				SDL_PauseAudioDevice(deviceId, 0);
			}

			if (gameWin)
			{
				break;
			}

			if (newPoint.front().node()->m_x == t_g.nodeIndex(i)->m_x &&
				newPoint.front().node()->m_y == t_g.nodeIndex(i)->m_y)
			{
				// this is then the next tile index to go to

				if (animateMovingToPoint(t_map[i].getPosition().x - (rect->w / 4.0f), t_map[i].getPosition().y - (rect->h / 4.0f)))
				{
					PriorGameBoardIndex = CurrentGameBoardIndex;
					CurrentGameBoardIndex = i;
					m_diceRoll--;
					m_randomDirectionDecided = false;
					choiceLoop = true;
					// direction check here;
				}
				
			}

			
		}
		
	}


	bool getEndGame()
	{
		return gameWin;
	}

	

	void rollForMove(int t_diceRolled) {

		if (!m_takeingTurn)
		{
			m_diceRoll = t_diceRolled;
			m_takeingTurn = true;
			//m_finishedTurn = false;
		}
	}

	bool animateMovingToPoint(float t_DestX, float t_DestY) {
		float tempX = rect->x - t_DestX;
		float tempY = rect->y - t_DestY;

		if (rect->x == t_DestX && rect->y == t_DestY)
			return true;

		normalize(tempX, tempY);

		rect->x += (tempX * m_movementSpeed);
		rect->y += (tempY * m_movementSpeed);

		return false;
	}


	void normalize(float& t_x, float& t_y) {
		float len = sqrt(t_x * t_x + t_y * t_y);

		t_x /= len;
		t_y /= len;
	}

	void leftOrRightChoice(bool t_choice) {
		LeftOrRight = t_choice;
		choiceLoop = false;
	}

	void directionChoice(int t_choice) {
		m_DirectionChoiceNum = t_choice;
		choiceLoop = false;
	}


	bool getTakeingTurn(){
		return m_takeingTurn;
	}

	int getDiceValue()
	{
		return m_diceRoll;
	}

	void setDiceValue(int i)
	{
		m_diceRoll = i;
	}


	int nodeDirectionCheck(int x1, int y1, int x2, int y2)
	{

		if (x1 == x2 && y1 > y2)
		{	// p2 Down
			return 1;
		}
		else if (x1 == x2 && y1 < y2)
		{	// p2 Up
			return 6;
		}
		else if (x1 > x2 && y1 == y2)
		{	// p2 Right
			return 4;
		}
		else if (x1 < x2 && y1 == y2)
		{	// p2 Left
			return 5;
		}

		return -1;
	}

	int getCurrentIndex()
	{
		return CurrentGameBoardIndex;
	}

	int tileBehaviour(std::vector<Tile>& t_map)
	{
		switch (t_map[CurrentGameBoardIndex].getType())
		{
		case 1:
			//SDL_Delay(500);
			std::cout << "good square" << std::endl;
			return 0;
			break;
		case 2:
			switch (CurrentGameBoardIndex)
			{
			case 32:
				//SDL_Delay(500);
				std::cout << "story 1" << std::endl;
				return 10;
				break;
			case 62:
				//SDL_Delay(500);
				std::cout << "story 2" << std::endl;
				return 11;
				break;
			case 104:
				//SDL_Delay(500);
				std::cout << "story 3" << std::endl;
				return 12;
				break;
			case 125:
				//SDL_Delay(500);
				std::cout << "story 4" << std::endl;
				return 13;
				break;
			default:
				break;
			}
			break;
		case 3:
			//SDL_Delay(500);
			std::cout << "bounce square" << std::endl;
			return 2;
			break;
		case 4:
			//SDL_Delay(500);
			std::cout << "dice square" << std::endl;
			return 3;
			break;
		case 5:
			//SDL_Delay(500);
			std::cout << "honey puddle square" << std::endl;
			return 4;
			break;
		case 6:
			//SDL_Delay(500);
			std::cout << "tumble square" << std::endl;
			return 5;
			break;
		default:
			break;
		}
	}

private:

	//Real one
	int CurrentGameBoardIndex;
	int PriorGameBoardIndex;

	bool MoveForward = false;
	bool MoveBack = false;
	int IndexPlaceHolder;

	SDL_Rect * rect;
	bool * m_IsAi;

	bool m_randomDirectionDecided{false};
	bool choiceLoop;

	bool LeftOrRight = false;
	bool useTile = false;
	int m_currentDiceRoll{ -1 };



	bool gameWin = false;
	int playerWon;

	bool m_takeingTurn;

	float m_movementSpeed;

	int m_diceRoll{-1};

	int m_DirectionChoiceNum = -1;
};