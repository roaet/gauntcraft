#ifndef class_sdlgauntcraft_levelscroller
#define class_sdlgauntcraft_levelscroller

#include <cmath>
#include <string>
#include <list>
#include <vector>

#include "ClientCore.h"
#include "ILevelScroller.h"
#include "IMouseTarget.h"
#include "SpriteSheet.h"
#include "Timer.h"
#include "LevelScrollerTile.h"
#include "LevelScrollerEntity.h"

typedef struct {
	CORE_INT age;
	CORE_INT x;
	CORE_INT y;
} ScrollerTile;

#define LS_RESET 0
#define LS_LEFT 1
#define LS_RIGHT 2
#define LS_TOP 4
#define LS_BOTTOM 8

#define SCROLLERDEBUG 0

#define INVALID_MOUSE -1

#define LOADING_PADDING 5
#define MAX_ENTITIES 1024
namespace gauntcraft {
	class LevelScroller : public ILevelScroller, public IMouseTarget{
	private:
		void drawBorder(SDL_Surface *);
		void generateScrollerTiles();
		void displayScrollerTiles(SDL_Surface *);
		void updateScrollerTiles(CORE_BITMASK directionalBitmask);
		void updateScrollerEntities();
		void displayScrollerEntities(SDL_Surface *);

		/* /// DEBUG TEST FUNCTIONS */
		/* /// */

		CORE_INT r_border, g_border, b_border;
		CORE_INT tileSize;
		SDL_Rect visibleExtents;
		gauntcraft::SpriteSheet * levelSheet;
		CORE_INT hTilesNeeded, vTilesNeeded;

		// Variables for scrolling method
		std::vector < std::vector <gauntcraft::LevelScrollerTile> > scrollerMap;
		std::list < gauntcraft::LevelScrollerEntity * > mapEntities;
		gauntcraft::SpriteSheet * entitySheet;
		gauntcraft::SpriteSheet * entitySheet2;
		CORE_INT columnsToRefresh, rowsToRefresh;
		CORE_INT hShift, vShift;
		CORE_BITMASK updateRequired;

		CORE_INT lastMouseX, lastMouseY;

	public:
		LevelScroller(gauntcraft::SpriteSheet *);
		virtual ~LevelScroller();

		//IMouseTarget stuff
		virtual CORE_BOOL targetHit(SDL_Event * event);

		void setSpriteSheet(gauntcraft::SpriteSheet *);
		void setEntitySpriteSheet(gauntcraft::SpriteSheet *);
		void setEntitySpriteSheet2(gauntcraft::SpriteSheet *);

		virtual void pan(CORE_INT x, CORE_INT y);
		virtual void show(SDL_Surface *);
		virtual void setVisibleExtents(SDL_Rect);
	};
}

#endif //class_sdlgauntcraft_levelscroller