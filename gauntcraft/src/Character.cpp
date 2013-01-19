#include "../inc/Character.h"

namespace gauntcraft {
	Character::Character(SpriteSheet * sheet, std::string spriteFrame) {
		this->sheet = sheet;
		this->spriteFrame = spriteFrame;
		speed = 200;
		x = y = xVel = yVel = 0;
		spriteDirection = 0;
		north.velocity = south.velocity = east.velocity = west.velocity = 0;
		north.toggle = south.toggle = east.toggle = west.toggle = false;
		north.activated = south.activated = east.activated = west.activated = false;
		north.modified = south.modified = east.modified = west.modified = false;
		north.modFactor = south.modFactor = east.modFactor = west.modFactor = 1;
		boosted = boost_toggle = false;
		inputStack = new InputStack();

	}

	Character::~Character() {
		if(inputStack) delete inputStack;
	}

	void Character::handleMovement(void) {
		if(north.toggle) {
			north.velocity = north.velocity == 0 ? speed : -north.velocity;
			north.activated = !north.activated;
			if(!north.activated) spriteDirection ^= DIR_UP;
			north.toggle = false;
			yVel -= north.velocity;
		}
		if(south.toggle) {
			south.velocity = south.velocity == 0 ? speed : -south.velocity;
			south.activated = !south.activated;
			if(!south.activated) spriteDirection ^= DIR_DOWN;
			south.toggle = false;
			yVel += south.velocity;
		}
		if(east.toggle) {
			east.velocity = east.velocity == 0 ? speed : -east.velocity;
			east.activated = !east.activated;
			if(!east.activated) spriteDirection ^= DIR_RIGHT;
			east.toggle = false;
			xVel += east.velocity;
		}
		if(west.toggle) {
			west.velocity = west.velocity == 0 ? speed : -west.velocity;
			west.activated = !west.activated;
			if(!west.activated) spriteDirection ^= DIR_LEFT;
			west.toggle = false;
			xVel -= west.velocity;
		}
	}

	CORE_BOOL Character::targetScan(KeyboardHandler * keys) {
		inputStack->scan_keys(keys);
		north.toggle = inputStack->contains(CI_UP) != north.activated;
		south.toggle = inputStack->contains(CI_DOWN) != south.activated;
		east.toggle = inputStack->contains(CI_RIGHT) != east.activated;
		west.toggle = inputStack->contains(CI_LEFT) != west.activated;
		handleMovement();
		selectSpriteDirection();
		return CORE_TRUE;
	}

	CORE_VOID Character::selectSpriteDirection() {
		const CORE_INPUT * stack = inputStack->getStack();
		if(inputStack->count() == 0)
			spriteDirection = 0;
		else {
			for(int x = 0; x < inputStack->count(); ++x) {
				switch(stack[x]) {
				case CI_UP:
					spriteDirection |= DIR_UP;
					break;
				case CI_DOWN:
					spriteDirection |= DIR_DOWN;
					break;
				case CI_LEFT:
					spriteDirection |= DIR_LEFT;
					break;
				case CI_RIGHT:
					spriteDirection |= DIR_RIGHT;
					break;
				}
			}
			for(int x = 0; x < inputStack->count(); ++x) {
				switch(stack[x]) {
				case CI_UP:
					if(spriteDirection & DIR_DOWN) spriteDirection ^= DIR_DOWN;
					break;
				case CI_DOWN:
					if(spriteDirection & DIR_UP) spriteDirection ^= DIR_UP;
					break;
				case CI_LEFT:
					if(spriteDirection & DIR_RIGHT) spriteDirection ^= DIR_RIGHT;
					break;
				case CI_RIGHT:
					if(spriteDirection & DIR_LEFT) spriteDirection ^= DIR_LEFT;
					break;
				}
			}
		}
	}

	void Character::moveTo(CORE_INT newX, CORE_INT newY) {
		startX = newX;
		startY = newY;
	}

	void Character::show(SDL_Surface * dest) {
		if(spriteDirection != 0 && !animationTimer.is_started()) {
			animationTimer.start();
			animationFrame = 0;
		}
		std::string selectedFrame = spriteFrame;
		CORE_INPUT lastKey = inputStack->getTail();
		
		if(spriteDirection & DIR_UP && spriteDirection & DIR_LEFT ) {
			selectedFrame += "-nw";
			if(!sheet->hasKey(selectedFrame)) {
				selectedFrame = spriteFrame + 
								(lastKey == CI_LEFT ? "-w" : "-n");
			}
		} else if(spriteDirection & DIR_UP && spriteDirection & DIR_RIGHT) {
			selectedFrame += "-ne";
			if(!sheet->hasKey(selectedFrame)) {
				selectedFrame = spriteFrame + 
								(lastKey == CI_RIGHT ? "-e" : "-n");
			};
		} else if(spriteDirection & DIR_UP) {
			selectedFrame += "-n";
		} else if(spriteDirection & DIR_DOWN && spriteDirection & DIR_LEFT) {
			selectedFrame += "-sw";
			if(!sheet->hasKey(selectedFrame)) {
				selectedFrame = spriteFrame +
								(lastKey == CI_LEFT ? "-w" : "-s");
			};
		} else if(spriteDirection & DIR_DOWN && spriteDirection & DIR_RIGHT) {
			selectedFrame += "-se";
			if(!sheet->hasKey(selectedFrame)) {
				selectedFrame = spriteFrame +
								(lastKey == CI_RIGHT ? "-e" : "-s");
			};
		} else if(spriteDirection & DIR_DOWN) {
			selectedFrame += "-s";
		} else if(spriteDirection & DIR_LEFT) {
			selectedFrame += "-w";
		} else if(spriteDirection & DIR_RIGHT) {
			selectedFrame += "-e";
		}
		oldSpriteDirection = spriteDirection;

		if(animationTimer.get_ticks() > 150) {
			animationFrame++;
			animationTimer.start();
		}

		if(spriteDirection == 0) {
			animationFrame = SPRITEIDLE;
			animationTimer.stop();
			selectedFrame = oldSpriteFrame;
		}
		if(!sheet->hasKey(selectedFrame)) selectedFrame = spriteFrame;
		oldSpriteFrame = selectedFrame;
		sheet->blitAnimatedSprite(selectedFrame, (int)startX, (int)startY, animationFrame, dest);

	}
}