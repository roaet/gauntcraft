#ifndef class_sdlgauntcraft_levelscrollerentity
#define class_sdlgauntcraft_levelscrollerentity

#include "ClientCore.h"
#include "ILevelScroller.h"
#include "SpriteSheet.h"
#include "Timer.h"
#include "LevelScrollerTile.h"

namespace gauntcraft{
	class LevelScrollerEntity : public LevelScrollerTile {
	private:
	public:
		LevelScrollerEntity();
		virtual ~LevelScrollerEntity();

		using LevelScrollerTile::getAge;
		using LevelScrollerTile::getX;
		using LevelScrollerTile::getY;

		using LevelScrollerTile::setAge;
		using LevelScrollerTile::setX;
		using LevelScrollerTile::setY;
	};
}

#endif //class_sdlgauntcraft_levelscrollerentity