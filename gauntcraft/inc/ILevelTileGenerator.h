#ifndef class_sdlgauntcraft_ileveltilegenerator
#define class_sdlgauntcraft_ileveltilegenerator

#include <string>

#include "SDL.h"

class LevelTile;
namespace gauntcraft {
	class ILevelTileGenerator {
	public:
		virtual LevelTile* generateTile(int x, int y) = 0;
	};
}
#endif //class_sdlgauntcraft_ileveltilegenerator