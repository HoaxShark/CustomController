#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::setRect(int posX, int posY, int width, int height)
{
	objectRect;
	objectRect.x = posX;
	objectRect.y = posY;
	objectRect.w = width;
	objectRect.h = height;
}

SDL_Rect Object::getRect()
{
	return objectRect;
}


