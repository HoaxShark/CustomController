#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

/*
* creates the rect for a new object
*
*/
void Object::setRect(int posX, int posY, int width, int height)
{
	objectRect;
	objectRect.x = posX;
	objectRect.y = posY;
	objectRect.w = width;
	objectRect.h = height;
}

/*
* returns rect values of object
*
*/
SDL_Rect Object::getRect()
{
	return objectRect;
}


