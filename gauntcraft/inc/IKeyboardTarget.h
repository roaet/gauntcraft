#ifndef class_sdlgauntcraft_ikeyboardtarget
#define class_sdlgauntcraft_ikeyboardtarget
#include "ClientCore.h"
#include "KeyboardHandler.h"

namespace gauntcraft {
	class IKeyboardTarget {
	private:

	public:
		virtual CORE_BOOL targetScan(KeyboardHandler * keys)=0;
	};
}

#endif // class_sdlgauntcraft_ikeyboardtarget