#include "../inc/Engine.h"

Engine::Engine(void) {
	logfile = stderr;
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;
	centerX = screenWidth/2;
	centerY = screenHeight/2;
	screenBpp = SCREEN_BPP;
	windowCaption = "Generic Title";
	running = false;
	character = NULL;
	level = NULL;
	sprites = NULL;
	frameCount = 0;
}

Engine::~Engine(void) {
	CoreUtility::clearPtr(sprites);
	CoreUtility::clearPtr(character);
	CoreUtility::clearPtr(level);
	CoreUtility::clearPtr(characterSprite);
	SDL_Quit();
}

void Engine::setScreenExtents(CORE_INT width, CORE_INT height) {
	screenWidth = width;
	screenHeight = height;
}

void Engine::setWindowCaption(std::string caption) {
	windowCaption = caption;
}

void Engine::updateFPSCaption(void) {
	if(update.get_ticks() > 1000) {
		CORE_FLOAT fpsCalc = frameCount / ( fps.get_ticks() / 1000.f );
		fprintf(logfile, "FPS: %05.2f\n", fpsCalc);
		update.start();
	}
}

CORE_STATUS Engine::init_SDL(void) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(logfile, "Error initializing SDL");
		return CORE_ERR;
	}

	screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBpp, SDL_HWSURFACE);
	if(!screen) {
		fprintf(logfile, "Error initializing screen");
		return CORE_ERR;
	}

	CORE_INT flags = IMG_INIT_JPG | IMG_INIT_PNG;
	CORE_INT initted = IMG_Init(flags);
	if( (initted & flags) != flags) {
		fprintf(logfile, "Could not init SDL_Image");
		return CORE_ERR;
	}

	
	SDL_WM_SetCaption(windowCaption.c_str(), NULL);

	return CORE_SUCCESS;
}

CORE_STATUS Engine::init(void) {
	if(CoreUtility::failed(init_SDL())) {
		fprintf(logfile, "Error initializing SDL");
		return CORE_ERR;
	}

	sprites = new SpriteSheet(this, "assets/sprites/dirt.png");
	characterSprite = new SpriteSheet(this, "assets/sprites/character2.png");

	character = new Character(characterSprite, "alex");

	level = new LevelScroller(sprites);

#if SCROLLERDEBUG == 1
		SDL_Rect extents = {centerX - 80, centerY - 80, 160, 160};
		level->setVisibleExtents(extents);
#else
		SDL_Rect extents = {0, 0, screenWidth, screenHeight};
		level->setVisibleExtents(extents);
#endif

	character->moveTo(centerX, centerY);
	
	running = true;
	return CORE_SUCCESS;
}

CORE_STATUS Engine::doEvents(void) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			running = false; 
		}
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
			case SDLK_ESCAPE:
				running = false;
				break;
			}
		}
		character->handleInput(&event);
	}
	return CORE_SUCCESS;
}

CORE_STATUS Engine::doPreframe(void) {
	CORE_INT preCharX = character->getX();
	CORE_INT preCharY = character->getY();
	character->move(frameDelta.get_ticks());
	CORE_INT charDiffX = character->getX() - preCharX;
	CORE_INT charDiffY = character->getY() - preCharY;
	if(level && (charDiffX != 0 || charDiffY != 0))
		level->pan(-charDiffX, -charDiffY);
	
	frameDelta.start();
	return CORE_SUCCESS;
}

CORE_STATUS Engine::doFrame(void) {
	
	SDL_PixelFormat* format = screen->format;
	
	SDL_FillRect(screen, NULL, SDL_MapRGB(format, 255, 255, 255));
	
	if(level) level->show(screen);
	if(character) character->show(screen);

	if(SDL_Flip(screen) == -1) {
		fprintf(logfile, "Error flipping screen");
		return CORE_ERR;
	}
	return CORE_SUCCESS;
}

CORE_STATUS Engine::run(void) {
	frameDelta.start();

	if(SDL_Flip(screen) < 0) {
		fprintf(logfile, "Error flipping screen");
		return CORE_ERR;
	}
	update.start();
	fps.start();
	while(running) {
		fpsLock.start();
		doEvents();
		doPreframe();
		doFrame();
		frameCount++;
		if ( fpsLock.get_ticks() < 1000 / FRAME_CAP ) {
			SDL_Delay( (1000/FRAME_CAP) - fpsLock.get_ticks() );
		}
		updateFPSCaption();
	}
	return CORE_SUCCESS;
}

// As needed by ISDLImageLoader
SDL_Surface* Engine::loadImage(std::string filename) {
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if(loadedImage) {
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

		SDL_FreeSurface(loadedImage);
	} else {
		fprintf(logfile, "Error loading image %s", filename.c_str());
	}
	return optimizedImage;
}