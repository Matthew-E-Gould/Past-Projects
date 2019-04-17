#include "Classes.h"


Weather::Weather(uint16_t random1, uint16_t random2, uint16_t random3)
{
	//intialisation works similarly to nextday to on intialisation class will run nexday
	nextDay(random1, random2, random3);
}
Weather::~Weather()
{
}

void Weather::nextDay(uint16_t random1, uint16_t random2, uint16_t random3) {

	// setting the random generated number modded by the max roll of it raining
	random1 = random1 % ROLL_MAX;

	// if the roll is less than the rain chance it will rain
	if (random1 <= ROLL_CHANCE) {
		rained = true;
		// setting the random generated number modded by the max rain amount plus 1
		downpour = random2 % MAX_DOWNPOUR + 1;
	}
	else {
		// stting to neutral default values if it hasn't rained
		rained = false;
		downpour = 0;
	}

	// setting the random generated number modded by the max sunlight amount
	sunlight = random3 % MAX_SUNLIGHT;

}

bool Weather::getRained() {
	return rained;
}

uint16_t Weather::getDownpour() {
	return downpour;
}

uint16_t Weather::getSunlight() {
	return sunlight;
}