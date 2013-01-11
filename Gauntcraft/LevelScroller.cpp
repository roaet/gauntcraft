#include "LevelScroller.h"

LevelScroller::LevelScroller(SpriteSheet * sheet) {
	r_border = g_border = b_border = 0;
	levelSheet = sheet;
	tileSize = 32;
	hShift = vShift = 0;
	columnsToRefresh = rowsToRefresh = 0;
	updateRequired = RESET;
}

LevelScroller::~LevelScroller() {

}


void LevelScroller::generateScrollerTiles() {
	hTilesNeeded = visibleExtents.w / tileSize + 2 * LOADING_PADDING;
	vTilesNeeded = visibleExtents.h / tileSize + 2 * LOADING_PADDING;

	scrollerMap.resize(vTilesNeeded);
	for(CORE_INT i = 0; i < vTilesNeeded; i++)
		scrollerMap[i].resize(hTilesNeeded);

	for(CORE_INT i = 0; i < vTilesNeeded; i++) {
		for(CORE_INT j = 0; j < hTilesNeeded; j++) {
#if SCROLLERDEBUG == 1
				scrollerMap[i][j].age = rand() % 3 + 1;
#else
				scrollerMap[i][j].age = rand() % 50 + 1;
#endif
			scrollerMap[i][j].x = j*tileSize;
			scrollerMap[i][j].y = i*tileSize;
		}
	}
}

void LevelScroller::displayScrollerTiles(SDL_Surface * dest) {
	for(CORE_INT i = 0; i < vTilesNeeded; i++) {
		for(CORE_INT j = 0; j < hTilesNeeded; j++) {
			ScrollerTile tile = scrollerMap[i][j];
			CORE_INT xPos = tile.x + visibleExtents.x - LOADING_PADDING * tileSize;
			CORE_INT yPos = tile.y + visibleExtents.y - LOADING_PADDING * tileSize;
			xPos += hShift;
			yPos += vShift;
#if SCROLLERDEBUG == 1
			switch(tile.age) {
			case 1:
				boxRGBA(dest, xPos, yPos, 
					    xPos + tileSize,
					    yPos + tileSize,
					    125, 255, 125, 255);
				break;
			case 2:
				boxRGBA(dest, xPos, yPos, 
					    xPos + tileSize,
					    yPos + tileSize,
					    255, 125, 125, 255);
				break;
			case 3:
				boxRGBA(dest, xPos, yPos, 
					    xPos + tileSize,
					    yPos + tileSize,
					    125, 125, 255, 255);
				break;
			default:
				boxRGBA(dest, xPos, yPos, 
					    xPos + tileSize,
					    yPos + tileSize,
					    128, 128, 128, 255);
			}
			rectangleRGBA(dest, xPos, yPos, 
					      xPos + tileSize,
					      yPos + tileSize,
					      0, 0, 0, 50);
#else
			levelSheet->blitSprite("dirt", xPos, yPos,  dest);
			if(tile.age == 1) {
				levelSheet->blitSprite("blastdirt", xPos, yPos, dest);
			} else if(tile.age < 5) {
				levelSheet->blitSprite("darkdirt", xPos, yPos, dest);
			}
			rectangleRGBA(dest, xPos, yPos, 
					      xPos + tileSize,
					      yPos + tileSize,
					      0, 0, 0, 50);
#endif

		}
	}
}

void LevelScroller::updateScrollerTiles(CORE_BITMASK directionalBitmask) {

	// Flag all current tiles to be not old
	for(CORE_INT i = 0; i < vTilesNeeded; i++) {
		for(CORE_INT j = 0; j < hTilesNeeded; j++) {
			if(scrollerMap[i][j].age == 0)
#if SCROLLERDEBUG == 1
				scrollerMap[i][j].age = rand() % 3 + 1;
#else
				scrollerMap[i][j].age = rand() % 50 + 1;
#endif
		}
	}

	if(updateRequired & LEFT) { // need to push all tiles RIGHT and generate new ones on LEFT
		for(CORE_INT i = 0; i < vTilesNeeded; i++) 
			for(CORE_INT j = hTilesNeeded - 1; j > 0; j--) 
				scrollerMap[i][j].age = scrollerMap[i][j-1].age;
		// resetting the columnsToRefresh LEFT columns
		for(CORE_INT i = 0; i < vTilesNeeded; i++) 
			for(CORE_INT j = 0; j < columnsToRefresh; j++)
				scrollerMap[i][j].age = 0;

	} else if(updateRequired & RIGHT) { // need to push all tiles LEFT and generate new ones on RIGHT
		for(CORE_INT i = 0; i < vTilesNeeded; i++) 
			for(CORE_INT j = 0; j < hTilesNeeded - 1; j++)
				scrollerMap[i][j].age = scrollerMap[i][j+1].age;
		// resetting the columnsToRefresh RIGHT columns
		for(CORE_INT i = 0; i < vTilesNeeded; i++) 
			for(CORE_INT j = hTilesNeeded - 1; j > hTilesNeeded - columnsToRefresh - 1; j--)
				scrollerMap[i][j].age = 0;
	}

	if(updateRequired & TOP) { // need to push all tiles DOWN and generate new ones on TOP
		for(CORE_INT j = 0; j < hTilesNeeded; j++) 
			for(CORE_INT i = vTilesNeeded - 1; i > 0; i--) 
				scrollerMap[i][j].age = scrollerMap[i-1][j].age;
		// resetting the rowsToRefresh TOP columns
		for(CORE_INT i = 0; i < rowsToRefresh; i++) 
			for(CORE_INT j = 0; j < hTilesNeeded; j++) 
				scrollerMap[i][j].age = 0;

	} else if(updateRequired & BOTTOM) { // need to push all tiles UP and generate new ones on BOTTOM
		for(CORE_INT j = 0; j < hTilesNeeded; j++)
			for(CORE_INT i = 0; i < vTilesNeeded - 1; i++) 
				scrollerMap[i][j].age = scrollerMap[i+1][j].age;
		// resetting the rowsToRefresh BOTTOM columns
		for(CORE_INT j = 0; j < hTilesNeeded; j++) 
			for(CORE_INT i = vTilesNeeded - 1; i > vTilesNeeded - rowsToRefresh - 1; i--) 
				scrollerMap[i][j].age = 0;
	}

	// reset the update state
	updateRequired = RESET;
}

void LevelScroller::pan(CORE_INT x, CORE_INT y) {
	hShift += x;
	vShift += y;

	if(hShift > tileSize) {
		updateRequired = updateRequired | LEFT;
		columnsToRefresh = (int)(hShift / tileSize);
		hShift = 0;
	} else if (hShift < -tileSize) {
		updateRequired = updateRequired | RIGHT;
		columnsToRefresh = (int)(hShift / -tileSize);
		hShift = 0;
	}

	if(vShift > tileSize) {
		updateRequired = updateRequired | TOP;
		rowsToRefresh = (int)(vShift / tileSize);
		vShift = 0;
	} else if (vShift < -tileSize) {
		updateRequired = updateRequired | BOTTOM;
		rowsToRefresh = (int)(vShift / -tileSize);
		vShift = 0;
	}
	
	if(updateRequired) {
		updateScrollerTiles(updateRequired);
	}
}

void LevelScroller::drawBorder(SDL_Surface * dest) {
	
	if(true) 
		rectangleRGBA(dest, visibleExtents.x, visibleExtents.y, 
					  visibleExtents.x + visibleExtents.w,
					  visibleExtents.y + visibleExtents.h,
					  0, 0, 0, 255);
}

void LevelScroller::show(SDL_Surface * dest) {
	displayScrollerTiles(dest);
	drawBorder(dest);
}


void LevelScroller::setSpriteSheet(SpriteSheet * sheet) {
	this->levelSheet = sheet;
}

void LevelScroller::setVisibleExtents(SDL_Rect extents) {
	visibleExtents.h = extents.h;
	visibleExtents.w = extents.w;
	visibleExtents.x = extents.x;
	visibleExtents.y = extents.y;
	generateScrollerTiles();
}
