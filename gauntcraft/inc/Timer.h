#ifndef class_sdlgauntcraft_timer
#define class_sdlgauntcraft_timer

#include "CoreTypes.h"
#include "SDL.h"

class Timer {
	CORE_INT startTicks;
	CORE_INT pausedTicks;

	CORE_BOOL paused;
	CORE_BOOL started;
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	CORE_INT get_ticks();

	CORE_BOOL is_started();
	CORE_BOOL is_paused();
};

#endif //class_sdlgauntcraft_timer