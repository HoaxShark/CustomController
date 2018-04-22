#pragma once
#include "Object.h"
#include "Player.h"
#include <cstdlib>


class Wall :
	public Object
{
public:
	Wall();
	~Wall();
	bool isBlocked = false;

	bool wallActive = false;

	bool spawnActive = true;

	int posX = 680;

	int nextWallSpawn;

	int wallHeight = 480;

	std::string wallColour;

	// set wallColour to a random colour
	void chooseColour();

	std::string getColour();

	void updateWall();

	bool isWallActive();

	void setWallActive();

	int getNextWallSpawn();

	void activateNextWall();

	void setSpawnActive();

	void turnIsBlockedOn();

	void turnIsBlockedOff();

	Player * currentPlayer;

	int difficulty = 300;

	void increaseDifficulty();
};

