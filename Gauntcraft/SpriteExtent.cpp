#include "SpriteExtent.h"

SpriteExtent::SpriteExtent(CORE_INT x, CORE_INT y, CORE_UINT w, CORE_UINT h) {
	SDL_Rect rect = {x, y, w, h};
	random_horizontal_frames = 0;
	this->clipRect = rect;
	this->idleFrame = 0;
}

SDL_Rect SpriteExtent::getRect() {
	return getRect(-1);
}

SDL_Rect SpriteExtent::getRect(CORE_INT frame) {
	SDL_Rect returnRect = clipRect;
	CORE_UINT width = clipRect.w;
	if(frame >= 0) {
		int offset;
		if(frames > 1) {
			offset = (frame % frames);
		} else if(random_horizontal_frames > 1) {
			offset = (frame % random_horizontal_frames);
		}
		SDL_Rect temp = {width*offset+clipRect.x, clipRect.y, clipRect.w, clipRect.h};
		returnRect = temp;
	} else if( frame == SPRITERANDOM) {
		if(random_horizontal_frames > 1) {
			CORE_INT randomOffset = rand() % random_horizontal_frames;
			SDL_Rect temp = {width*randomOffset+clipRect.x, clipRect.y, clipRect.w, clipRect.h};
			returnRect = temp;
		}
	} else if( frame == SPRITEIDLE) {
		SDL_Rect temp = {width*idleFrame+clipRect.x, clipRect.y, clipRect.w, clipRect.h};
		returnRect = temp;
	}
	return returnRect;
}

void SpriteExtent::setRandom(CORE_INT randomHorizontalFrames) {
	random_horizontal_frames = randomHorizontalFrames;
}

void SpriteExtent::setFrames(CORE_INT frames) {
	this->frames = frames;
}

void SpriteExtent::setIdleFrame(CORE_INT frame) {
	this->idleFrame = frame;
}