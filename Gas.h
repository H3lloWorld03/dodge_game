#ifndef ENEMY0_H
#define ENEMY0_H

#include"Common.h"


class Gas
{
public:
	SDL_FRect B;
	long float Xvel, Yvel;
	bool exist = false;
	Gas(float w, float h);
	void moving();
	//void show();

};

#endif // !ENEMY0_H
