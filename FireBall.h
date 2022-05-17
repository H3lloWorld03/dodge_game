#ifndef FIREBALL_H
#define FIREBALL_H
#include"Common.h"

class FireBall
{
public:
	SDL_FRect B;
	long float Xvel, Yvel;
	bool exist = false;
	FireBall(float w, float h);
	void moving();
	//void show();

};


#endif

