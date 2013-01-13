#ifndef class_sdlgauntcraft_spriteextent
#define class_sdlgauntcraft_spriteextent

#include "CoreTypes.h"
#include "SDL/SDL.h"
#include <cstdlib>

class SpriteExtent {
private:
	CORE_INT random_horizontal_frames;
	CORE_INT frames;
	CORE_INT idleFrame;
	SDL_Rect clipRect;
public:
	SpriteExtent(CORE_INT x, CORE_INT y, CORE_UINT w, CORE_UINT h);
	void setRandom(CORE_INT);
	void setFrames(CORE_INT);
	void setIdleFrame(CORE_INT);
	SDL_Rect getRect();
	SDL_Rect getRect(CORE_INT);
};

#endif //class_sdlgauntcraft_spriteextent
