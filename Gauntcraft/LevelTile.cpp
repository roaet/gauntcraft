#include "LevelTile.h"

LevelTile::LevelTile(int id, int idxx, int idxy, int w, int h, int tileWidth, SpriteSheet * sheet, ILevelTileGenerator * gen) {
	width = w;
	height = h;
	tileData = NULL;
	this->tileWidth = tileWidth;
	generator = gen;
	tileId = id;
	fullTileWidth = width * tileWidth;
	fullTileHeight = height * tileWidth;
	levelSheet = sheet;
	initialize();
	generate();
	x = y = 0;
	bottom = top = left = right = NULL;
	x_index = idxx;
	y_index = idxy;
}

LevelTile::~LevelTile() {
	if(tileData) {
		for(int y = 0; y < height; y++) delete [] tileData[y];
		delete [] tileData;
	}
	SDL_FreeSurface(surface);
}


int LevelTile::getXIndex() {
	return x_index;
}

int LevelTile::getYIndex() {
	return y_index;
}

LevelTile * LevelTile::getBottom() {
	return bottom;
}

LevelTile * LevelTile::getTop() {
	return top;
}

LevelTile * LevelTile::getLeft() {
	return left;
}

LevelTile * LevelTile::getRight() {
	return right;
}

void LevelTile::generateSurround() {
	// create the tiles that surround this tile if they don't exist
	if(bottom == NULL) {
		bottom = generator->generateTile(x_index, y_index+1);
	}
	if(top == NULL) {
		top = generator->generateTile(x_index, y_index-1);
	}
	if(left == NULL) {
		left = generator->generateTile(x_index-1, y_index);
	}
	if(right == NULL) {
		right = generator->generateTile(x_index+1, y_index);
	}

}

void LevelTile::moveTo(int newX, int newY) {
	x = newX;
	y = newY;
}

void LevelTile::initialize() {
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, fullTileWidth, fullTileHeight, 32,
                                   0, 0, 0, 0);

	if(!surface) {
		fprintf(stderr, "Cannot make level surface");
	}

	tileData = new int*[height];
	for(int y = 0; y < height; y++) tileData[y] = new int[width];
}

void LevelTile::generate() {
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int tileChoice = rand() % 100;
			tileData[y][x] = tileChoice < 10 ? 0 : 1;
		}
	}
	/*
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			levelSheet->blitSprite("grass", tileWidth*x, tileWidth*y, surface);
			if(tileData[y][x] == 0)
				levelSheet->blitSprite("tree", tileWidth*x, tileWidth*y, surface);

		}
	}

	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			rectangleRGBA(surface, tileWidth*x, tileWidth*y, 
						  tileWidth*x + tileWidth,
						  tileWidth*y + tileWidth,
						  0, 0, 0, 128);

		}
	}
	*/
}

void LevelTile::show(int x, int y, SDL_Surface * dest, SDL_Rect * clip) {
	SDL_Rect offset = {x, y, 0, 0};
	int offsetX = x;
	int offsetY = y;
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			levelSheet->blitSprite("grass", 
								   tileWidth*x+offsetX,
								   tileWidth*y+offsetY, dest);
			if(tileData[y][x] == 0)
				levelSheet->blitSprite("tree", 
									   tileWidth*x+offsetX,
									   tileWidth*y+offsetY, dest);

		}
	}
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			rectangleRGBA(dest, 
				          tileWidth*x + offsetX,
						  tileWidth*y + offsetY, 
						  tileWidth*x + tileWidth + offsetX,
						  tileWidth*y + tileWidth + offsetY,
						  0, 0, 0, 128);

		}
	}
	//SDL_BlitSurface(surface, clip, dest, &offset);
}

SDL_Rect * LevelTile::getClipRect() {
	return &surface->clip_rect;
}

int LevelTile::getX() {
	return x;
}

int LevelTile::getY() {
	return y;
}