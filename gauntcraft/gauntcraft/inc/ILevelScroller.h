#ifndef class_sdlgauntcraft_ilevelscroller
#define class_sdlgauntcraft_ilevelscroller

#include <string>

#include "CoreTypes.h"
#include "SDL/SDL.h"

class ILevelScroller {
public:
	virtual void pan(CORE_INT x, CORE_INT y)=0;
	virtual void show(SDL_Surface *)=0;
	virtual void setVisibleExtents(SDL_Rect)=0;
};

#endif //class_sdlgauntcraft_ilevelscroller
