#ifndef BUTTON_H
#define BUTTON_H
#include"Common.h"

class Button
{
public:
	SDL_FRect B;
	Button();
	void Handle(SDL_Event* e);
	bool exist = false;

};
#endif // !BUTTON_H

