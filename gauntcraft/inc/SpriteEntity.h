/*********************************
Entity is one sprite or a collection of sprites
whose relationship to each other and the world
are defined by a configuration file. The prime
requirement of the Entity class is to provide
a layout for a collection of sprites and to
define the anchor point for where the whole
object connects to the world (a render offset)

This class also handles:
- Animation frames and timing
- Separate sprite frames dependant on state
*********************************/
#ifndef class_sdlgauntcraft_spriteentity
#define class_sdlgauntcraft_spriteentity

#include <string>

#include "GauntcraftCore.h"
#include "ICoreServicesProvider.h"
#include "SpriteObject.h"
#include "boost/optional.hpp"
#include "boost/foreach.hpp"
#include "boost/unordered_map.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

const std::string SPRITEENTITY_FILE_PREFIX = "assets/entities/";
namespace gauntcraft {
	class SpriteEntity : public SpriteObject {
	private:
		CORE_POINT anchor;
		std::string spriteconf;
		
		CORE_BOOL loadJsonConf();

	public:
		SpriteEntity(ICoreServicesProvider * provider, std::string spriteconf);



		virtual ~SpriteEntity();
	};
}
#endif //class_sdlgauntcraft_spriteentity