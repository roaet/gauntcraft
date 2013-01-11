#include "Character.h"

Character::Character(SpriteSheet * sheet, std::string spriteFrame) {
	this->sheet = sheet;
	this->spriteFrame = spriteFrame;
	speed = 100;
	x = y = xVel = yVel = 0;
	spriteDirection = 0;

}

void Character::handleInput(SDL_Event * event) {
	if(event->type == SDL_KEYDOWN) {
		switch(event->key.keysym.sym) {
		case SDLK_w: yVel -= speed; 
			spriteDirection |= DIR_UP;
			break;
		case SDLK_a: xVel -= speed; 
			spriteDirection |= DIR_LEFT;
			break;
		case SDLK_s: yVel += speed; 
			spriteDirection |= DIR_DOWN;
			break;
		case SDLK_d: xVel += speed; 
			spriteDirection |= DIR_RIGHT;
			break;
		}
	} else if(event->type == SDL_KEYUP) {
		switch(event->key.keysym.sym) {
		case SDLK_w: yVel += speed; 
			spriteDirection ^= DIR_UP;
			break;
		case SDLK_a: xVel += speed; 
			spriteDirection ^= DIR_LEFT;
			break;
		case SDLK_s: yVel -= speed; 
			spriteDirection ^= DIR_DOWN;
			break;
		case SDLK_d: xVel -= speed; 
			spriteDirection ^= DIR_RIGHT;
			break;
		}
	}
}

void Character::moveTo(CORE_FLOAT newX, CORE_FLOAT newY) {
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

	if(animationTimer.get_ticks() > 200) {
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