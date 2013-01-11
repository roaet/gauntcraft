#ifndef class_sdlgauntcraft_coreentity
#define class_sdlgauntcraft_coreentity

#include <string>

#include "CoreTypes.h"
#include "SDL.h"
#include "SpriteSheet.h"

class CoreEntity {
protected:
	// position
	CORE_FLOAT x, y;

	// velocity
	CORE_FLOAT xVel, yVel;

	// speed
	CORE_FLOAT speed;
public:
	CoreEntity();
	virtual ~CoreEntity();
	virtual void handleInput(SDL_Event *);
	virtual void move(CORE_UINT32 deltaTicks);
	virtual void moveTo(CORE_FLOAT newX, CORE_FLOAT newY);
	virtual void show(SDL_Surface *)=0;
	virtual float getX();
	virtual float getY();
};

#endif //class_sdlgauntcraft_coreentity
