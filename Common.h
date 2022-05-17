#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include <stdio.h>
#include <string>
#include<vector>
#include <ctime>
#include <sstream>
#include<cmath>
#include<algorithm>
#include<math.h>
#include<SDL_mixer.h>
#include <SDL_rect.h>



//Screen dimension constants
const int SCREEN_WIDTH = 546;
const int SCREEN_HEIGHT = 780;
const int ENEMY_HEIGHT = 10;
const int ENEMY_WIDTH = 10;
const int ENEMY2_HEIGHT = 20;
const int ENEMY2_WIDTH = 20;
const int ENEMY3_HEIGHT = 151;
const int ENEMY3_WIDTH = 150;
static SDL_Surface* enemy = NULL;



const int WALKING_ANIMATION_FRAMES = 4;
const int WALKING_ANIMATION_FRAMES_2 = 2;
const int WALKING_ANIMATION_FRAMES_3 = 20;




#endif // !COMMON_H

