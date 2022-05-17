#include"Enemy4.h"

Bullet2::Bullet2(float w, float h)
{

	exist = true;
	Box.w = w;
	Box.h = h;

}

void Bullet2::moving()
{


	Box.x += xVel;
	Box.y += yVel;
	if ((Box.x < 0) || (Box.x > SCREEN_WIDTH))
	{
		exist = false;
	}
	if ((Box.y < 0) || (Box.y > SCREEN_HEIGHT))
	{
		exist = false;
	}
}
