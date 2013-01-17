#include <cstdio>
#include <string>

#include "../inc/Engine.h"
#include "zlib.h"
#include "GauntcraftCore.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif


#define CHUNK 16384

int main(int argc, char ** argv) {
	gauntcraft::Engine* engine = new gauntcraft::Engine();
	engine->setWindowCaption("Gauntcraft");
	engine->init();
	random_function();
	int ret = engine->run();
	delete engine;
	return ret;
}