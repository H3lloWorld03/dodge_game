#ifndef BULLET1_H
#define BULLET1_H
#include"Common.h"
class Bullet1
{
public:
	SDL_FRect Box;
	float xVel, yVel;
	bool exist = false;
	Bullet1(float w, float h);
	void moving();
	//void show();



};
#endif 

