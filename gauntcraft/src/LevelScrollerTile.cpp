#include "../inc/LevelScrollerTile.h"

gauntcraft::LevelScrollerTile::LevelScrollerTile() {
	this->age = 0;
	this->x = 0;
	this->y = 0;
}

gauntcraft::LevelScrollerTile::~LevelScrollerTile() {

}

CORE_INT gauntcraft::LevelScrollerTile::getAge() {
	return this->age;
}

CORE_INT gauntcraft::LevelScrollerTile::getY() {
	return this->y;
}

CORE_INT gauntcraft::LevelScrollerTile::getX() {
	return this->x;
}


void gauntcraft::LevelScrollerTile::setAge(CORE_INT a) {
	this->age = a;
}

void gauntcraft::LevelScrollerTile::setX(CORE_INT nx) {
	this->x = nx;
}

void gauntcraft::LevelScrollerTile::setY(CORE_INT ny) {
	this->y = ny;
}