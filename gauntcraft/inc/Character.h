#ifndef class_sdlgauntcraft_character
#define class_sdlgauntcraft_character

#include <string>

#include "ClientCore.h"
#include "ClientCoreEntity.h"
#include "SDL.h"
#include "SpriteSheet.h"
#include "Timer.h"

typedef struct {
	CORE_INT velocity;
	CORE_BOOL toggle;
	CORE_BOOL modified;
	CORE_INT modFactor;
} CharMoveStatus;
namespace gauntcraft {
	class Character : public gauntcraftcore::ClientCoreEntity {
	private:
		void handleMovement();

		gauntcraft::SpriteSheet * sheet;
		std::string spriteFrame;
		CORE_INT startX, startY;
		CORE_BITMASK spriteDirection;
		CORE_BITMASK oldSpriteDirection;
		gauntcraft::Timer animationTimer;
		CORE_INT animationFrame;
		std::string oldSpriteFrame;
		CharMoveStatus north, south, east, west;
		CORE_BOOL boost_toggle;
		CORE_BOOL boosted;

	public:
		Character(gauntcraft::SpriteSheet *, std::string);
		virtual ~Character();

		using ClientCoreEntity::move;
		using ClientCoreEntity::getX;
		using ClientCoreEntity::getY;
		virtual void moveTo(CORE_INT newX, CORE_INT newY);
		virtual void handleInput(SDL_Event *);
		virtual void show(SDL_Surface *);
	};
}
#endif //class_sdlgauntcraft_character
