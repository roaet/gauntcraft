#ifndef class_sdlgauntcraft_levelscroller
#define class_sdlgauntcraft_levelscroller

#include <cmath>
#include <string>
#include <vector>

#include "ClientCore.h"
#include "ILevelScroller.h"
#include "IMouseTarget.h"
#include "SpriteSheet.h"
#include "Timer.h"
#include "LevelScrollerTile.h"

typedef struct {
	CORE_INT age;
	CORE_INT x;
	CORE_INT y;
} ScrollerTile;

#define RESET 0
#define LEFT 1
#define RIGHT 2
#define TOP 4
#define BOTTOM 8

#define SCROLLERDEBUG 0

#define INVALID_MOUSE -1

#define LOADING_PADDING 2
namespace gauntcraft {
	class LevelScroller : public ILevelScroller, public IMouseTarget{
	private:
		void drawBorder(SDL_Surface *);
		void generateScrollerTiles();
		void displayScrollerTiles(SDL_Surface *);
		void updateScrollerTiles(CORE_BITMASK directionalBitmask);

		/* /// DEBUG TEST FUNCTIONS */
		/* /// */

		CORE_INT r_border, g_border, b_border;
		CORE_INT tileSize;
		SDL_Rect visibleExtents;
		gauntcraft::SpriteSheet * levelSheet;
		CORE_INT hTilesNeeded, vTilesNeeded;

		// Variables for scrolling method
		std::vector < std::vector <gauntcraft::LevelScrollerTile> > scrollerMap;
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

		virtual void pan(CORE_INT x, CORE_INT y);
		virtual void show(SDL_Surface *);
		virtual void setVisibleExtents(SDL_Rect);
	};
}

#endif //class_sdlgauntcraft_levelscroller