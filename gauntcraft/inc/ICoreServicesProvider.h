#ifndef class_sdlgauntcraft_icoreservicesprovider
#define class_sdlgauntcraft_icoreservicesprovider

#include "SpriteSheetManager.h"
namespace gauntcraft {
	class ICoreServicesProvider {
	public:
		virtual SpriteSheetManager * getSpriteManager()=0;
	};
}
#endif //class_sdlgauntcraft_icoreservicesprovider