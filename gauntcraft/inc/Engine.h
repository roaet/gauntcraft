#ifndef class_sdlgauntcraft
#define class_sdlgauntcraft
#include <cstdio>
#include <string>

#include "Character.h"
#include "ClientCore.h"
#include "SpriteSheet.h"
#include "ISDLImageLoader.h"
#include "Timer.h"
#include "LevelScroller.h"
#include "LevelScroller.h"
#include "MouseShooter.h"
#include "KeyboardHandler.h"
#include "InputStack.h"

const CORE_INT SCREEN_WIDTH = 640;
const CORE_INT SCREEN_HEIGHT = 480;
const CORE_INT SCREEN_BPP = 32;
const CORE_INT FRAME_CAP = 150;
namespace gauntcraft {
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
		gauntcraft::SpriteSheet* sprites;
		gauntcraft::SpriteSheet* characterSprite;
		Character * player;
		gauntcraft::Timer frameDelta;

		LevelScroller* level;
		KeyboardHandler keys;

		// FPS stuff
		CORE_INT frameCount;
		gauntcraft::Timer fps;
		gauntcraft::Timer fpsLock;
		gauntcraft::Timer update;

		MouseShooter mouseShooter;

	public:
		Engine(void);
		virtual ~Engine(void);

		void setScreenExtents(CORE_INT width, CORE_INT height);
		void setWindowCaption(std::string caption);

		CORE_STATUS init(void);
		CORE_STATUS run(void);

		virtual SDL_Surface* loadImage(std::string filename);
	};
}
#endif