#ifndef BULLET4_H
#define BULLET4_H
#include "Common.h"

class Bullet2
{
public:
	SDL_FRect Box;
	float xVel, yVel;
	bool exist = false;
	Bullet2(float w, float h);
	void moving();
	//void show4();

};

#endif

