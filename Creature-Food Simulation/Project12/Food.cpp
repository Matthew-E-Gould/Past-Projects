#include "Food.h"

// precondition: value must be passed to the object to set location co-ordinate
void Food::setLocationX(int X)
{
	locationX = X;
};
void Food::setLocationY(int Y)
{
	locationY = Y;
};
// no preconditions
void Food::eaten() {
	edible = false;
}
void Food::newRound() {
	edible = true;
}

int Food::getLocationX()
{
	return locationX;
};
int Food::getLocationY()
{
	return locationY;
};

bool Food::isEdible() {
	return edible;
}

Food::Food()
{
	locationX = 0;
	locationY = 0;
	edible = true;
}

Food::~Food()
{
}
