#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>


class Object
{
public:
	Object();
	~Object();

	// variable for the objects rectangle
	SDL_Rect objectRect;

	// set the position and size of the rect
	void setRect(int posX, int posY, int width, int height);

	// return rects values
	SDL_Rect getRect();

	

};

