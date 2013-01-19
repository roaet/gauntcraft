#include "../inc/KeyboardHandler.h"

namespace gauntcraft {
	KeyboardHandler::KeyboardHandler() {

	}

	KeyboardHandler::~KeyboardHandler() {

	}

	CORE_VOID KeyboardHandler::getKeyState() {
		keystate = SDL_GetKeyState(NULL);
	}

	CORE_BOOL KeyboardHandler::key_pressed(SDLKey key) {
		if (keystate[key]) return CORE_TRUE;
		return CORE_FALSE;
	}
}