#include "../inc/SpriteSheet.h"

SpriteSheet::SpriteSheet(ISDLImageLoader* loader, std::string filename) {
	logfile = stderr;
	this->filename = filename;
	this->loader = loader;

	sheet = NULL;
	load();
}

SpriteSheet::~SpriteSheet() {
	if(sheet) {
		SDL_FreeSurface(sheet);
	}
	for(SpriteHash::iterator it = sprites.begin(); it != sprites.end(); ++it) {
		delete it->second;
	}
}

CORE_STATUS SpriteSheet::load_from_ini(boost::property_tree::ptree pt) {
		std::istringstream spritelist(pt.get<std::string>("SpriteSheet.Sprites"));
		CORE_INT defaultWidth = pt.get<CORE_INT>("SpriteSheet.defaultWidth");
		CORE_INT defaultHeight = pt.get<CORE_INT>("SpriteSheet.defaultHeight");
		CORE_INT defaultIdleFrame = 0;

		std::stringstream lookup;
		std::string key;
		while(std::getline(spritelist, key, ' ')) {

			spriteKeys.insert(key);
						
			
			lookup.str(std::string());
			lookup << key << ".frames";
			boost::optional<CORE_INT> frames = pt.get_optional<CORE_INT>(lookup.str());

			lookup.str(std::string());
			lookup << key << ".random";
			boost::optional<CORE_INT> randomSelections = pt.get_optional<CORE_INT>(lookup.str());
			
			lookup.str(std::string());
			lookup << key << ".idleframe";
			boost::optional<CORE_INT> idleframe = pt.get_optional<CORE_INT>(lookup.str());
			if(!idleframe) idleframe = defaultIdleFrame;

			lookup.str(std::string());
			lookup << key << ".w";
			boost::optional<CORE_INT> w = pt.get_optional<CORE_INT>(lookup.str());
			if(!w) w = defaultWidth;


			lookup.str(std::string());
			lookup << key << ".h";
			boost::optional<CORE_INT> h = pt.get_optional<CORE_INT>(lookup.str());
			if(!h) h = defaultHeight;

			lookup.str(std::string());
			lookup << key << ".x";
			CORE_INT x = pt.get<CORE_INT>(lookup.str());

			lookup.str(std::string());
			lookup << key << ".y";
			CORE_INT y = pt.get<CORE_INT>(lookup.str());

			
			lookup.str(std::string());
			lookup << key << ".directions";
			boost::optional<std::string> directions = pt.get_optional<std::string>(lookup.str());

			SpriteExtent * newExtent = new SpriteExtent(x, y, *w, *h);
			if(randomSelections) newExtent->setRandom(*randomSelections);
			if(frames) newExtent->setFrames(*frames);
			newExtent->setIdleFrame(*idleframe);

			this->sprites[std::string(key)] = newExtent;

			// if the directions setting is there the loader will
			// attempt to auto generate the rest of the sprites
			// with the assumption that the rest are very similar
			// to the one we just loaded. The one we just loaded 
			// will be the first directional we meet.
			if(directions) {
				std::istringstream directionlist(*directions);
				std::string dir;
				CORE_INT encounters = 0;
				CORE_BOOL isBelow = false;
				while(std::getline(directionlist, dir, ' ')) {
					std::string newKey = key;
					// These are control words that state where the next frame are
					// if this is not first it will assume that the sprites
					// are to the side
					if(dir == "below") {
						isBelow = true;
						continue;
					} 

					newKey += "-" + dir;
					if(encounters != 0) {
						// we are at a new sprite, create a new one and add it
						// the position is different this time, but the rest
						// are assumed to be the same
						CORE_INT newX = x + (encounters * (*w * *frames));
						CORE_INT newY = y;
						if(isBelow) {
							newX = x;
							newY = y + (encounters * *h);
						}
						SpriteExtent * newExtent = new SpriteExtent(newX, newY, *w, *h);
						if(randomSelections) newExtent->setRandom(*randomSelections);
						if(frames) newExtent->setFrames(*frames);
						newExtent->setIdleFrame(*idleframe);
						spriteKeys.insert(newKey);
						this->sprites[std::string(newKey)] = newExtent;
					} else {
						// we ran into the first sprite, please just add
						// another key for it so we can access it this way
						this->sprites[std::string(newKey)] = newExtent;
					}
					encounters++;
				}
			}
		}
		return 0;
}

CORE_STATUS SpriteSheet::load() {
	boost::property_tree::ptree pt;
	// Adding space in buffer for .ini\0
	char * iniFilename = new char[filename.length() + 5];
	sprintf_s(iniFilename, filename.length() + 5, "%s.ini", filename.c_str());
	CORE_BOOL iniFileLoaded = false;
	sheet = loader->loadImage(filename);
	if(!sheet) {
		fprintf(logfile, "Error loading spritesheet");
		return 1;
	}

	try {
		boost::property_tree::ini_parser::read_ini(iniFilename, pt);
		iniFileLoaded = true;

	} catch (boost::property_tree::ini_parser_error e) {
		fprintf(logfile, "Error loading %s", iniFilename);
	}
	
	delete iniFilename;
	if(iniFileLoaded) {
		if(load_from_ini(pt) < 0) {
			fprintf(logfile, "Problem parsing logfile");
			return 1;
		}
	} else {
		fprintf(logfile, "Error locating spritesheet ini file");
		return 1;
	}

	return 0;
}

CORE_STATUS SpriteSheet::blitSprite(std::string name, CORE_INT x, CORE_INT y, SDL_Surface* dest) {
	SpriteExtent * rect = this->sprites[name];
	SDL_Rect offset = {x, y, 0, 0};
	SDL_BlitSurface(sheet, &(rect->getRect()), dest, &offset);
	return 0;
}

CORE_STATUS SpriteSheet::blitAnimatedSprite(std::string name, CORE_INT x, CORE_INT y, CORE_INT frame, SDL_Surface* dest) {
	SpriteExtent * rect = this->sprites[name];
	SDL_Rect offset = {x, y, 0, 0};
	SDL_BlitSurface(sheet, &(rect->getRect(frame)), dest, &offset);
	return 0;
}

SDL_Rect SpriteSheet::getSpriteDimensions(std::string name) {
	SDL_Rect rect = this->sprites[name]->getRect();
	SDL_Rect ret = {0, 0, rect.w, rect.h};
	return ret;
}

CORE_BOOL SpriteSheet::hasKey(std::string key) {
	return (spriteKeys.find(key) != spriteKeys.end());
}