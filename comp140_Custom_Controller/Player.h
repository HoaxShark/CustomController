#pragma once
#include "Object.h"
#include <cstdlib>


class Player :
	public Object
{
public:
	Player();
	~Player();

	int score;
	bool playerAlive;
	int lives;

	void update();
	int getScore();
	void setDead();

};

