#include "../inc/SpriteSheetManager.h"

namespace gauntcraft {

	SpriteSheetManager::SpriteSheetManager(ISDLImageLoader * loader) {
		this->loader = loader;
	}

	SpriteSheetManager::~SpriteSheetManager() {
		sheets.clear();
	}

	CORE_BOOL SpriteSheetManager::loadSheet(std::string sheet) {
		std::string fullFilename = FILE_PREFIX + sheet;
		LOG(INFO) << "Loading sprite sheet ( " << fullFilename << ")";
		SpriteSheet * newSheet = new SpriteSheet(this->loader, fullFilename);
		if(!newSheet->isValid()) {
			LOG(ERROR) << "Error loading sprite sheet ( " << fullFilename<< ")";
			delete newSheet;
			return CORE_FALSE;
		}
		sheets[sheet] = newSheet;
		return CORE_TRUE;
	}

	SpriteSheet * SpriteSheetManager::getSheet(std::string sheet) {
		if(!hasSheet(sheet)) {
			if(!loadSheet(sheet))
				return NULL;
		}
		return sheets[sheet];
	}

	CORE_BOOL SpriteSheetManager::hasSheet(std::string sheet) {
		return (sheets.find(sheet) != sheets.end());
	}

}