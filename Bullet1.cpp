#include"Bullet1.h"

Bullet1::Bullet1(float w, float h)
{
	
	exist = true;
	Box.w = w;
	Box.h = h;

}
void Bullet1::moving()
{
	
		if (exist == false) return;
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