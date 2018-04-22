#include "stdafx.h"
#include "Game.h"
#include "Object.h"
#include <SDL_image.h>
#include <time.h>
#include <iostream>

using std::cout;

Game game;

/*
* Constructor 
*
*/
Game::Game()
{
	// starts the random seed
	srand(time(NULL));

	serialInterface = new SerialInterface(); // initiates the serial interface
	// fill the wallList with wall objects
	player = new Player(); // initiate player
	for (unsigned int a = 0; a < sizeof(wallList) / sizeof(wallList[0]); a = a + 1) {
		wallList[a] = new Wall;
	}
	wallList[0]->setWallActive(); // activates the first wall


}

/*
	Decontructor
*/
Game::~Game()
{
}

/*
* init - used to initialise and setup SDL
* Return true if everything is successful
*/
bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL init success \n";

		// Create a window
		mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if window succesful..
		if (mainWindow != 0) {
			cout << "Window creation success \n";

			// create renderer
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

			// if renderer successful...
			if (mainRenderer != 0) {
				cout << "Renderer creation success \n";
				SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
			}
			else {
				cout << "renderer failed \n";
				return false;
			}
		}
		else {
			cout << "window failed \n";
			return false;
		}

	}
	else {
		cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	cout << "SDL init success \n";

	// Create rect for sky img
	sky.x = 0;
	sky.y = 0;
	sky.w = 680;
	sky.h = 480;

	// create rect for ground img
	ground.x = 0;
	ground.y = 300;
	ground.w = 680;
	ground.h = 180;

	// create rect for player
	playerRect.x = 50;
	playerRect.y = 300;
	playerRect.w = 100;
	playerRect.h = 100;

	// create rect for score
	gameoverRect.x = 50;
	gameoverRect.y = 100;
	gameoverRect.w = 400;
	gameoverRect.h = 100;

	// create rect for score
	scoreRect.x = 50;
	scoreRect.y = 200;
	scoreRect.w = 400;
	scoreRect.h = 100;

	// create texture for all imgs
	groundImage = IMG_LoadTexture(mainRenderer, "images/ground.png");
	yellowBeam = IMG_LoadTexture(mainRenderer, "images/yellowBeam.png");
	redBeam = IMG_LoadTexture(mainRenderer, "images/redBeam.png");
	blueBeam = IMG_LoadTexture(mainRenderer, "images/blueBeam.png");
	greenBeam = IMG_LoadTexture(mainRenderer, "images/greenBeam.png");
	whiteBeam = IMG_LoadTexture(mainRenderer, "images/whiteBeam.png");
	blackBeam = IMG_LoadTexture(mainRenderer, "images/blackBeam.png");
	skyImage = IMG_LoadTexture(mainRenderer, "images/sky.png");
	playerImage = IMG_LoadTexture(mainRenderer, "images/screaming.png");

	// init sdl_ttf
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	Font = TTF_OpenFont("LHANDW.TTF", 24); // set up font

	return true;
}

void Game::render()
{
	// set background color
	//SDL_SetRenderDrawColor(mainRenderer, 135, 206, 250, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// render sky
	SDL_RenderCopy(mainRenderer, skyImage, NULL, &sky);

	// render player
	SDL_RenderCopy(mainRenderer, playerImage, NULL, &playerRect);

	// draw to the screen here!
	// iterate through list of objects
	for (unsigned int a = 0; a < sizeof(wallList) / sizeof(wallList[0]); a = a + 1) {
		SDL_Rect currentRect = wallList[a]->getRect();
		std::string currentColour = wallList[a]->getColour();
		if (currentColour == "Yellow") {
			SDL_RenderCopy(mainRenderer, yellowBeam, NULL, &currentRect);
		}
		else if (currentColour == "Red") {
			SDL_RenderCopy(mainRenderer, redBeam, NULL, &currentRect);
		}
		else if (currentColour == "Blue") {
			SDL_RenderCopy(mainRenderer, blueBeam, NULL, &currentRect);
		}
		else if (currentColour == "Green") {
			SDL_RenderCopy(mainRenderer, greenBeam, NULL, &currentRect);
		}
		else if (currentColour == "White") {
			SDL_RenderCopy(mainRenderer, whiteBeam, NULL, &currentRect);
		}
		else if (currentColour == "Black") {
			SDL_RenderCopy(mainRenderer, blackBeam, NULL, &currentRect);
		}
	}

	if (!player->playerAlive)
	{
		gameoverTextRender();
	}

	// render ground
	SDL_RenderCopy(mainRenderer, groundImage, NULL, &ground);

	// render new frame
	SDL_RenderPresent(mainRenderer);
}

/*
* update - Process all variables !in charge of anything to do with rendering
*
*/
void Game::update()
{
	serialInterface->getValues(); // updates the light sensor values from the controller
	serialInterface->printValues(); // prints values for testing
	player->update(); // updates player

	for (unsigned int a = 0; a < sizeof(wallList) / sizeof(wallList[0]); a = a + 1) { // iterate through all walls
		if (wallList[a]->isWallActive()) // if wall is active move wall
		{
			handleWallBlocking(wallList[a]);
			wallList[a]->updateWall();
		}
	}
}

/*
* handleEvents - Poll Events and uses switch case to process specific events
*
*/
void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		default:
			break;
		}

	}
}

/*
* clean - Clean up SDL and close the port
*
*/
void Game::clean()
{	
	serialInterface->close();

	cout << "Cleaning SDL \n";
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}

void Game::handleWallBlocking(Wall * currentWall) // checks wall to see if it's blocked and changes the variable if it is or isn't
{
	if (player->playerAlive)
	{
		int red = serialInterface->getRedValue();
		int green = serialInterface->getGreenValue();
		int blue = serialInterface->getBlueValue();
		int yellow = serialInterface->getYellowValue();

		if ((red >= sensorBlockedValue) && (green >= sensorBlockedValue) && (blue >= sensorBlockedValue)
			&& (yellow >= sensorBlockedValue) && (currentWall->getColour() == "White")) // if all sensors blocked (White) and the wall is black
		{
			currentWall->turnIsBlockedOn();
		}
		else if ((red < sensorBlockedValue) && (green < sensorBlockedValue) && (blue < sensorBlockedValue)
			&& (yellow < sensorBlockedValue) && (currentWall->getColour() == "Black")) // if all sensors are not blocked (Black) and the wall is white
		{
			currentWall->turnIsBlockedOn();
		}
		else if ((red < sensorBlockedValue) && (green > sensorBlockedValue) && (blue > sensorBlockedValue)
			&& (yellow > sensorBlockedValue) && (currentWall->getColour() == "Red")) // if red sensor is blocked and the wall is red
		{
			currentWall->turnIsBlockedOn();
		}
		else if ((red > sensorBlockedValue) && (green < sensorBlockedValue) && (blue > sensorBlockedValue)
			&& (yellow > sensorBlockedValue) && (currentWall->getColour() == "Green")) // if green sensor is blocked and the wall is green
		{
			currentWall->turnIsBlockedOn();
		}
		else if ((red > sensorBlockedValue) && (green > sensorBlockedValue) && (blue < sensorBlockedValue)
			&& (yellow > sensorBlockedValue) && (currentWall->getColour() == "Blue")) // if blue sensor is blocked and the wall is blue
		{
			currentWall->turnIsBlockedOn();
		}
		else if ((red > sensorBlockedValue) && (green > sensorBlockedValue) && (blue > sensorBlockedValue)
			&& (yellow < sensorBlockedValue) && (currentWall->getColour() == "Yellow")) // if yellow sensor is blocked and the wall is yellow
		{
			currentWall->turnIsBlockedOn();
		}
		else
		{
			currentWall->turnIsBlockedOff();
		}
	}
}

Player * Game::getPlayer()
{
	return player;
}

void Game::gameoverTextRender()
{
	int playerScore = player->getScore(); // gets player score
	string stringPlayerScore = "Your Score: " + std::to_string(playerScore); // changes int to string and adds some text
	char const * charPlayerScore = stringPlayerScore.c_str(); // changes string to char to work with the SDL tff
	SDL_Color Black = { 0, 0, 0 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, charPlayerScore, Black);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(mainRenderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderCopy(mainRenderer, Message, NULL, &scoreRect);
	SDL_DestroyTexture(Message);
	surfaceMessage = TTF_RenderText_Solid(Font, "Gameover!", Black);
	Message = SDL_CreateTextureFromSurface(mainRenderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderCopy(mainRenderer, Message, NULL, &gameoverRect);
	SDL_DestroyTexture(Message);
}



