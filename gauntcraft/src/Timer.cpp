#include "../inc/Timer.h"

Timer::Timer() {
	startTicks = pausedTicks = 0;
	paused = started = false;
}

void Timer::start() {
	started = true;

	paused = false;

	startTicks = SDL_GetTicks();
}

void Timer::stop() {
	started = false;
	paused = false;
}

CORE_INT Timer::get_ticks() {
	if(started) {
		if(paused) return pausedTicks;
		else return SDL_GetTicks() - startTicks;
	}
	return 0;
}

void Timer::pause() {
	if(started && !paused) {
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause() {
	if(paused) {
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}

CORE_BOOL Timer::is_paused() {
	return paused; 
}

CORE_BOOL Timer::is_started() {
	return started;
}