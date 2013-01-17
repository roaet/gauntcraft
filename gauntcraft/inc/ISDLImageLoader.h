#ifndef class_sdlgauntcraft_isdlimageloader
#define class_sdlgauntcraft_isdlimageloader

#include "SDL.h"
#include <string>
namespace gauntcraft {
	class ISDLImageLoader {
	public:
		virtual SDL_Surface* loadImage(std::string filename) = 0;
	};
}
#endif //class_sdlgauntcraft_isdlimageloader