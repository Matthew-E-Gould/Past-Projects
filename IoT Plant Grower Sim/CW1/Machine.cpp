#include "Classes.h"

using namespace std;

Machine::Machine(Authenticator &a, Plant(&p)[5], Soil &s, Weather &w)
{
	on = false;
	plants = 0;
	for (uint16_t i = 0; i < CAPACITY; i++) {
		freeSlot[i] = true;
	}
	moistureInput = 5;
	year = 0;
	month = 0;
	day = 1;

	pAuthenticator = &a;

	for (int i = 0; i < CAPACITY; i++) {
		pPlant[i] = &p[i];
	}

	pSoil = &s;
	pWeather = &w;
}
// setting everythhing to useless values so no information can be gathered from the program
Machine::~Machine()
{
	for (uint16_t i = 0; i < CAPACITY; i++) {
		pPlant[i] = nullptr;
		freeSlot[i] = false;
	}
	pSoil = nullptr;
	pWeather = nullptr;
	pAuthenticator = nullptr;

	newDay = false;
	offAfterDay = false;
	tempInt = 0;
	tempStr = "nothing";

	torf = false;
	on = false;
	hasRained = false;

	plants = 0;
	temp = 0;
	moistureInput = 0;

	year = 0;
	month = 0;
	day = 0;

}

bool Machine::isOn() {
	return on;
}
bool Machine::slotIsFree(uint16_t slot) {
	return freeSlot[slot];
}
bool Machine::getOffAfterDay() {
	torf = offAfterDay;
	offAfterDay = false;
	return torf;
}

void Machine::rainCheck(bool rained) {
	hasRained = rained;
}
void Machine::changeMachineState(bool stateChange){
	on = stateChange;
}
void Machine::addPlant(uint16_t x) {
	// making the machine add a plant and recognise it's existance
	temp = 0;
	for (int i = 0; i < 5 && !freeSlot[i]; i++) {
		temp = i+1;
	}

	freeSlot[temp] = false;
	plants++;

	pPlant[x]->newPlant(Random16Bit());

}
void Machine::removePlant(uint16_t plant) {
	// making the machine remove a plant and recognise it's lack of existance
	freeSlot[plant] = true;
	plants--;

}
void Machine::wateringAmount(uint16_t water) {
	moistureInput = water;
}
void Machine::turnOff() {
	on = false;
}
void Machine::updateDate() {
	// updating the date, if days = 31 month increases, if month is = 13 year increases
	day++;
	if (day == 31) {
		month++;
		day = 0;
	}
	if (month == 13) {
		year++;
		month = 0;
	}
	if (year == UINT64_MAX) {
		cout << "MAX Year Reached, removing 1 from year value\n";
		year = UINT64_MAX - 1;
	}

}

// just a bunch of getters, the get stuff for other parts of the machine
uint16_t Machine::getPlantCount() {
	return plants;
}
uint16_t Machine::getwateringAmount(){
	return moistureInput;
}
uint16_t Machine::waterSoil(uint16_t soilMoisture){
	if (moistureInput > soilMoisture);
	{
		soilMoisture = moistureInput;
	}
	return soilMoisture;
}

uint64_t Machine::getYear() {
	return year;
}
uint16_t Machine::getMonth() {
	return month;
}
uint16_t Machine::getDay() {
	return day;
}

void Machine::main() {
	// if the machine is on then the program runs
	if (on) {
		//setting to new day to false, this will be turned to true when user is done doing their stuff...
		newDay = false;
		while (!newDay) {

			// makes sure there is atleast 1 plant in the machine before it is run, if there isn't machine will ask user if they want to add a plant
			if (getPlantCount() == 0) {

				NoPlants();

			}
			else {
				// giving a menu of what the user wants to do
				cout << "\nwhat would you like to do?\n";
				cout << "[1] Add a plant\n";
				cout << "[2] Remove a plant\n";
				cout << "[3] Fertilise soil\n";
				cout << "[4] Set water amount\n";
				cout << "[5] List stats\n";
				cout << "[6] Done for today\n";
				cout << "[7] Turn off device after fertilising and watering plants\n";

				InputCheck(tempInt, 1, 7);

				cout << endl;
				// making the function that the user wants to run, run
				if (tempInt == 1) {				
					Opt1();
				}
				else if (tempInt == 2) {
					Opt2();
				}
				else if (tempInt == 3) {
					// security feature, makes sure that user is allowed to access this part of the program bacuase it affect the growth rate of the plants if user has already logged in during this session they don't have to log in again
					pAuthenticator->authenticate();
					if (pAuthenticator->authenticated) {
						Opt3();
					}
				}
				else if (tempInt == 4) {
					// security feature, makes sure that user is allowed to access this part of the program bacuase it affect the growth rate of the plants if user has already logged in during this session they don't have to log in again
					pAuthenticator->authenticate();
					if (pAuthenticator->authenticated) {
						Opt4();
					}
				}
				else if (tempInt == 5) {
					Opt5();
				}
				else if (tempInt == 6) {					
					Opt6();
				}
				else if (tempInt == 7) {					
					Opt7();
				}
				else {
					cout << "ERROR, option overflow\n";
				}
			}
		}
	}
}

void Machine::NoPlants() {
	// asking the user if they want to add a plant to the system
	string tempStr;

	cout << "There are no plants in the machine, do you want to plant a plant [y/n]: ";
	
	cin >> tempStr;
	// input validation
	while (tempStr != "y" && tempStr != "Y" && tempStr != "n" && tempStr != "N") {
		cout << "ERROR: Enter either [y/Y/n/N]: ";
		cin >> tempStr;
	}

	if (tempStr == "y" || tempStr == "Y") {
		// adding plant to the first slot
		addPlant(0);

	}
	else { // if the user doesnt want to add a plant to the machine the machine will ask it if the user wants to turn the machine off
		cout << "would you like to turn the machine off [y/n]: ";
		
		cin >> tempStr;

		while (tempStr != "y" && tempStr != "Y" && tempStr != "n" && tempStr != "N") {
			cout << "ERROR: Enter either [y/Y/n/N]: ";
			cin >> tempStr;
		}

		if (tempStr == "y" || tempStr == "Y") {

			changeMachineState(false);

		}
	}

}

// random number generator of 16 bits
uint16_t Machine::Random16Bit() {
	srand(time(NULL));
	uint16_t random = rand() % UINT16_MAX;
	return random;
}

//these are the functions for the options that the user is given in machine.main(); Opt1 means option 1, Opt2 means option 2 etc...
void Machine::Opt1() {

	if (getPlantCount() == CAPACITY) {
		//if the plant count is the same as the capacity return an error
		cout << "NOTICE: There are no places in the machine left, please remove a plant to add another\n";

	}
	else if ((getPlantCount() > CAPACITY)) {
		//if (somehow) the plant count is higher than the capacity return an error
		cout << "ERROR: too many plants in machine\n";

	}
	else {
		// if no errors are thrown add a plant
		for (uint16_t i = 0; i < CAPACITY; i++) {

			if (slotIsFree(i)) {
				tempInt = i;
				i = CAPACITY;
			}

		}

		addPlant(tempInt);
		cout << "A plant has been added.\n"; // inform user that a plant was added

	}

}

void Machine::Opt2() {

	cout << "Which plant would you like to remove?\n";

	for (tempInt = 0; tempInt < CAPACITY; tempInt++) {
		// listing waht plants are in the machine and what their height is
		if (!slotIsFree(tempInt)) {
			cout << "Plant [" << tempInt + 1 << "], with height of " << pPlant[tempInt]->getheight() << "mm.\n";
		}

	}
	// informing user how to quit process if they decide not to remove plant
	cout << "[6] to cancel.\n";

	cin >> tempInt;

	if (tempInt == 6) {

		cout << "No plant will be removed.\n";

	}
	else {
		// making sure the input is within a valid range and that there is actually a plant in that slot of the machine
		while (tempInt < 1 || tempInt > 5 || slotIsFree(tempInt - 1)) {
			cin.clear();
			cin.ignore();
			cout << "ERROR: please enter a value between 1 and 5 that has a plant in it: ";
			cin >> tempInt;

		}
		// removing plant from the machine, temp int gets 1 removed from itself because the interface shows the range as 1-5 rather than 0-4 (how arrays work)
		pPlant[tempInt - 1]->digUp();
		removePlant(tempInt - 1);

	}

}
void Machine::Opt3() {

	cout << "Fertilising soil increases the rate that all plants grow for a certain amount of time.\nAre you sure you want to fertilise the soil [y/n]: ";
	cin >> tempStr;
	while (tempStr != "y" && tempStr != "Y" && tempStr != "n" && tempStr != "N") {
		cout << "ERROR: Enter either [y/Y/n/N]: ";
		cin >> tempStr;
	}
	if (tempStr == "y" || tempStr == "Y")
	{
		// fertilising the soil if the user wants to
		pSoil->fertilise();

	}

}
void Machine::Opt4() {
	// informing the user what the amounts of watering do... and getting the value they want... the user is allowed to input the same value as it already was and thats taken as do not cahnge anything.
	cout << "Set watering intensity in a range of 0 - 10," <<
		"\n[0] No watering by the device," <<
		"\n[5] Default, Ideal watering by device," <<
		"\n[10] Overwatering," <<
		"\n[" << getwateringAmount() << "] current value,"
		"\nDevice will stop watering soil when soil reaches a relative moisture content.\n";
	// making sure that the entered value is within range
	InputCheck(tempInt, 0, 10);
	// setting the amount htat the user wants the plants to be watered
	wateringAmount(tempInt);

}
void Machine::Opt5() {

	for (tempInt = 0; tempInt < CAPACITY; tempInt++) {
		// this will list all the stats of the plants that are in the machine
		if (!slotIsFree(tempInt)) {
			cout << "Plant [" << tempInt + 1 << "], with height of " << pPlant[tempInt]->getheight() << "mm.\n";
		}
		else { 
			cout << endl;
		}

	}
	// informing the user if the ground is currently fertilised
	if (pSoil->getFertilised()) {
		cout << "The ground is fertilised\n";
	}
	else {
		cout << "The ground is not fertilised\n";
	}

}
void Machine::Opt6() {
	// sets the machine so it will end all options
	newDay = true;

}
void Machine::Opt7() {
	// sets the machine so it will end all options & trun off
	newDay = true;
	offAfterDay = true;

}

void Machine::InputCheck(uint16_t &input, uint16_t min, uint16_t max) {
	// validation of input check
	cin >> input;

	while (input < min || input > max || cin.get() != '\n') { // cin.get() removes some cases of it looping without user being able to input value
		cin.clear();
		cin.ignore(); // cin.clear() & cin.ignore() removes the other cases of it looping without user being able to input value
		cout << "ERROR: please enter a value between " << min << " and " << max << ": "; // informing the user on what hte desired max&min are
		cin >> input;
	}
}