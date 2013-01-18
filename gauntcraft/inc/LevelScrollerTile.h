#ifndef class_sdlgauntcraft_levelscrollertile
#define class_sdlgauntcraft_levelscrollertile

#include "ClientCore.h"
#include "ILevelScroller.h"
#include "SpriteSheet.h"
#include "Timer.h"

namespace gauntcraft{
	class LevelScrollerTile {
	private:
		CORE_INT age;
		CORE_INT x;
		CORE_INT y;
	public:
		LevelScrollerTile();
		virtual ~LevelScrollerTile();

		CORE_INT getAge();
		CORE_INT getX();
		CORE_INT getY();

		void setAge(CORE_INT a);
		void setX(CORE_INT nw);
		void setY(CORE_INT ny);
	};
}

#endif //class_sdlgauntcraft_levelscrollertile