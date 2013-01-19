#ifndef class_sdlgauntcraft_keyboardhandler
#define class_sdlgauntcraft_keyboardhandler

#include "ClientCore.h"

namespace gauntcraft {
	class KeyboardHandler {
	private:
		Uint8 * keystate;
	public:
		KeyboardHandler();
		~KeyboardHandler();

		CORE_VOID getKeyState();
		CORE_BOOL key_pressed(SDLKey key);
	};
}

#endif // class_sdlgauntcraft_keyboardhandler