#include "stdafx.h"
#include "Player.h"
#include "stdlib.h"


Player::Player()
{
	score = 0;
	lives = 1;
	playerAlive = true;
}


Player::~Player()
{
}

void Player::update()
{
	if (playerAlive) {
		score = score + 1;
	}
}

int Player::getScore()
{
	return score;
}

void Player::setDead()
{
	playerAlive = false;
}

