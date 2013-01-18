#ifndef class_sdlgauntcraft_imousetarget
#define class_sdlgauntcraft_imousetarget
#include "ClientCore.h"

namespace gauntcraft {
	class IMouseTarget {
	private:

	public:
		virtual CORE_BOOL targetHit(SDL_Event * event)=0;
	};
}

#endif // class_sdlgauntcraft_imousetarget