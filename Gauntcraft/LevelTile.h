#ifndef class_sdlgauntcraft_leveltile
#define class_sdlgauntcraft_leveltile
#include <cstdio>
#include <iostream>
#include <hash_map>
#include <string>

#include "SDL.h"
#include "SpriteSheet.h"

#include "SDL_gfxPrimitives.h"
#include "ILevelTileGenerator.h"


class LevelTile {
private:
	void generate();
	void initialize();
	
	SpriteSheet * levelSheet;
	SDL_Surface * surface;

	int width;
	int height;
	int tileWidth;

	int ** tileData;

	int fullTileWidth; 
	int fullTileHeight;

	int tileId;
	int x_index;
	int y_index;

	int x, y;

	LevelTile * top;
	LevelTile * bottom;
	LevelTile * left;
	LevelTile * right;

	ILevelTileGenerator * generator;

public:
	LevelTile(int id, int x, int y, int w, int h, int tileWidth, SpriteSheet* sheet, ILevelTileGenerator * gen);
	~LevelTile();

	void show(int x, int y, SDL_Surface * dest, SDL_Rect * clip);
	void moveTo(int x, int y);
	void generateSurround();
	SDL_Rect * getClipRect();

	int getX();
	int getY();

	int getXIndex();
	int getYIndex();

	LevelTile * getBottom();
	LevelTile * getTop();
	LevelTile * getLeft();
	LevelTile * getRight();
};
#endif // class_sdlgauntcraft_leveltile
