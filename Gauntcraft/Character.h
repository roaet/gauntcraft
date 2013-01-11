#ifndef class_sdlgauntcraft_character
#define class_sdlgauntcraft_character

#include <string>

#include "CoreEntity.h"
#include "CoreTypes.h"
#include "SDL.h"
#include "SpriteSheet.h"
#include "Timer.h"

class Character : public CoreEntity {
private:
	SpriteSheet * sheet;
	std::string spriteFrame;
	CORE_FLOAT startX, startY;
	CORE_BITMASK spriteDirection;
	CORE_BITMASK oldSpriteDirection;
	Timer animationTimer;
	CORE_INT animationFrame;
	std::string oldSpriteFrame;

public:
	using CoreEntity::move;
	using CoreEntity::getX, CoreEntity::getY;
	virtual void moveTo(CORE_FLOAT newX, CORE_FLOAT newY) override;
	Character(SpriteSheet *, std::string);
	virtual void handleInput(SDL_Event *) override;
	virtual void show(SDL_Surface *) override;
};

#endif //class_sdlgauntcraft_character
