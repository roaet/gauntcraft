#ifndef class_sdlgauntcraft_levelmap
#define class_sdlgauntcraft_levelmap
#include <cstdio>
#include <iostream>
#include <hash_map>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>

#include "CoreUtility.h"
#include "ILevelTileGenerator.h"
#include "LevelTile.h"
#include "SDL.h"
#include "SpriteSheet.h"
#include "SDL_gfxPrimitives.h"
#include "boost/unordered_map.hpp"


#define EXTRA_TILES 1

typedef std::vector < std::vector < LevelTile * > > MapMatrix;

class LevelMap : public ILevelTileGenerator {
private:	

	void init();
	void showTile(LevelTile * tile, SDL_Surface * dest);
	void shiftTile(LevelTile * tile, int x, int y);

	SpriteSheet * levelSheet;
	SDL_Surface * surface;
	float xPos, yPos;
	int mapOffsetX, mapOffsetY;

	int tileCountX;
	int tileCountY;
	int tileWidth;
	int fullTileWidth; 
	int fullTileHeight;
	int tileId;
	int mapCenterX;
	int mapCenterY;

	bool doClip;
	bool drawBorder;
	SDL_Rect clipRect;

	LevelTile* center;
	MapMatrix matrix;
public:
	LevelMap(int w, int h, int tileWidth, SpriteSheet* sheet);
	~LevelMap();

	void shift(int x, int y);
	void show(SDL_Surface * dest);
	void centerOn(int x, int y);
	void setClip(bool flag);
	void handleInput(SDL_Event *);
	virtual LevelTile* generateTile(int x, int y);
};
#endif // class_sdlgauntcraft_levelmap
