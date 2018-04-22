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

	void update();
	int getScore();

};

