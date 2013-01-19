#include "../inc/Engine.h"
namespace gauntcraft {
	Engine::Engine(void) {
		logfile = stderr;
		screenWidth = SCREEN_WIDTH;
		screenHeight = SCREEN_HEIGHT;
		centerX = screenWidth/2;
		centerY = screenHeight/2;
		screenBpp = SCREEN_BPP;
		windowCaption = "Generic Title";
		running = false;
		player = NULL;
		level = NULL;
		sprites = NULL;
		frameCount = 0;
	}

	Engine::~Engine(void) {
		gauntcraftcore::GauntcraftCoreUtility::clearPtr(sprites);
		gauntcraftcore::GauntcraftCoreUtility::clearPtr(player);
		gauntcraftcore::GauntcraftCoreUtility::clearPtr(level);
		gauntcraftcore::GauntcraftCoreUtility::clearPtr(characterSprite);
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
			char buffer[255];
			sprintf(buffer,"%s (%f FPS)", windowCaption.c_str(), fpsCalc);
			SDL_WM_SetCaption(buffer, NULL);
			update.start();
		}
	}

	CORE_STATUS Engine::init_SDL(void) {
		CORELOG("Initializing SDL")
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			LOG(FATAL) << "Error initializing SDL";
			return CORE_ERR;
		}

		screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBpp, SDL_HWSURFACE);
		if(!screen) {
			LOG(FATAL) << "Error initializing screen";
			return CORE_ERR;
		}

		CORE_INT flags = IMG_INIT_JPG | IMG_INIT_PNG;
		CORE_INT initted = IMG_Init(flags);
		if( (initted & flags) != flags) {
			LOG(FATAL) << "Error initializing SDL_Image";
			return CORE_ERR;
		}

	
		SDL_WM_SetCaption(windowCaption.c_str(), NULL);

		return CORE_SUCCESS;
	}

	CORE_STATUS Engine::init(void) {
		if(gauntcraftcore::GauntcraftCoreUtility::failed(init_SDL())) {
			LOG(FATAL) << "Error during SDL initialization";
			return CORE_ERR;
		}

		sprites = new SpriteSheet(this, "assets/sprites/grass.png");
		characterSprite = new SpriteSheet(this, "assets/sprites/character2.png");

		player = new Character(characterSprite, "alex");

		level = new LevelScroller(sprites);
		level->setEntitySpriteSheet(new SpriteSheet(this, "assets/sprites/trunk.png"));
		level->setEntitySpriteSheet2(new SpriteSheet(this, "assets/sprites/treetop.png"));
		mouseShooter.registerTarget(level);

	#if SCROLLERDEBUG == 1
			SDL_Rect extents = {centerX - 80, centerY - 80, 160, 160};
			level->setVisibleExtents(extents);
	#else
			SDL_Rect extents = {0, 0, screenWidth, screenHeight};
			level->setVisibleExtents(extents);
	#endif

		player->moveTo(centerX, centerY);
	
		running = true;
		return CORE_SUCCESS;
	}

	CORE_STATUS Engine::doEvents(void) {
		SDL_Event event;
		SDL_PumpEvents();
		keys.getKeyState();
		if(keys.key_pressed(SDLK_ESCAPE)) {
			running = false;
		}
		player->targetScan(&keys);
		while(SDL_PollEvent(&event)) {
			//player->handleInput(&event);
			mouseShooter.shootMouse(&event);
		}
		return CORE_SUCCESS;
	}

	CORE_STATUS Engine::doPreframe(void) {
		CORE_INT preCharX = player->getX();
		CORE_INT preCharY = player->getY();
		player->move(frameDelta.get_ticks());
		CORE_INT charDiffX = player->getX() - preCharX;
		CORE_INT charDiffY = player->getY() - preCharY;
		if(level && (charDiffX != 0 || charDiffY != 0))
			level->pan(-charDiffX, -charDiffY);
	
		frameDelta.start();
		return CORE_SUCCESS;
	}

	CORE_STATUS Engine::doFrame(void) {
		SDL_PixelFormat* format = screen->format;
	
		SDL_FillRect(screen, NULL, SDL_MapRGB(format, 255, 255, 255));
	
		if(level) level->show(screen);
		if(player) player->show(screen);

		if(SDL_Flip(screen) == -1) {
			LOG(FATAL) << "Error flipping screen";
			return CORE_ERR;
		}
		return CORE_SUCCESS;
	}

	CORE_STATUS Engine::run(void) {
		frameDelta.start();

		if(SDL_Flip(screen) < 0) {
			LOG(FATAL) << "Error flipping screen";
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
			LOG(FATAL) << "Error loading image " << filename;
		}
		return optimizedImage;
	}
}