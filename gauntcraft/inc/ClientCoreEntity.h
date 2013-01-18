#ifndef class_sdlgauntcraft_coreentity
#define class_sdlgauntcraft_coreentity

#include <cmath>
#include <string>

#include "ClientCore.h"
#include "SpriteSheet.h"
namespace gauntcraftcore {
	class ClientCoreEntity {
	protected:
		// position
		CORE_INT x, y;

		// velocity
		CORE_INT xVel, yVel;

		// speed
		CORE_INT speed;
	public:
		ClientCoreEntity();
		virtual ~ClientCoreEntity();
		virtual void handleInput(SDL_Event *);
		virtual void move(CORE_UINT32 deltaTicks);
		virtual void moveTo(CORE_INT newX, CORE_INT newY);
		virtual void show(SDL_Surface *)=0;
		virtual CORE_INT getX();
		virtual CORE_INT getY();
	};
}

#endif //class_sdlgauntcraft_coreentity
