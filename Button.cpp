#include"Button.h"

Button::Button()
{
	alive = true;
	B.x = 125;
	B.y = 337;
	B.w = 300;
	B.h = 125;

}

void Button::Handle(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < B.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > B.x + B.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < B.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > B.y + B.h)
		{
			inside = false;
		}
		if (inside == true)
		{
			alive = false;
		}
	}
	//Mouse is outside button

}