#include "CoreEntity.h"

CoreEntity::CoreEntity() {

}

CoreEntity::~CoreEntity() {

}

void CoreEntity::handleInput(SDL_Event * event) {

}

void CoreEntity::moveTo(CORE_INT newX, CORE_INT newY) {
	x = newX;
	y = newY;
}

void CoreEntity::move(CORE_UINT32 deltaTicks) {
	CORE_FLOAT xCalcVel = (float)xVel * (deltaTicks / 1000.f);
	CORE_FLOAT yCalcVel = (float)yVel * (deltaTicks / 1000.f);
	x += (CORE_INT) xCalcVel;
	y += (CORE_INT) yCalcVel;	
}

CORE_INT CoreEntity::getX() {
	return x;
}

CORE_INT CoreEntity::getY() {
	return y;
}