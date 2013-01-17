#ifndef class_sdlgauntcraft_coreutility
#define class_sdlgauntcraft_coreutility

#include <algorithm>

#include "ClientCore.h"
#include "ClientCoreTypes.h"
namespace gauntcraftcore {
	class ClientCoreUtility {

	public:
		static SDL_Rect IntersectRect(SDL_Rect * a, SDL_Rect *b);
		static void clearPtr(void *);
		static bool failed(CORE_INT);
	};
}
#endif // class_sdlgauntcraft_coreutility
