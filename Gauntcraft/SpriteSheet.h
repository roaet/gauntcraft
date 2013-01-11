#ifndef class_sdlgauntcraft_spritesheet
#define class_sdlgauntcraft_spritesheet
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <hash_map>
#include <string>
#include <sstream>
#include <vector>
#include <set>

#include "SDL.h"
#include "SDL_image.h"
#include "SpriteExtent.h"
#include "ISDLImageLoader.h"
#include "boost/optional.hpp"
#include "boost/unordered_map.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

typedef boost::unordered_map<std::string, SpriteExtent*> SpriteHash;

class SpriteSheet {
private:
	CORE_STATUS load(void);
	CORE_STATUS load_from_ini(boost::property_tree::ptree pt);

	SDL_Surface* sheet;
	std::string filename;
	ISDLImageLoader * loader;
	FILE* logfile;

	SpriteHash sprites;
	std::set<std::string> spriteKeys;


public:
	SpriteSheet(ISDLImageLoader* loader, std::string filename);
	virtual ~SpriteSheet(void);

	CORE_STATUS blitSprite(std::string name, CORE_INT x, CORE_INT y, SDL_Surface* dest);
	CORE_STATUS blitAnimatedSprite(std::string name, CORE_INT x, CORE_INT y, CORE_INT frame, SDL_Surface* dest);
	SDL_Rect getSpriteDimensions(std::string name);
	CORE_BOOL hasKey(std::string key);
};
#endif
