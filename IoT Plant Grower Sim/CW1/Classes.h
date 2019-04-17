#include <cinttypes>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

#pragma once

using namespace std;

// listing all classes so they can be infered in the use of other classes
class Authenticator;
class Soil;
class Plant;
class Weather;
class Machine;
class DataLoadSave;

class Authenticator
{
public:
	friend class Machine;

	Authenticator();
	~Authenticator();

	void authenticate(); // function that will uthentiucate if uName and uPass are correct
	void validateUser(); // functiuon that will ask for the inputs of uName and Upass
	void turnedOff(); // logs user out when the machine is turned off

private:

	map<string, string>Users; // map for username and passwords

	bool authenticated = false; // boolean of if the user is aquthenticated or not

	string uName = "A"; // username
	string uPass = "A"; // password
};

class Soil
{
public:

	Soil();
	~Soil();

	void nextDay(uint16_t rainAmount, bool rained, uint16_t sunlight); // function that will update the soils moisture down to what the environment is like.
	void endDay(double plantCount); // function that will work out the fertilisation of siol after plants have grown for the day
	void fertilise(); // function that will fertilise the soil
	void Soil::water(uint16_t watered); // function that will water the soil down to what the machine waters

	bool getFertilised(); // function that will return weather the soil is fertilised or not

	double getFertiliseValue(); // function that will tell the machine what the fertilisation of the soil is
	double getMoistureValue(); // function that will tell the machine what the moisture of the soil is

private:
	bool fertilised = false; // boolean that sets if plant has been fertilised

	const double FERTILISER_DECAY = 0.1; // sets the rate of decay of the fertiliser in the soil
	double fertiliserAmount = 0;
	double moisture = 0; // actual moisture of soil, range from 0 to 10, 0 is no moisture & 10 is oversaturated

};

class Plant
{
public:

	Plant();
	~Plant();

	uint32_t getheight(); // returns height of the plant

	void nextDay(bool fertilised, uint16_t moisture, uint16_t sunlight, double fertiliser); // grows the plant down to the enviroment
	void newPlant(uint16_t random); // intialises a new plant when it is added to the machine
	void digUp(); // removes the plant from the machine
	bool isAlive(); // returns if the plant is alive or not

private:
	uint64_t height = 0; // height of the plant in mm

	double moistureIntake = 0; // moisture intake of the plant

	bool alive = false; // states whether the plant is alive or not

};

class Weather
{

public:
	Weather(uint16_t random1, uint16_t random2, uint16_t random3);
	~Weather();

	void nextDay(uint16_t random1, uint16_t random2, uint16_t random3); // setting up the next day, Overload 1 is if it has rained, Overload 2 is how much it's rained, Overload 3 is how much sunlight there has been

	bool getRained(); // returns whether it has rained or not

	uint16_t getDownpour(); // returns how much has rained
	uint16_t getSunlight(); // retuens how sunny it was

private:
	bool rained; // bool for if it has rained

	uint16_t downpour = 0; // how much it has  rained in mm
	uint16_t sunlight = 0; // how much sunlight there has been

	const uint16_t ROLL_MAX = 7; // chance of it not raining +1
	const uint16_t ROLL_CHANCE = 1; // chance of it raining
	const uint16_t MAX_DOWNPOUR = 9; // maximum downpour in mm
	const uint16_t MAX_SUNLIGHT = 4; // maximum sunlight

};

class Machine
{
public:

	friend Authenticator;
	friend Plant;
	friend Soil;
	friend Weather;

	Machine(Authenticator &a, Plant(&p)[5], Soil &s, Weather &w);
	~Machine();

	bool isOn(); // returns if the machine is turned on or not for other components to use
	bool slotIsFree(uint16_t slot); // returns if a slot in the mchine is free or not
	bool getOffAfterDay(); // returns if the machine is going to be turned off after the day

	void changeMachineState(bool stateChange); // user turning the machine on or off
	void turnOff(); // same as above but doesnt require an input 

	void addPlant(uint16_t x); // adds a plant to the machine
	void removePlant(uint16_t plant); // removes a plant from the machine
	uint16_t getPlantCount(); // returns the count of the plants

	uint16_t getwateringAmount(); // returns how much the machine is watering soil
	void rainCheck(bool rained); // machine sees if it rains and if so how much it has rained

	uint16_t Machine::waterSoil(uint16_t soilMoisture); // machine waters soil down to how moist the soil already is
	void wateringAmount(uint16_t water); // machine gets given how much it needs to water soil by user.

	void updateDate(); // updates the date
	uint64_t getYear(); // returns year
	uint16_t getMonth(); // returns date
	uint16_t getDay(); // returns day

	void main(); // main user interaction
	void NoPlants(); // UI for if there are no plantsw in the machine
	void Opt1(); // UI for if the user selects relative option in main()
	void Opt2(); // UI for if the user selects relative option in main()
	void Opt3(); // UI for if the user selects relative option in main()
	void Opt4(); // UI for if the user selects relative option in main()
	void Opt5(); // UI for if the user selects relative option in main()
	void Opt6(); // UI for if the user selects relative option in main()
	void Opt7(); // UI for if the user selects relative option in main()

	// validation of user inputs:
	void InputCheck(uint16_t &input, uint16_t min, uint16_t max); // validation for a neumerical input

private:

	Plant* pPlant[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
	Soil* pSoil = nullptr;
	Weather* pWeather = nullptr;
	Authenticator* pAuthenticator = nullptr;

	bool newDay = false; // bool for the machine to know if a day has passed
	bool offAfterDay = false; // bool for if the user wants the machine to turn off after the day has ended
	uint16_t tempInt = 0; // temporary integer
	uint16_t Random16Bit(); // random number generator of 16 bits
	const uint16_t CAPACITY = 5; // maximum amout of plants allowed in machine
	string tempStr = "A"; // temporary string

	bool torf = false; // temporary bool value
	bool on = false; // boolean statement for wether the machine is on or off
	bool hasRained = false; //
	bool freeSlot[5] = {false, false, false, false, false}; // plants in machine (max 5)

	uint16_t plants = 0; // count of plants in machine
	uint16_t temp = 0; // temporary value
	uint16_t moistureInput = 0; // moisture added to the soil by the machine

	uint64_t year = 0; // current year storage
	uint16_t month = 0; // current month storage
	uint16_t day = 0; // current day storage

};

class DataLoadSave
{
public:
	friend Machine;
	friend Plant;

	DataLoadSave(Machine &m, Plant(&p)[5]);
	~DataLoadSave();

	void appendD(); // appends data to file << this is my logger FYI
	void readD(); // reads data from file
	void saveD(); // saves data to file

private:

	Machine* pMachine = nullptr;
	Plant* pPlant[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };

	ofstream append;
	ofstream save;
};