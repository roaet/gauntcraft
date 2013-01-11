#ifndef class_sdlgauntcraft_character
#define class_sdlgauntcraft_character

#include <string>

#include "CoreEntity.h"
#include "CoreTypes.h"
#include "SDL.h"
#include "SpriteSheet.h"
#include "Timer.h"

typedef struct {
	CORE_INT velocity;
	CORE_BOOL toggle;
	CORE_BOOL modified;
	CORE_INT modFactor;
} CharMoveStatus;

class Character : public CoreEntity {
private:
	void handleMovement();

	SpriteSheet * sheet;
	std::string spriteFrame;
	CORE_INT startX, startY;
	CORE_BITMASK spriteDirection;
	CORE_BITMASK oldSpriteDirection;
	Timer animationTimer;
	CORE_INT animationFrame;
	std::string oldSpriteFrame;
	CharMoveStatus north, south, east, west;
	CORE_BOOL boost_toggle;
	CORE_BOOL boosted;

public:
	Character(SpriteSheet *, std::string);
	virtual ~Character();

	using CoreEntity::move;
	using CoreEntity::getX, CoreEntity::getY;
	virtual void moveTo(CORE_INT newX, CORE_INT newY) override;
	virtual void handleInput(SDL_Event *) override;
	virtual void show(SDL_Surface *) override;
};

#endif //class_sdlgauntcraft_character
