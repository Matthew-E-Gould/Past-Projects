#include "Classes.h"



Soil::Soil()
{
	fertilised = false;
	fertiliserAmount = 1;
	moisture = 5;
}

Soil::~Soil()
{
}

void Soil::nextDay(uint16_t rainAmount, bool rained, uint16_t sunlight) {

	if (rained) {

		sunlight = sunlight / 2; // if it rains the suns intensity is halved meaning that it was a cooler day.

		// checking if the moisture would go negative if calculation is run
		if ((moisture + rainAmount) > sunlight) {
			moisture = moisture + rainAmount - sunlight;
		}
		else {
			moisture = 0;
		}
	}
	else {
		// checking if the moisture would go negative if calculation is run
		if (moisture > sunlight) {
			moisture = moisture - sunlight;
		}
		else {
			moisture = 0;
		}
	}

	// setting moisture to max value if higher than max value
	if (moisture > 10) {
		moisture = 10;
	}
}

void Soil::endDay(double plantCount) {


	if (fertilised) {

		// editing how mach the plants absorb the fertiliser&moisture... the higher the divider the less they absorb
		plantCount = plantCount / 1.5;

		// making sure that plants dont case a value loop in the moisture
		if (moisture < plantCount) {
			moisture = 0;
		}
		else { // making plant absorb water down to how many plant there are
			moisture -= plantCount;
		}

		fertiliserAmount -= (FERTILISER_DECAY * plantCount);

		// making sure that the plants don't absorb too much
		if (fertiliserAmount <= 1) {
			fertilised = false;
			fertiliserAmount = 1;
		}
	}
	else {

		plantCount = plantCount / 3;

		if (moisture < plantCount) {
			moisture = 0;
		}
		else {
			moisture -= plantCount;
		}
	}

}

void Soil::fertilise() {

	fertilised = true;

	if (fertiliserAmount < (DBL_MAX - 2)) {

		if (fertiliserAmount > 1) {

			fertiliserAmount = fertiliserAmount + 0.5;

		}
		else {
			fertiliserAmount = DBL_MAX - 2;
		}

	}
}

void Soil::water(uint16_t watered) {
	moisture = watered;
}

bool Soil::getFertilised() {
	return fertilised;
}

double Soil::getFertiliseValue() {
	return fertiliserAmount;
}
double Soil::getMoistureValue() {
	return moisture;
}