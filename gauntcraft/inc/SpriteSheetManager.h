/*********************************
SpriteSheetManager will provide a single point
to load and access all the spritesheets for the
program and will handle their unloading. 

Might be a singleton, but undecided.
*********************************/
#ifndef class_sdlgauntcraft_spritesheetmanager
#define class_sdlgauntcraft_spritesheetmanager
#include <string>
#include <glog/logging.h>

#include "ClientCore.h"
#include "SpriteSheet.h"

#include "ISDLImageLoader.h"
#include "boost/optional.hpp"
#include "boost/unordered_map.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
typedef boost::unordered_map<std::string, gauntcraft::SpriteSheet *> SpriteSheetHash;

const std::string FILE_PREFIX = "assets/sprites/";

namespace gauntcraft {
	class SpriteSheetManager {
	private:
		ISDLImageLoader* loader;
		SpriteSheetHash sheets;

	public:
		SpriteSheetManager(ISDLImageLoader * loader);
		virtual ~SpriteSheetManager();
		CORE_BOOL loadSheet(std::string sheet);
		SpriteSheet * getSheet(std::string sheet);
		CORE_BOOL hasSheet(std::string sheet);
	};
}
#endif //class_sdlgauntcraft_spritesheetmanager