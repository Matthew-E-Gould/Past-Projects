#include "Classes.h"

Plant::Plant() {
	digUp();
}
Plant::~Plant() {
}

uint32_t Plant::getheight() {
	return height;
}

void Plant::nextDay(bool fertilised, uint16_t moisture, uint16_t sunlight, double fertiliser) {
	
	if (height < UINT64_MAX - 30) {
		// setting ferterliser to 1.5 so the maximum multiplier is 1.5, excess just allows the plants to be ferterlised for longer
		if (fertiliser > 1.5) {
			fertiliser = 1.5;
		}
		if (sunlight == 0) {
			sunlight = 1;
		}
		// making plants grow down to how much moisture there is, the amout of water in soil affects rate of growth
		if (moisture > 4 && moisture < 6) {

			if (fertilised) {
				fertiliser = (sunlight * fertiliser * 1.25);
			}
			else {
				fertiliser = (sunlight * 1.25);
			}

			height += fertiliser;

		}
		else if (moisture > 3 && moisture < 7) {

			if (fertilised) {
				fertiliser = (sunlight * fertiliser * 1);
			}
			else {
				fertiliser = (sunlight * 1);
			}

			height += fertiliser;

		}
		else if (moisture > 2 && moisture < 8) {

			if (fertilised) {
				fertiliser = (sunlight * fertiliser * 0.6);
			}
			else {
				fertiliser = (sunlight * 0.6);
			}

			height += fertiliser;

		}
		else if (moisture >= 0 && moisture <= 10) {

			if (fertilised) {
				fertiliser = (sunlight * fertiliser * 0.2);
			}
			else {
				fertiliser = (sunlight * 0.2);
			}

			height += fertiliser;

		}
	}

}

void Plant::newPlant(uint16_t random) {
	height = (random % 99) + 1; // setting the plants height from 1 to 100 
	alive = true;
}

void Plant::digUp() {
	height = 0;
	alive = false;
}

bool Plant::isAlive() {
	
	return alive;

}