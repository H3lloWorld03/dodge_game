#ifndef AGAIN_H
#define AGAIN_H
#include"Common.h"
class Again
{
public:
	SDL_FRect Bm;
	Again();
	bool exist = false;
	void HandleE(SDL_Event* e);

};

#endif // !AGAIN_H

