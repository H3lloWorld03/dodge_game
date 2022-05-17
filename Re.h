#ifndef RE_H
#define RE_H

#include"Common.h"

class Re
{
public:
	SDL_FRect Bm;
	Re();
	bool exist = false;
	void HandleR(SDL_Event* e);
};

#endif // !RE_H

