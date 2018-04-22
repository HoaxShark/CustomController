#pragma once
#include "SDL.h"
#include "Object.h"
#include "Wall.h"
#include "SerialInterface.h"
#include "Player.h"


class Game
{
public:
	Game();
	~Game();
	int sensorBlockedValue = 500; // used to tell if the sensor is blocked compared agaisnt the light sensor values
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	void handleWallBlocking(Wall *currentWall);
	Wall* wallList[10];
	SDL_Texture* newImage;
	SDL_Texture* groundImage;
	SDL_Texture* skyImage;
	SDL_Texture* yellowBeam;
	SDL_Texture* redBeam;
	SDL_Texture* blueBeam;
	SDL_Texture* greenBeam;
	SDL_Texture* whiteBeam;
	SDL_Texture* blackBeam;
	SDL_Rect sky;
	SDL_Rect ground;
	Player * player;
	Player * getPlayer();

	bool running() { return isRunning; };

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	bool isRunning;

	SerialInterface* serialInterface;
};

extern Game game;