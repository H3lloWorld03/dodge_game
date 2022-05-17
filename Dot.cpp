#include"Dot.h"
#include"Common.h"

Dot::Dot()
{

	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2;

	
	mVelX = 0;
	mVelY = 0;

	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;
}

void Dot::handleEvent(SDL_Event& e)
{
	
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
	
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: mVelY += DOT_VEL; break;
		case SDLK_LEFT: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}

	}
}

void Dot::move()
{

	mPosX += mVelX;
	mCollider.x = mPosX;

	if ((mPosX < 0 + 10) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
	{
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}

	mPosY += mVelY;
	mCollider.y = mPosY;
	if ((mPosY < 0 + 10) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}