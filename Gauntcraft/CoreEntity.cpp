#include "CoreEntity.h"

CoreEntity::CoreEntity() {

}

CoreEntity::~CoreEntity() {

}

void CoreEntity::handleInput(SDL_Event * event) {

}

void CoreEntity::moveTo(CORE_FLOAT newX, CORE_FLOAT newY) {
	x = newX;
	y = newY;
}

void CoreEntity::move(CORE_UINT32 deltaTicks) {
	x += xVel * (deltaTicks / 1000.f);
	y += yVel * (deltaTicks / 1000.f);	
}

float CoreEntity::getX() {
	return x;
}

float CoreEntity::getY() {
	return y;
}