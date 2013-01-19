#ifndef class_sdlgauntcraft_gauntcraftcore
#define class_sdlgauntcraft_gauntcraftcore
#include <cstdio>
#include <stdint.h>
#include "CoreInfoheader.h"
#include "GauntcraftCoreTypes.h"
#include "GauntcraftCoreUtility.h"

namespace gauntcraft {
	typedef enum {
		CI_NONE=0, CI_UP, CI_DOWN, CI_LEFT, CI_RIGHT
	} CORE_INPUT;
}
void random_function();

#endif //class_sdlgauntcraft_gauntcraftcore