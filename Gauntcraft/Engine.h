#ifndef class_sdlgauntcraft
#define class_sdlgauntcraft
#include <cstdio>
#include <string>

#include "Character.h"
#include "CoreUtility.h"
#include "CoreTypes.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SpriteSheet.h"
#include "ISDLImageLoader.h"
#include "Timer.h"
#include "ILevelScroller.h"
#include "LevelScroller.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

class Engine : public ISDLImageLoader {
private:
	CORE_STATUS doEvents(void);
	CORE_STATUS doPreframe(void);
	CORE_STATUS doFrame(void);
	CORE_STATUS init_SDL(void);
	void updateFPSCaption(void);

	CORE_INT screenWidth, screenHeight, screenBpp;
	CORE_INT centerX, centerY;
	CORE_BOOL running;

	std::string windowCaption;
	SDL_Surface* screen;
	FILE* logfile;
	SpriteSheet* sprites;
	SpriteSheet* characterSprite;
	Character * character;
	Timer frameDelta;

	ILevelScroller* level;

	// FPS stuff
	CORE_INT frameCount;
	Timer fps;
	Timer update;


public:
	Engine(void);
	virtual ~Engine(void);

	void setScreenExtents(CORE_INT width, CORE_INT height);
	void setWindowCaption(std::string caption);

	CORE_STATUS init(void);
	CORE_STATUS run(void);

	virtual SDL_Surface* loadImage(std::string filename);
};
#endif