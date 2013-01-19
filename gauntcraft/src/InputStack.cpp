#include "../inc/InputStack.h"

namespace gauntcraft {
	InputStack::InputStack() {
		stack = new CORE_INPUT[INITIAL_STACK_SIZE];
		currentHead = 0;
	}

	InputStack::~InputStack() {
		if(stack) delete [] stack;
	}

	SDLKey InputStack::citokey(CORE_INPUT input) {
		switch(input) {
		case CI_DOWN:	return SDLK_s;
		case CI_UP:	return SDLK_w;
		case CI_LEFT:	return SDLK_a;
		case CI_RIGHT:	return SDLK_d;
		}
		return SDLK_LAST;
	}

	const CORE_INPUT * InputStack::getStack() {
		return stack;
	}

	CORE_VOID InputStack::updateKeyState(CORE_INPUT input, CORE_BOOL pressed) {
		if(pressed && !contains(input)) push_input(input);
		if(!pressed && contains(input)) remove_input(input);
	}

	CORE_VOID InputStack::scan_keys(KeyboardHandler * keys) {
		updateKeyState(CI_UP, keys->key_pressed(citokey(CI_UP)));
		updateKeyState(CI_DOWN, keys->key_pressed(citokey(CI_DOWN)));
		updateKeyState(CI_LEFT, keys->key_pressed(citokey(CI_LEFT)));
		updateKeyState(CI_RIGHT, keys->key_pressed(citokey(CI_RIGHT)));
	}

	CORE_VOID InputStack::outputStackLog() {
		LOG(INFO) << "STACK {";
		for(int x = 0; x < currentHead; ++x) {
			LOG(INFO) << stack[x];
		}
		LOG(INFO) << "}";

	}

	CORE_INT InputStack::find_input(CORE_INPUT input) {
		for(int x = 0; x < currentHead; ++x)
			if(stack[x] == input) return x;
		return -1;
	}

	CORE_BOOL InputStack::contains(CORE_INPUT input) {
		if(find_input(input) < 0) return CORE_FALSE;
		return CORE_TRUE;
	}

	CORE_VOID InputStack::shiftDown(CORE_INT shift_to) {
		for(int x = shift_to; x < currentHead; ++x)
			stack[x] = stack[x+1];	
	}

	CORE_VOID InputStack::remove(CORE_INPUT input) {
		CORE_INT index = find_input(input);
		--currentHead;
		shiftDown(index);
	}

	CORE_BOOL InputStack::push_input(CORE_INPUT input) {
		if(contains(input) || currentHead >= INITIAL_STACK_SIZE) return CORE_FALSE;
		stack[currentHead] = input;
		++currentHead;
		return CORE_TRUE;
	}

	CORE_INPUT InputStack::remove_input(CORE_INPUT input) {
		if(!contains(input)) return CI_NONE;
		remove(input);	
		return input;
	}

	CORE_INT InputStack::count() {
		return currentHead;
	}

	CORE_VOID InputStack::clear() {
		currentHead = 0;
	}


	CORE_INPUT InputStack::getTail() {
		if(currentHead <= 0) return CI_NONE;
		return stack[currentHead-1];
	}


}