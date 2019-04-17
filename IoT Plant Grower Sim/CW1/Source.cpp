#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "Classes.h"

using namespace std;

uint16_t Random16Bit(); // generates a random 16 bit value
void InputCheck(uint16_t &i, uint16_t min, uint16_t max);
void turnOn(Machine &m, Weather &w);

int main() {

	const uint16_t PLANTS = 5;

	bool running = true;
	bool newDay = false;
	bool torf;

	string tempStr;

	uint16_t tempInt = 0;

	Plant plant[PLANTS];
	Soil soil;
	Weather weather(Random16Bit(), Random16Bit(), Random16Bit());
	Authenticator authenticator;
	Machine machine(authenticator, plant, soil, weather);
	DataLoadSave data(machine, plant);

	// loading data from a file
	cout << "LAST SAVE DATA:\n";
	data.readD();
	cout << "\n\n";

	while (running) {

		// generating new day data for soil and weather, consists of a securely randomly generated number being inputted and the soil reacting to that.
		weather.nextDay(Random16Bit(), Random16Bit(), Random16Bit());
		soil.nextDay(weather.getDownpour(), weather.getRained(), weather.getSunlight());

		// user deicdes if they want to turn the machine on, if not a day passes
		turnOn(machine, weather);

		// running the machines interface
		machine.main();

		// saving and appending data
		data.saveD();
		data.appendD();

		// watering soil
		soil.water(machine.waterSoil(soil.getMoistureValue()));

		// growing plants
		for (int i = 0; i < PLANTS; i++) {
			if (plant[i].isAlive()) {
				plant[i].nextDay(soil.getFertilised(), soil.getMoistureValue(), weather.getSunlight(), soil.getFertiliseValue());
			}
		}

		// updating soil moisture and fertilisation
		soil.endDay((double)machine.getPlantCount());

		// turning off machine if user requested it
		if (machine.getOffAfterDay()) {
			machine.turnOff();
			authenticator.turnedOff();
		}

		// updating the date in the machine
		machine.updateDate();

		// asking validator if the want to end the simulation of the plant waterer
		cout << "\n\tEND PROGRAM? [Y/N]";
		cin >> tempStr;

		while (tempStr != "y" && tempStr != "Y" && tempStr != "n" && tempStr != "N") {
			cout << "ERROR: Enter either [y/Y/n/N]: ";
			cin >> tempStr;
		}

		if (tempStr == "y" || tempStr == "Y") {

			running = false;

		}

	}

	system("pause");
	return 0;
}

// generates a random number between 0 and 2^16
uint16_t Random16Bit() {
	srand(time(NULL));
	uint16_t random = rand() % UINT16_MAX;
	return random;
}

// checks if the input is valid
void InputCheck(uint16_t &i, uint16_t min, uint16_t max) {

	cin >> i;

	while (i < min || i > max || cin.get() != '\n') {
		cin.clear();
		cin.ignore();
		cout << "ERROR: please enter a value between " << min << " and " << max << ": ";
		cin >> i;
	}
}

// asking if the user wants to turn the machine on or off. and does so.
void turnOn(Machine &m, Weather &w) {

	string tempStr;


	if (m.isOn()) {
		m.rainCheck(w.getRained());
	}
	else {
		cout << "Turn device on? [y/n]: ";
		cin >> tempStr;

		while (tempStr != "y" && tempStr != "Y" && tempStr != "n" && tempStr != "N") {
			cout << "ERROR: Enter either [y/Y/n/N]: ";
			cin >> tempStr;
		}

		if (tempStr == "y" || tempStr == "Y") {

			m.changeMachineState(true);
			tempStr.clear();

		}
	}
}

/*
Set up weather
Set up machine
Set up soil
Randomise the initial weather
Make soil affected by weather
	//START while loop
		//IF machine is off
		Ask user if they want to turn on the machine
		//IF machine is on
		see if it rained
	System logs date
		//WHILE torf
		Machine asks user if they want to plant plants
		//IF machine has free spaces left && user says yes
		Machine adds plant to lowest vector
		//IF machine has no free spaces left && user says yes
		Inform user the machine has no spaces left
		set torf to false
		//IF user says no
		set torf to false
		//END of WHILE
		//FOR each plant
		Machine tests soil moisture
		Machine measures plant height and informs user
		Machine logs height
		Machine informs user and asks what they want to do
			//IF user wants to change plants desired moisture
			Asks user to input desired (water resistivity)
			//IF user wants to dig up plant
			Remove plant from machine (vector)
			//IF user wants to fertilise plant
			fertilise plant
		Machine waters plant IF it needs it
		Machine logs moisture levels whether plant was watered & fertilised
		torf = true		
	ask user if they want to stop
		//if yes set running = false
	//END while loop if running == false
Return 0;


Weather 1 _ 1 Machine													Weather 1 _ * Machine
   1		1	1														   1		*	*
   |  _____/	|		OR (if there are mutiple machines allowed)		   |  _____/	|<== Plant/Machine allocation
   1 1			*														   1 1			*
Soil 1 ____ * Plant														Soil 1 ____ * Plant

*/