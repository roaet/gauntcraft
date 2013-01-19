#include "../inc/SpriteEntity.h"

namespace gauntcraft {
	SpriteEntity::SpriteEntity(ICoreServicesProvider * provider, std::string spriteconf):
	SpriteObject(provider), spriteconf(spriteconf) {
		loadJsonConf();
	}

	CORE_BOOL SpriteEntity::loadJsonConf() {
		boost::property_tree::ptree pt;
		std::string fullfile = SPRITEENTITY_FILE_PREFIX + spriteconf;
		CORE_BOOL loaded = CORE_FALSE;
		try {
			boost::property_tree::json_parser::read_json(fullfile.c_str(),pt);
			loaded = CORE_TRUE;
		} catch (boost::property_tree::json_parser_error e) {
			LOG(ERROR) << "Error loading " << fullfile << ": " << e.message();
		}
		if(!loaded) return CORE_FALSE;

		anchor.x = pt.get<CORE_INT>("entity.anchor.x");
		anchor.y = pt.get<CORE_INT>("entity.anchor.y");

		LOG(INFO) << "Loaded entity with anchors ("<<
			anchor.x<<","<<
			anchor.y<<")";
		return CORE_TRUE;
	}

	SpriteEntity::~SpriteEntity() {

	}
}