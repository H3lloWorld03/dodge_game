#ifndef DOT_H
#define DOT_H
#include<SDL_image.h>
class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 18;

	//Maximum axis velocity of the dot
	const float DOT_VEL = 4;

	SDL_FRect mCollider;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	//void render();

	bool exist = true;

	//The X and Y offsets of the dot
	float mPosX, mPosY;
	//The velocity of the dot
	int mVelX, mVelY;
	//Dot's collision box
	//Dot's collision box
};

#endif // !DOT_H

