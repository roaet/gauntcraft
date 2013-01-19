#ifndef class_sdlgauntcraft_inputstack
#define class_sdlgauntcraft_inputstack
#include "ClientCore.h"

#include "KeyboardHandler.h"
#include <glog/logging.h>

#define INITIAL_STACK_SIZE 10

namespace gauntcraft {
	class InputStack {
	private:
		CORE_INPUT* stack;
		CORE_INT currentHead;

		CORE_VOID shiftDown(CORE_INT shift_to);
		CORE_VOID remove(CORE_INPUT input);
		CORE_INT find_input(CORE_INPUT input);
		
		CORE_VOID updateKeyState(CORE_INPUT input, CORE_BOOL pressed);
		CORE_BOOL push_input(CORE_INPUT input);
		CORE_INPUT remove_input(CORE_INPUT input);
		SDLKey citokey(CORE_INPUT input);

		CORE_VOID outputStackLog();
	public:
		InputStack();
		virtual ~InputStack();
		CORE_BOOL contains(CORE_INPUT input);
		CORE_VOID scan_keys(KeyboardHandler * keys);
		const CORE_INPUT * getStack();
		CORE_INPUT getTail();
		CORE_INT count();
		CORE_VOID clear();
		
	};
}

#endif //class_sdlgauntcraft_inputstack