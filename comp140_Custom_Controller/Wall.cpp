#include "stdafx.h"
#include "Wall.h"
#include "Game.h"
#include "stdlib.h"


Wall::Wall()
{
	chooseColour(); // pick a random colour from the 6 options
	setRect(640, 0, 50, wallHeight);
	nextWallSpawn = rand() % 100 + difficulty; // get a number between 100 and current difficulty to spawn the next wall
	currentPlayer = game.getPlayer(); // bring the player into this file
}


Wall::~Wall()
{
}

/*
* Sets the wall colour value to a random one out of 6 options
*
*/
void Wall::chooseColour()
{
	// grab a random number between 1 and 4
	int decider = rand() % 6 + 1;

	if (decider == 1)
	{
		wallColour = "Yellow";
	}
	else if (decider == 2)
	{
		wallColour = "Red";
	}
	else if (decider == 3)
	{
		wallColour = "Green";
	}
	else if (decider == 4)
	{
		wallColour = "Blue";
	}
	else if (decider == 5)
	{
		wallColour = "White";
	}
	else if (decider == 6)
	{
		wallColour = "Black";
	}
}

/*
* returns wall colour
*
*/
std::string Wall::getColour()
{
	return wallColour;
}

/*
* updates wall positions and size if they are blocked or not
* checks the position, if over the player sets player dead
* activates the next wall once passed a randomly generated position
*/
void Wall::updateWall()
{
	if (wallActive && isBlocked) // if the input is blocked shorten the wall
	{
		wallHeight = 50;
	}
	else if (wallActive && !isBlocked) // if not blocked return wall to normal size
	{
		wallHeight = 480;
	}
	if (posX <= 130 && posX >= 20 && !isBlocked) // if the beam isn't blocked when crossing a certain point set player to dead
	{
		currentPlayer->setDead();
	}
	if (wallActive) 
	{
		int playerScore = currentPlayer->getScore();
		std::cout << playerScore << std::endl;
		posX = (posX - 1) - (playerScore / 500); // change to - playerscore later might need to be a float
		setRect(posX, 0, 50, wallHeight);
		if ((posX <= nextWallSpawn) && spawnActive)
		{
			activateNextWall(); // activates the next inactive wall in the array
			setSpawnActive(); // flips if this wall can activate a wall or not (to false)
		}
		if (posX < -55)
		{
			setWallActive(); // deactivate this wall
			posX = 680; // set position back to the start
			chooseColour(); // choose a new colour
			nextWallSpawn = rand() % 100 + difficulty;
			setSpawnActive(); //  flips if this wall can activate a wall or not (to true)
		}
	}
}

bool Wall::isWallActive()
{
	return wallActive;
}

void Wall::setWallActive()
{
	wallActive = !wallActive;
}

int Wall::getNextWallSpawn()
{
	return nextWallSpawn;
}

/*
* geos through the list of walls to find the first inactive wall and activates it
*
*/
void Wall::activateNextWall()
{
	for (unsigned int a = 0; a < sizeof(Game::wallList) / sizeof(Game::wallList[0]); a = a + 1)
	{
		if (game.wallList[a]->isWallActive() == false)
		{
			game.wallList[a]->setWallActive();
			break;
		}
	}
}

void Wall::setSpawnActive()
{
	spawnActive = !spawnActive;
}

void Wall::turnIsBlockedOn()
{
	isBlocked = true;
}

void Wall::turnIsBlockedOff()
{
	isBlocked = false;
}

/*
* raises the difficulty once hitting ceratin score values meaning walls can spawn closer together
*
*/
void Wall::increaseDifficulty()
{
	if (currentPlayer->getScore() <= 5000)
	{
		difficulty = 500;
	}
	else if (currentPlayer->getScore() <= 2500)
	{
		difficulty = 400;
	}
}
