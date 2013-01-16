#include "../inc/CoreEntity.h"

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
	CORE_FLOAT xCalcVel = (CORE_FLOAT)xVel * (deltaTicks / 1000.f);
	CORE_FLOAT yCalcVel = (CORE_FLOAT)yVel * (deltaTicks / 1000.f);
	x += (CORE_INT) xCalcVel;
	y += (CORE_INT) yCalcVel;	
}

CORE_INT CoreEntity::getX() {
	return x;
}

CORE_INT CoreEntity::getY() {
	return y;
}