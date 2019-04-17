#include "Creature.h"

// precondition: value must be passed to the object to set location co-ordinate
void Creature::setLocationX(int X)
{
	locationX = X;
};
void Creature::setLocationY(int Y)
{
	locationY = Y;
};
void Creature::ate(bool tOrF) {
	if (tOrF) {
		energy += 3;
		fed = true;
	}
	else {
		energy -= 1;
	}
}
// precondition: energy must have an int value
void Creature::energyCheck() {
	if (energy > 9) {
		energy = 9;
	}
	if (energy < 0) {
		energy = 0;
	}
}
// no preconditions
void Creature::kill() {
	alive = false;
}
void Creature::newRound() {
	fed = false;
}

int Creature::getLocationX()
{
	return locationX;
};
int Creature::getLocationY()
{
	return locationY;
};
int Creature::getEnergy() {
	return energy;
}

bool Creature::isAlive() {
	return alive;
};
bool Creature::hasEaten() {
	return fed;
}

Creature::Creature()
{
	energy = 5;
	locationX = -1;
	locationY = -1;
	alive = true;
	fed = false;
}

Creature::~Creature()
{
}
