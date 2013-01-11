#include "LevelMap.h"

LevelMap::LevelMap(int w, int h, int tileWidth, SpriteSheet* sheet) {
	this->tileWidth = tileWidth;
	fullTileWidth = w * tileWidth;
	fullTileHeight = h * tileWidth;
	levelSheet = sheet;
	tileCountX = w;
	tileCountY = h;
	mapCenterX = mapCenterY = 2;

	SDL_Rect temp = {0, 0, fullTileWidth, fullTileHeight};
	xPos = 0;
	yPos = 0;
	tileId = 0;

	clipRect = temp;
	doClip = false;
	drawBorder = true;
	matrix = MapMatrix(4, std::vector <LevelTile *>(4, NULL));

	init();
}

LevelMap::~LevelMap() {
	if (center) delete center;
}

void LevelMap::init() {
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, fullTileWidth, fullTileHeight, 32,
                                   0, 0, 0, 0);

	if(!surface) {
		fprintf(stderr, "Cannot make level surface");
	}

	center = generateTile(mapCenterX, mapCenterY);
	center->generateSurround();
}

LevelTile* LevelMap::generateTile(int x, int y) {
	int currentTileId = tileId;
	matrix[x][y] = new LevelTile(currentTileId, x, y, tileCountX, tileCountY,
					     		    tileWidth, levelSheet, this);
	return matrix[x][y];
}

void LevelMap::shiftTile(LevelTile* tile, int x, int y) {
	tile->moveTo(center->getX()-x, tile->getY()-y);
}

void LevelMap::shift(int x, int y) {
	shiftTile(center, x, y);
	shiftTile(center->getBottom(), x, y);
	shiftTile(center->getTop(), x, y);
	shiftTile(center->getLeft(), x, y);
	shiftTile(center->getRight(), x, y);
}

void LevelMap::showTile(LevelTile * tile, SDL_Surface * dest) {
	int tileCoordX = tile->getXIndex() - mapCenterX;
	int tileCoordY = tile->getYIndex() - mapCenterY;
	int x_offset = tileCoordX * fullTileWidth;
	int y_offset = tileCoordY * fullTileHeight;
	x_offset += tile->getX();
	y_offset += tile->getY();
	tile->show(x_offset, y_offset, dest, NULL);
}

void LevelMap::show(SDL_Surface * dest) {
	SDL_PixelFormat* format = dest->format;
	SDL_FillRect(surface, NULL, SDL_MapRGB(format, 0, 0, 0));
	showTile(center, surface);
	showTile(center->getBottom(), surface);
	showTile(center->getTop(), surface);
	showTile(center->getLeft(), surface); 
	showTile(center->getRight(), surface);
	
	SDL_Rect offset = {mapOffsetX, mapOffsetY, 0, 0};
	SDL_BlitSurface(surface, NULL, dest, &offset);
	
	if(drawBorder) 
		rectangleRGBA(dest, mapOffsetX, mapOffsetY, 
					  mapOffsetX + fullTileWidth,
					  mapOffsetY + fullTileHeight,
					  0, 0, 0, 255);

}

void LevelMap::handleInput(SDL_Event * event) {
	if(event->type == SDL_MOUSEMOTION) {
		int x = event->motion.x;
		int y = event->motion.y;
		// only meaningful if we're within the bounds of the map
		if( ! ( x < mapOffsetX || x > mapOffsetX + fullTileWidth ||
			    y < mapOffsetY || y > mapOffsetY + fullTileHeight) ) {
			fprintf(stderr,"Mouse moved (%d, %d)", x, y);
		}
	}
}

void LevelMap::centerOn(int x, int y) { 
	mapOffsetX = x - fullTileWidth/2;
	mapOffsetY = y - fullTileHeight/2;
}

void LevelMap::setClip(bool flag) {
	doClip = flag;
}