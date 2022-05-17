#include"Again.h"

Again::Again()
{
	exist = false;
	Bm.x = 125;
	Bm.y = 337+150;
	Bm.w = 300;
	Bm.h = 84;

}

void Again::HandleE(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		
		int x, y;
		SDL_GetMouseState(&x, &y);
	
		bool inside = true;

		if (x < Bm.x)
		{
			inside = false;
		}
	
		else if (x > Bm.x + Bm.w)
		{
			inside = false;
		}
	
		else if (y < Bm.y)
		{
			inside = false;
		}
	
		else if (y > Bm.y + Bm.h)
		{
			inside = false;
		}
		if (inside == true)
		{
			exist = false;
		}

	}
}