#include "../inc/ClientCoreEntity.h"
namespace gauntcraftcore {
	ClientCoreEntity::ClientCoreEntity() {

	}

	ClientCoreEntity::~ClientCoreEntity() {

	}

	void ClientCoreEntity::moveTo(CORE_INT newX, CORE_INT newY) {
		x = newX;
		y = newY;
	}

	void ClientCoreEntity::move(CORE_UINT32 deltaTicks) {
		CORE_FLOAT xCalcVel = (CORE_FLOAT)xVel * (deltaTicks / 1000.f);
		CORE_FLOAT yCalcVel = (CORE_FLOAT)yVel * (deltaTicks / 1000.f);
		x += (CORE_INT) xCalcVel;
		y += (CORE_INT) yCalcVel;	
	}

	CORE_INT ClientCoreEntity::getX() {
		return x;
	}

	CORE_INT ClientCoreEntity::getY() {
		return y;
	}
}