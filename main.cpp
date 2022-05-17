
#include"Dot.h"
#include"Bullet1.h"
#include"FireBall.h"
#include"Bullet4.h"
#include"Button.h"
#include"Again.h"
#include"Gas.h"
#include"Re.h"

bool init();


bool loadMedia();


SDL_Texture* loadTexture(std::string path);

int main(int argc, char* args[]);


void close();

SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gSpriteClips2[WALKING_ANIMATION_FRAMES_2];
SDL_Rect gSpriteClips3[WALKING_ANIMATION_FRAMES_3];

 Mix_Music* bgsound = NULL;
 Mix_Chunk* exsound = NULL;


 SDL_Window* gWindow = NULL;

 SDL_Renderer* gRenderer = NULL;

 SDL_Texture* gTexture = NULL;

 TTF_Font* gFont = NULL;


 //lazyfoo
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	//Loads image at specified path
	bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(float x, float y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

LTexture ButtonTexture;
//Scene textures
LTexture gDotTexture;
LTexture gBoomTexture;
LTexture gBullet1Texture;
LTexture gFireBallTexture;
LTexture gBullet2Texture;
LTexture gBGTexture;
LTexture gSpriteSheetTexture;
//Scene textures
LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;
LTexture gReTexture;
LTexture gAgainTexture;
LTexture gGasTexture;
LTexture gBossTexure;
LTexture gText;
LTexture gText2;
LTexture Pauset;
LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}
void LTexture::render(float x, float y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}

#endif



class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};
LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool LTimer::isPaused()
{

	//Timer is running and paused
	return mPaused && mStarted;
}





void spawn0(std::vector<Gas>& v)
{
	const int delay = 500;
	static int start = 0;

	int a = rand() % 3;
	
	if (a == 0)
	{
		if (++start >= delay)// time to spawn
		{
			for (long float i = 0; i < v.size(); i++)
			{
				if (v[i].exist == false)
				{
					v[i].B.y = 50;
					v[i].B.x = (SCREEN_WIDTH - v[i].B.w) / 2;
					v[i].Xvel = i - 2;
					v[i].Yvel = 3;
					v[i].exist = true;

				}
				start = 0;// reset for next time
			}
		}
	}
	if (a == 1)
	{
		if (++start >= delay)// time to spawn
		{
			for (long float i = 0; i < v.size(); i++)
			{
				if (v[i].exist == false)
				{
					v[i].B.y = 50;
					v[i].B.x = (SCREEN_WIDTH - v[i].B.w) / 2;
					
					v[i].Xvel = (i+1)/v.size();
					v[i].Yvel = 3;
					v[i].exist = true;

				}
				start = 0;
			}
		}
	}
	if (a == 2)
	{
		if (++start >= delay)
		{
			for (long float i = 0; i < v.size(); i++)
			{
				if (v[i].exist == false)
				{
					v[i].B.y = 50;
					v[i].B.x = (SCREEN_WIDTH - v[i].B.w) / 2;
					v[i].Xvel = -(i + 1) / v.size();
					v[i].Yvel = 3;
					v[i].exist = true;

				}
				start = 0;
			}
		}
	}
	
}


void showRe(Re r)
{
	if (r.exist == true) gReTexture.render(r.Bm.x, r.Bm.y);

}

void render0(Gas a)
{
	if (a.exist == true) gGasTexture.render(a.B.x, a.B.y);

	
}
void showAgain(Again a)
{
	if (a.exist == true) gAgainTexture.render(a.Bm.x, a.Bm.y);
}


void showbutton(Button a)
{
	if (a.exist == true)	ButtonTexture.render(a.B.x, a.B.y);
	

}



void render(Dot dot)
{
	
	if (dot.exist == true) gDotTexture.render(dot.mPosX, dot.mPosY);
	

}



void render2(FireBall a)
{
	if (a.exist == true)	gFireBallTexture.render(a.B.x, a.B.y);

	
}

void render1(Bullet1 a)
{

	if (a.exist == true)	gBullet1Texture.render(a.Box.x, a.Box.y, NULL, 57.2957795 * acos(a.xVel / sqrt(a.xVel * a.xVel + a.yVel * a.yVel)));

	
}

void render4(Bullet2 e)
{

	if (e.exist == true)	gBullet2Texture.render(e.Box.x, e.Box.y, NULL, -57.2957795 * acos((e.xVel) / (sqrt(e.xVel * e.xVel + e.yVel * e.yVel))));

	
}


void spawn1(std::vector<Bullet1>& eVec,Dot dot)
{
	const float delay = 8;
	static float start = 0;
	
	if (++start >= delay)
	{
		for (unsigned i = 0; i < eVec.size(); ++i)
		{

			if (eVec[i].exist == false)
			{

				eVec[i].Box.y = 0;
				eVec[i].Box.x = (rand() % (int)SCREEN_WIDTH + 0);

				float a = sqrt((dot.mPosX - eVec[i].Box.x) * (dot.mPosX - eVec[i].Box.x) + (dot.mPosY - eVec[i].Box.y) * (dot.mPosY - eVec[i].Box.y));

				eVec[i].xVel = 4 * (dot.mPosX - eVec[i].Box.x) / a;
				eVec[i].yVel = 4 * (dot.mPosY - eVec[i].Box.y) / a;					
				eVec[i].exist = true;
				break;


			}
			start = 0;
		}
	}
}


void spawn2(std::vector<FireBall>& v )
{
	const int delay = 205;
	static int start = 0;
	
	int a = rand() % 5;
	if (a == 0)
	{
		if (++start >= delay)// time to spawn
		{

			for (long float i = 0; i < v.size(); i++)
			{
				if (v[i].exist == false)
				{
					v[i].B.y = 0;
					v[i].B.x = 0;
					v[i].Xvel = 5 * i / (v.size()-1);
					v[i].Yvel = 5 * sqrt(1 - v[i].Xvel * v[i].Xvel / 25);
					
					v[i].exist = true;

				}
				start = 0;

			}

		}
		
	}
	else if (a == 1)
	{
		if (++start >= delay)
		{

			for (long float i = 0; i < v.size(); i++)
			{
				
				if (v[i].exist == false)
				{
					v[i].B.y = SCREEN_HEIGHT;
					v[i].B.x = 0;
					v[i].Xvel = -5 * i / (v.size() - 1);
					v[i].Yvel = 5 * sqrt(1 - v[i].Xvel * v[i].Xvel / 25);					
					v[i].exist = true;

				}
				start = 0;
			}

		}

	}
	else if (a == 2)
	{
		if (++start >= delay)
		{

			for (long float i = 0; i < v.size(); i++)
			{

				if (v[i].exist == false)
				{
					v[i].B.y = SCREEN_HEIGHT-1;
					v[i].B.x = SCREEN_WIDTH-1;
					v[i].Xvel = -5 * i / (v.size() - 1);
					v[i].Yvel = -5 * sqrt(1 - v[i].Xvel * v[i].Xvel / 25);
					v[i].exist = true;
				}
				start = 0;

			}

		}

	}
	else if (a == 3)
	{
		if (++start >= delay)
		{

			for (long float i = 0; i < v.size(); i++)
			{

				if (v[i].exist == false)
				{
					v[i].B.y = 0;
					v[i].B.x = SCREEN_WIDTH;
					v[i].Xvel = 5 * i / (v.size() - 1);
					v[i].Yvel = -5 * sqrt(1 - v[i].Xvel * v[i].Xvel / 25);
					v[i].exist = true;

				} //+10
				start = 0;

			}

		}

	}
	else if (a == 4)
	{
		if (++start >= delay) {
			for (long float i = 0; i < v.size(); i++)
			{
				if (v[i].exist == false)
				{
					v[i].B.y = i * (800 / (v.size() - 1));
					v[i].B.x = SCREEN_WIDTH;
					v[i].Xvel = -4;
					v[i].Yvel = 0;
					v[i].exist = true;

				}
				start = 0;

			}
		}


	}
	else if (a == 5)
	{
		if (++start >= delay) {
			for (long float i = 0; i < v.size(); i++)
			{
				if (v[i].exist == false)
				{
					v[i].B.y = i * (800 / (v.size() - 1));
					v[i].B.x = 0;
					v[i].Xvel = 4;
					v[i].Yvel = 0;
					v[i].exist = true;
				}
				start = 0;
			}

		}
	}

}



void spawn4(std::vector<Bullet2>& v, Dot dot)
{
	dot.move();
	const float delay = 8;
	static float start = 0;
	if (++start >= delay)
	{
		for (unsigned i = 0; i < v.size(); ++i)
		{

			if (v[i].exist == false)
			{
				v[i].Box.y = SCREEN_HEIGHT;
				v[i].Box.x = rand() % (int)SCREEN_WIDTH + 0;
				float a = sqrt((dot.mPosX - v[i].Box.x) * (dot.mPosX - v[i].Box.x) + (dot.mPosY - v[i].Box.y) * (dot.mPosY - v[i].Box.y));
				v[i].xVel = 4 * (dot.mPosX - v[i].Box.x) / a;
				v[i].yVel = 4 * (dot.mPosY - v[i].Box.y) / a;
				v[i].exist = true;
				break;


			}
			start = 0;
		}
	}
}

bool init()
{
	//Initialization flag;
	bool success = true;
	//Initialize SDL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Ez", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia()
{


	bool success = true;
	if (!gReTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/play1.png")) 
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	if (!gDotTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/ship.png")) // space ship
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gAgainTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/exit.png")) 
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	gTexture = loadTexture("C:/dev/SDLpn/SDLpn/Image/baa.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	if (!gGasTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/blueball.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gBullet1Texture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/bullet.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gFireBallTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/thienthach.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	
	if (!gBullet2Texture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/bullet.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	if (!ButtonTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/play.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	if (!gSpriteSheetTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/explotion.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{

		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 20;
		gSpriteClips[0].w = 95;
		gSpriteClips[0].h = 95;

		gSpriteClips[1].x = 135;
		gSpriteClips[1].y = 15;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 105;

		gSpriteClips[2].x = 265;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 125;
		gSpriteClips[2].h = 135;

		gSpriteClips[3].x = 410;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 135;
		gSpriteClips[3].h = 135;
	}

	if (!gBGTexture.loadFromFile("C:/dev/SDLpn/SDLpn/Image/uni.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	if (!gBossTexure.loadFromFile("C:/dev/SDLpn/SDLpn/Image/Boss.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
	
		gSpriteClips2[0].x = 0;
		gSpriteClips2[0].y = 86;
		gSpriteClips2[0].w = 319;
		gSpriteClips2[0].h = 86;

		gSpriteClips2[1].x = 0;
		gSpriteClips2[1].y = 0;
		gSpriteClips2[1].w = 319;
		gSpriteClips2[1].h = 173;

		
	}

	gFont = TTF_OpenFont("C:/dev/SDLpn/SDLpn/Image/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
	
		SDL_Color textColor = { 255, 255, 255, 0 };

		if (!gStartPromptTexture.loadFromRenderedText(" ", textColor))
		{
			printf("Unable to render start/stop prompt texture!\n");
			success = false;
		}

		
		if (!gPausePromptTexture.loadFromRenderedText(" ", textColor))
		{
			printf("Unable to render pause/unpause prompt texture!\n");
			success = false;
		}
	}


	bgsound = Mix_LoadMUS("C:/dev/SDLpn/SDLpn/sound/bgsound.wav");
	if (bgsound == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	exsound = Mix_LoadWAV("C:/dev/SDLpn/SDLpn/sound/explotion.wav");
	if (exsound == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

void close()
{

	gDotTexture.free();
	gBGTexture.free();
	ButtonTexture.free();
	gBossTexure.free();
	gGasTexture.free();
	Mix_FreeChunk(exsound);
	exsound = NULL;
	gAgainTexture.free();
	Pauset.free();
	//music
	Mix_FreeMusic(bgsound);
	bgsound = NULL;


	gText.free();
	gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();


	TTF_CloseFont(gFont);
	gFont = NULL;


	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
	
	gBullet1Texture.free();
	gFireBallTexture.free();
	gBullet2Texture.free();

		
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}


bool check_collision(SDL_Rect a, SDL_Rect b)
{
	
	if (a.x + a.w < b.x) return false;
	if (a.x > b.x + b.w) return false;

	if (a.y + a.h < b.y) return false;
	if (a.y > b.y + b.h) return false;


	return true;
}
bool check_collision2(SDL_FRect a, SDL_FRect b)
{

	if (a.x + a.w < b.x) return false;
	if (a.x > b.x + b.w) return false;

	if (a.y + a.h < b.y) return false;
	if (a.y > b.y + b.h) return false;

	
	return true;
}



int main(int argc, char* args[])
{
	srand((int)time(NULL));
	float i = 0;
	unsigned int j = 0;
	int k;
	k = 6;
	bool check = true;
	bool moving = true;
	bool run = true;
	bool spawn = true;
	int kk = 9;
	int a = rand() % 5;
	int d = 0;
	
	if (d == 0)
	{
		if (!init())
		{
			printf("Failed to initialize!\n");
		}
		else
		{

			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{

			
				bool quit = false;

			
				SDL_Event e;

				Dot dot;

				Button button;

				Again ag;

			
				SDL_Color textColor = { 0, 255, 255, 0 };

			
				Uint32 startTime = 0;

			
				std::stringstream timeText;

				std::stringstream Text;

				std::stringstream TextCon;

				std::stringstream pausetext;

				//int frame2 = 0;
				int frame2 = 0;

				LTimer timer;

			
				int frame = 0;

				
				float scrollingOffset = SCREEN_HEIGHT;

				std::vector<Bullet1> bullet1(k, Bullet1(20, 20));
				std::vector<FireBall> fireball(kk, FireBall(10, 10));
				std::vector<Bullet2> bullet2(k, Bullet2(20, 20));
				std::vector<Gas> gas(5, Gas(75, 75));
				if (Mix_PlayingMusic() == 0)
				{
			
					Mix_PlayMusic(bgsound, -1);
				}
			
				else
				{
		
					if (Mix_PausedMusic() == 1)
					{
				
						Mix_ResumeMusic();
					}
					
					else
					{
					
						Mix_PauseMusic();
					}
				}
				while (!quit)
				{
					
					while (SDL_PollEvent(&e) != 0)
					{
						
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						if ((e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) && check == true)
						{
							timer.start();
							check = false;
						}
						else if (e.type == SDL_KEYDOWN)
						{
						
							if (e.key.keysym.sym == SDLK_ESCAPE && dot.exist == true)
							{
								timer.pause();

								moving = false;

							}
							else if (e.key.keysym.sym == SDLK_SPACE && dot.exist == true)
							{
								timer.unpause();
								ag.exist = false;
								moving = true;
							}
							else if (e.key.keysym.sym == SDLK_r && dot.exist == false)
							{
								dot.exist = true;
								ag.exist = false;
								for (i = 0; i < bullet1.size(); ++i) bullet1[i].exist = false;
								for (i = 0; i < fireball.size(); ++i) fireball[i].exist = false;
								for (i = 0; i < bullet2.size(); ++i) bullet2[i].exist = false;
								for (i = 0; i < gas.size(); ++i) gas[i].exist = false;
								timer.start();
								dot.mPosX = SCREEN_WIDTH / 2;
								dot.mPosY = SCREEN_HEIGHT / 2;
								continue;
							}


						}
					
						dot.handleEvent(e);
						button.Handle(&e);
						ag.HandleE(&e);
					
					}

					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					scrollingOffset -= 0.4;
					if (scrollingOffset + SCREEN_HEIGHT < +gBGTexture.getHeight())
					{
						scrollingOffset = SCREEN_HEIGHT;
					}

					
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

				
					gBGTexture.render(0, -scrollingOffset);
					gBGTexture.render(0, -scrollingOffset + gBGTexture.getHeight());

					showbutton(button);

					if (button.exist == false) //&& ag.exist == false)
					{
						if (run)
						{
							if (spawn)
							{
								spawn2(fireball);
								spawn1(bullet1, dot);
								spawn4(bullet2, dot);
								spawn0(gas);
							}

							if (moving == true)
							{
						
								dot.move();
								for (i = 0; i < bullet1.size(); ++i) bullet1[i].moving();
								for (i = 0; i < fireball.size(); ++i) fireball[i].moving();
								for (i = 0; i < bullet2.size(); ++i) bullet2[i].moving();
								for (i = 0; i < gas.size(); ++i) gas[i].moving();
							}
							else {
								pausetext.str("SPACE to continue");
								if (!Pauset.loadFromRenderedText(pausetext.str().c_str(), textColor))
								{
									printf("Unable to render time texture!\n");
								}
								Pauset.render(135, 350);
							}

						
							gStartPromptTexture.render((SCREEN_WIDTH - gStartPromptTexture.getWidth()) / 2, 0);
							gPausePromptTexture.render((SCREEN_WIDTH - gPausePromptTexture.getWidth()) / 2, gStartPromptTexture.getHeight());
							
							SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

							render(dot);

							for (i = 0; i < gas.size(); ++i)
							{
								if (gas[i].exist == true)
								{
									SDL_Rect* B = &gSpriteClips2[frame2 /450];
									gBossTexure.render((SCREEN_WIDTH - B->w) / 2, 0, B);

									++frame2;
									if (frame2 / 450 >= 2)
									{
										frame2 = 0;
									}
								}
							}
							for (i = 0; i < bullet1.size(); ++i)
							{
								render1(bullet1[i]);
							}
							for (i = 0; i < fireball.size(); i++)
							{

								render2(fireball[i]);

							}
							for (i = 0; i < bullet2.size(); ++i)
							{
								render4(bullet2[i]);

							}
							for (i = 0; i < gas.size(); ++i)
							{
								render0(gas[i]);

							}
						}

						if (dot.exist)
						{
							timeText.str("");
							timeText << (timer.getTicks());
					
							if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
							{
								printf("Unable to render time texture!\n");
							}
							gTimeTextTexture.render(0, 20);
							for (i = 0; i < gas.size(); ++i)
							{
								
								if (gas[i].exist && check_collision2(dot.mCollider, gas[i].B))
								{
									dot.exist = false;
									gas[i].exist = false;

								
									SDL_Rect* currentClip = &gSpriteClips[frame / 1]; //(SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip
									gSpriteSheetTexture.render(dot.mPosX - 35, dot.mPosY - 35, currentClip);

							
									SDL_RenderPresent(gRenderer);

								
									++frame;

								
									if (frame / 1 >= WALKING_ANIMATION_FRAMES)
									{
										frame = 0;
									}
									Mix_PlayChannel(-1, exsound, 0);

									
								}
							}

							for (i = 0; i < bullet1.size(); ++i)
							{
								for (j = 0; j < gas.size(); ++j)
								{
									if (bullet1[i].exist && check_collision2(dot.mCollider, bullet1[i].Box))
									{
										dot.exist = false;
										bullet1[i].exist = false;

						
										SDL_Rect* currentClip = &gSpriteClips[frame / 1];
										gSpriteSheetTexture.render(dot.mPosX - 35, dot.mPosY - 35, currentClip);

							
										SDL_RenderPresent(gRenderer);

									
										++frame;

							
										if (frame / 1 >= WALKING_ANIMATION_FRAMES)
										{
											frame = 0;
										}
										Mix_PlayChannel(-1, exsound, 0);

										
									}
									if (bullet1[i].exist && check_collision2(gas[j].B, bullet1[i].Box))
									{
										
										bullet1[i].exist = false;
										
									}
								}
								

							}
							for (i = 0; i < fireball.size(); ++i)
							{

								for (j = 0; j < gas.size(); ++j)
								{
									if (fireball[i].exist && check_collision2(dot.mCollider, fireball[i].B))
									{
										dot.exist = false;
										fireball[i].exist = false;
										
										SDL_Rect* currentClip = &gSpriteClips[frame / 1];
										gSpriteSheetTexture.render(dot.mPosX - 35, dot.mPosY - 35, currentClip);

										
										SDL_RenderPresent(gRenderer);

										++frame;

										if (frame / 1 >= WALKING_ANIMATION_FRAMES)
										{
											frame = 0;
										}
										Mix_PlayChannel(-1, exsound, 0);

										
									}
									if (fireball[i].exist && check_collision2(gas[j].B, fireball[i].B))
									{
										fireball[i].exist = false;
										
									}
								}
							}
							for (i = 0; i < bullet2.size(); ++i)
							{

								for (j = 0; j < gas.size(); ++j)
								{
									if (bullet2[i].exist && check_collision2(dot.mCollider, bullet2[i].Box))
									{
										dot.exist = false;
										bullet1[i].exist = false;


							
										SDL_Rect* currentClip = &gSpriteClips[frame / 1];
										gSpriteSheetTexture.render(dot.mPosX - 35, dot.mPosY - 35, currentClip);

								
										SDL_RenderPresent(gRenderer);

								
										++frame;

							
										if (frame / 1 >= WALKING_ANIMATION_FRAMES)
										{
											frame = 0;
										}
										Mix_PlayChannel(-1, exsound, 0);
										
									}
									if (bullet2[i].exist && check_collision2(gas[j].B, bullet2[i].Box))
									{
										bullet2[i].exist = false;
										
									}
								}
							}
							if (dot.exist == false)
							{
								timer.pause();
								ag.exist = true;
							}
						}
						showAgain(ag);
						if (button.exist == false && dot.exist == false)
						{
							Text.str("Press R to play again!") ;
							TextCon.str("YOUR SCORE");
							gText.render(110, 120);

							gTimeTextTexture.render(245, 350);

							gText2.render(200, 300);
							if (!gText.loadFromRenderedText(Text.str().c_str(), textColor))
							{
								printf("Unable to render time texture!\n");
							}
							if (!gText2.loadFromRenderedText(TextCon.str().c_str(), textColor))
							{
								printf("Unable to render time texture!\n");
							}
						}
						if (dot.exist == false && ag.exist == false)
						{
							break;
						}
						
					}
		
					SDL_RenderPresent(gRenderer);
				}
			}

		}
		
	}

	close();
	return 0;
}