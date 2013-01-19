#include "../inc/LevelScroller.h"
namespace gauntcraft {
	LevelScroller::LevelScroller(SpriteSheet * sheet) {
		r_border = g_border = b_border = 0;
		levelSheet = sheet;
		tileSize = 32;
		lastMouseX = lastMouseY = INVALID_MOUSE;
		hShift = vShift = 0;
		columnsToRefresh = rowsToRefresh = 0;
		updateRequired = LS_RESET;
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
					scrollerMap[i][j].setAge(rand() % 100 + 1);
	#else
					scrollerMap[i][j].setAge(rand() % 50 + 1);
	#endif
				scrollerMap[i][j].setX(j*tileSize);
				scrollerMap[i][j].setY(i*tileSize);
			}
		}
	}

	void LevelScroller::displayScrollerEntities(SDL_Surface * dest) {
		while(!mapEntities.empty()) {
			LevelScrollerEntity * ent = mapEntities.front();
			entitySheet->blitSprite("trunk",ent->getX(), ent->getY(), dest); 
			entitySheet2->blitSprite("treetop",ent->getX(), ent->getY()-50, dest);
			mapEntities.pop_front();
		}
	}

	void LevelScroller::displayScrollerTiles(SDL_Surface * dest) {
		CORE_BOOL drawMouse = false;
		CORE_INT mouseX, mouseY;
		for(CORE_INT i = 0; i < vTilesNeeded; i++) {
			for(CORE_INT j = 0; j < hTilesNeeded; j++) {
				LevelScrollerTile tile = scrollerMap[i][j];
				CORE_INT xPos = tile.getX() + visibleExtents.x - LOADING_PADDING * tileSize;
				CORE_INT yPos = tile.getY() + visibleExtents.y - LOADING_PADDING * tileSize;
				xPos += hShift;
				yPos += vShift;
				if(!drawMouse) {
					if(lastMouseX < xPos || lastMouseY < yPos ||
						lastMouseX > xPos + tileSize ||
						lastMouseY > yPos + tileSize) 
						drawMouse = false;
					else {
						mouseX = xPos;
						mouseY = yPos;
						drawMouse = true;
					}
				}
	#if SCROLLERDEBUG == 1
				if(tile.getAge() != 0 && tile.getAge() < 10) {
					boxRGBA(dest, xPos, yPos, 
							xPos + tileSize,
							yPos + tileSize,
							125, 255, 125, 255);
					LevelScrollerEntity * tree = new LevelScrollerEntity();
					tree->setX(xPos - (entitySheet->getSpriteDimensions("trunk").w/2) + (tileSize/2));
					tree->setY(yPos - (entitySheet->getSpriteDimensions("trunk").h/2) + (tileSize/2));
					mapEntities.push_back(tree);
				} else if(tile.getAge() != 0 && tile.getAge() < 20) {
					boxRGBA(dest, xPos, yPos, 
							xPos + tileSize,
							yPos + tileSize,
							255, 125, 125, 255);
				} else if(tile.getAge() != 0) {
					boxRGBA(dest, xPos, yPos, 
							xPos + tileSize,
							yPos + tileSize,
							125, 125, 255, 255);
				} else {
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
				if(tile.getAge() == 1) {
					levelSheet->blitSprite("blastdirt", xPos, yPos, dest);
					LevelScrollerEntity * tree = new LevelScrollerEntity();
					tree->setX(xPos - (entitySheet->getSpriteDimensions("trunk").w/2) + (tileSize/2));
					tree->setY(yPos - (entitySheet->getSpriteDimensions("trunk").h/2) + (tileSize/2));
					mapEntities.push_back(tree);
				} else if(tile.getAge() < 5) {
					levelSheet->blitSprite("darkdirt", xPos, yPos, dest);
				}
				rectangleRGBA(dest, xPos, yPos, 
							  xPos + tileSize,
							  yPos + tileSize,
							  0, 0, 0, 25);
	#endif

			}
		}
		if(drawMouse) {
			rectangleRGBA(dest, mouseX, mouseY, 
						  mouseX + tileSize,
						  mouseY + tileSize,
						  255, 0, 0, 128);
		}
	}

	CORE_BOOL LevelScroller::targetHit(SDL_Event * event) {
		CORE_INT mouseX = event->motion.x;
		CORE_INT mouseY = event->motion.y;
		if( mouseX > visibleExtents.x + visibleExtents.w ||
			mouseX < visibleExtents.x ||
			mouseY > visibleExtents.y + visibleExtents.h ||
			mouseY < visibleExtents.y ) {
				lastMouseX = lastMouseY = INVALID_MOUSE;
				return false;
		}
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		return true;
	}

	void LevelScroller::updateScrollerEntities() {

	}

	void LevelScroller::updateScrollerTiles(CORE_BITMASK directionalBitmask) {

		// Flag all current tiles to be not old
		for(CORE_INT i = 0; i < vTilesNeeded; i++) {
			for(CORE_INT j = 0; j < hTilesNeeded; j++) {
				if(scrollerMap[i][j].getAge() == 0)
	#if SCROLLERDEBUG == 1
					scrollerMap[i][j].setAge(rand() % 100 + 1);
	#else
					scrollerMap[i][j].setAge(rand() % 50 + 1);
	#endif
			}
		}

		if(updateRequired & LS_LEFT) { // need to push all tiles RIGHT and generate new ones on LEFT
			for(CORE_INT i = 0; i < vTilesNeeded; i++) 
				for(CORE_INT j = hTilesNeeded - 1; j > 0; j--) 
					scrollerMap[i][j].setAge(scrollerMap[i][j-1].getAge());
			// resetting the columnsToRefresh LEFT columns
			for(CORE_INT i = 0; i < vTilesNeeded; i++) 
				for(CORE_INT j = 0; j < columnsToRefresh; j++)
					scrollerMap[i][j].setAge(0);

		} else if(updateRequired & LS_RIGHT) { // need to push all tiles LEFT and generate new ones on RIGHT
			for(CORE_INT i = 0; i < vTilesNeeded; i++) 
				for(CORE_INT j = 0; j < hTilesNeeded - 1; j++)
					scrollerMap[i][j].setAge(scrollerMap[i][j+1].getAge());
			// resetting the columnsToRefresh RIGHT columns
			for(CORE_INT i = 0; i < vTilesNeeded; i++) 
				for(CORE_INT j = hTilesNeeded - 1; j > hTilesNeeded - columnsToRefresh - 1; j--)
					scrollerMap[i][j].setAge(0);
		}

		if(updateRequired & LS_TOP) { // need to push all tiles DOWN and generate new ones on TOP
			for(CORE_INT j = 0; j < hTilesNeeded; j++) 
				for(CORE_INT i = vTilesNeeded - 1; i > 0; i--) 
					scrollerMap[i][j].setAge(scrollerMap[i-1][j].getAge());
			// resetting the rowsToRefresh TOP columns
			for(CORE_INT i = 0; i < rowsToRefresh; i++) 
				for(CORE_INT j = 0; j < hTilesNeeded; j++) 
					scrollerMap[i][j].setAge(0);

		} else if(updateRequired & LS_BOTTOM) { // need to push all tiles UP and generate new ones on BOTTOM
			for(CORE_INT j = 0; j < hTilesNeeded; j++)
				for(CORE_INT i = 0; i < vTilesNeeded - 1; i++) 
					scrollerMap[i][j].setAge(scrollerMap[i+1][j].getAge());
			// resetting the rowsToRefresh BOTTOM columns
			for(CORE_INT j = 0; j < hTilesNeeded; j++) 
				for(CORE_INT i = vTilesNeeded - 1; i > vTilesNeeded - rowsToRefresh - 1; i--) 
					scrollerMap[i][j].setAge(0);
		}

		// reset the update state
		updateRequired = LS_RESET;
	}

	void LevelScroller::pan(CORE_INT x, CORE_INT y) {
		hShift += x;
		vShift += y;

		if(hShift > tileSize) {
			updateRequired = updateRequired | LS_LEFT;
			columnsToRefresh = (int)(hShift / tileSize);
			hShift = 0;
		} else if (hShift < -tileSize) {
			updateRequired = updateRequired | LS_RIGHT;
			columnsToRefresh = (int)(hShift / -tileSize);
			hShift = 0;
		}

		if(vShift > tileSize) {
			updateRequired = updateRequired | LS_TOP;
			rowsToRefresh = (int)(vShift / tileSize);
			vShift = 0;
		} else if (vShift < -tileSize) {
			updateRequired = updateRequired | LS_BOTTOM;
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
		displayScrollerEntities(dest);
		drawBorder(dest);
	}


	void LevelScroller::setSpriteSheet(SpriteSheet * sheet) {
		this->levelSheet = sheet;
	}


	void LevelScroller::setEntitySpriteSheet(SpriteSheet* sheet) {
		this->entitySheet = sheet;
	}

	void LevelScroller::setEntitySpriteSheet2(SpriteSheet* sheet) {
		this->entitySheet2 = sheet;
	}

	void LevelScroller::setVisibleExtents(SDL_Rect extents) {
		visibleExtents.h = extents.h;
		visibleExtents.w = extents.w;
		visibleExtents.x = extents.x;
		visibleExtents.y = extents.y;
		generateScrollerTiles();
	}
}