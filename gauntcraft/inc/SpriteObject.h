/*********************************
SpriteObject is the base class for anything
that will make use of the SpriteSheetManager.

Ex: Map tiles, Entities, Player objects
*********************************/
#ifndef class_sdlgauntcraft_spriteobject
#define class_sdlgauntcraft_spriteobject
#include <string>

#include "ClientCore.h"
#include "SpriteSheet.h"
#include "ICoreServicesProvider.h"

namespace gauntcraft {
	class SpriteObject {
	protected:
		ICoreServicesProvider * serviceProvider;
	public:
		SpriteObject(ICoreServicesProvider * provider);
		virtual ~SpriteObject();
	};
}

#endif //class_sdlgauntcraft_spriteobject