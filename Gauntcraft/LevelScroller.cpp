#include "LevelScroller.h"

LevelScroller::LevelScroller(SpriteSheet * sheet) {
	r_border = g_border = b_border = 0;
	levelSheet = sheet;
	tileSize = 32;
	hShift = vShift = 0;
	updateRequired = RESET;
}

LevelScroller::~LevelScroller() {

}


void LevelScroller::generateScrollerTiles() {
	hTilesNeeded = visibleExtents.w / tileSize + 2 * LOADDING_PADDING;
	vTilesNeeded = visibleExtents.h / tileSize + 2 * LOADDING_PADDING;

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
			CORE_FLOAT xPos = tile.x + visibleExtents.x - LOADDING_PADDING * tileSize;
			CORE_FLOAT yPos = tile.y + visibleExtents.y - LOADDING_PADDING * tileSize;
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
					      255, 0, 0, 255);
#else
			
			levelSheet->blitSprite("dirt", xPos, yPos,  dest);
			if(tile.age == 1) {
				levelSheet->blitSprite("blastdirt", xPos, yPos, dest);
			} else if(tile.age < 5) {
				levelSheet->blitSprite("darkdirt", xPos, yPos, dest);
			}
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
		// resetting the LEFT column
		for(CORE_INT i = 0; i < vTilesNeeded; i++) scrollerMap[i][0].age = 0;
	} else if(updateRequired & RIGHT) { // need to push all tiles LEFT and generate new ones on RIGHT
		for(CORE_INT i = 0; i < vTilesNeeded; i++) 
			for(CORE_INT j = 0; j < hTilesNeeded - 1; j++)
				scrollerMap[i][j].age = scrollerMap[i][j+1].age;
		// resetting the RIGHT column
		for(CORE_INT i = 0; i < vTilesNeeded; i++) scrollerMap[i][hTilesNeeded-1].age = 0;
	}

	if(updateRequired & TOP) { // need to push all tiles DOWN and generate new ones on TOP
		for(CORE_INT j = 0; j < hTilesNeeded; j++) 
			for(CORE_INT i = vTilesNeeded - 1; i > 0; i--) 
				scrollerMap[i][j].age = scrollerMap[i-1][j].age;
		// resetting the TOP column
		for(CORE_INT j = 0; j < hTilesNeeded; j++) scrollerMap[0][j].age = 0;
	} else if(updateRequired & BOTTOM) { // need to push all tiles UP and generate new ones on BOTTOM
		for(CORE_INT j = 0; j < hTilesNeeded; j++)
			for(CORE_INT i = 0; i < vTilesNeeded - 1; i++) 
				scrollerMap[i][j].age = scrollerMap[i+1][j].age;
		// resetting the BOTTOM column
		for(CORE_INT j = 0; j < hTilesNeeded; j++) scrollerMap[vTilesNeeded-1][j].age = 0;
	}

	// reset the update state
	updateRequired = RESET;
}

void LevelScroller::pan(CORE_FLOAT x, CORE_FLOAT y) {
	hShift += x;
	vShift += y;

	if(hShift > tileSize) {
		updateRequired = updateRequired | LEFT;
		hShift = 0.f;
	} else if (hShift < -tileSize) {
		updateRequired = updateRequired | RIGHT;
		hShift = 0.f;
	}

	if(vShift > tileSize) {
		updateRequired = updateRequired | TOP;
		vShift = 0.f;
	} else if (vShift < -tileSize) {
		updateRequired = updateRequired | BOTTOM;
		vShift = 0.f;
	}
	
	if(updateRequired) updateScrollerTiles(updateRequired);
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
