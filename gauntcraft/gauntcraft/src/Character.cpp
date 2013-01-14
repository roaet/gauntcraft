#include "Character.h"

Character::Character(SpriteSheet * sheet, std::string spriteFrame) {
	this->sheet = sheet;
	this->spriteFrame = spriteFrame;
	speed = 200;
	x = y = xVel = yVel = 0;
	spriteDirection = 0;
	north.velocity = south.velocity = east.velocity = west.velocity = 0;
	north.toggle = south.toggle = east.toggle = west.toggle = false;
	north.modified = south.modified = east.modified = west.modified = false;
	north.modFactor = south.modFactor = east.modFactor = west.modFactor = 1;
	boosted = boost_toggle = false;

}

Character::~Character() {

}

void Character::handleMovement(void) {
	if(north.toggle) {
		north.velocity = north.velocity == 0 ? speed : -north.velocity;
		north.toggle = false;
		yVel -= north.velocity;
	}
	if(south.toggle) {
		south.velocity = south.velocity == 0 ? speed : -south.velocity;
		south.toggle = false;
		yVel += south.velocity;
	}
	if(east.toggle) {
		east.velocity = east.velocity == 0 ? speed : -east.velocity;
		east.toggle = false;
		xVel += east.velocity;
	}
	if(west.toggle) {
		west.velocity = west.velocity == 0 ? speed : -west.velocity;
		west.toggle = false;
		xVel -= west.velocity;
	}
}

void Character::handleInput(SDL_Event * event) {
	if(event->type == SDL_KEYDOWN) {
		switch(event->key.keysym.sym) {
		case SDLK_RSHIFT: case SDLK_LSHIFT:
			boost_toggle = true;
			break;
		case SDLK_w: 
			north.toggle = true;
			spriteDirection |= DIR_UP;
			break;
		case SDLK_a: 
			west.toggle = true;
			spriteDirection |= DIR_LEFT;
			break;
		case SDLK_s: 
			south.toggle = true;
			spriteDirection |= DIR_DOWN;
			break;
		case SDLK_d: 
			east.toggle = true;
			spriteDirection |= DIR_RIGHT;
			break;
		}
	} else if(event->type == SDL_KEYUP) {
		switch(event->key.keysym.sym) {
		case SDLK_RSHIFT: case SDLK_LSHIFT:
			boost_toggle = true;
			break;
		case SDLK_w: 
			north.toggle = true;
			spriteDirection ^= DIR_UP;
			break;
		case SDLK_a: 
			west.toggle = true;
			spriteDirection ^= DIR_LEFT;
			break;
		case SDLK_s:
			south.toggle = true;
			spriteDirection ^= DIR_DOWN;
			break;
		case SDLK_d: 
			east.toggle = true;
			spriteDirection ^= DIR_RIGHT;
			break;
		}
	}
	handleMovement();
			

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

	if(spriteDirection & DIR_UP && spriteDirection & DIR_LEFT ) {
		selectedFrame += "-nw";
		if(!sheet->hasKey(selectedFrame)) selectedFrame = spriteFrame + "-n";
	} else if(spriteDirection & DIR_UP && spriteDirection & DIR_RIGHT) {
		selectedFrame += "-ne";
		if(!sheet->hasKey(selectedFrame)) selectedFrame = spriteFrame + "-n";
	} else if(spriteDirection & DIR_UP) {
		selectedFrame += "-n";
	} else if(spriteDirection & DIR_DOWN && spriteDirection & DIR_LEFT) {
		selectedFrame += "-sw";
		if(!sheet->hasKey(selectedFrame)) selectedFrame = spriteFrame + "-s";
	} else if(spriteDirection & DIR_DOWN && spriteDirection & DIR_RIGHT) {
		selectedFrame += "-se";
		if(!sheet->hasKey(selectedFrame)) selectedFrame = spriteFrame + "-s";
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
	if(!sheet->hasKey(selectedFrame)) {
        std::string errorFrame = selectedFrame;
        selectedFrame = spriteFrame;
    }
    if(oldSpriteFrame != selectedFrame) animationFrame = 0;
	oldSpriteFrame = selectedFrame;
	sheet->blitAnimatedSprite(selectedFrame, (int)startX, (int)startY, animationFrame, dest);

}
