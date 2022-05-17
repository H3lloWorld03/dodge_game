#include"Gas.h"

Gas::Gas(float w, float h)
{

	exist = true;
	B.w = w;
	B.h = h;

}
void Gas::moving()
{
	B.x += Xvel;
	B.y += Yvel;
	if ((B.x < 0) || (B.x > SCREEN_WIDTH))
	{
		exist = false;
	}
	if ((B.y < 0) || (B.y > SCREEN_HEIGHT))
	{
		exist = false;
	}
}
