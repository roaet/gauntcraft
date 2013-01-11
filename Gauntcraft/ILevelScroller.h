#ifndef class_sdlgauntcraft_ilevelscroller
#define class_sdlgauntcraft_ilevelscroller

#include <string>

#include "CoreTypes.h"
#include "SDL.h"

class ILevelScroller {
public:
	virtual void pan(CORE_FLOAT x, CORE_FLOAT y)=0;
	virtual void show(SDL_Surface *)=0;
	virtual void setVisibleExtents(SDL_Rect)=0;
};

#endif //class_sdlgauntcraft_ilevelscroller