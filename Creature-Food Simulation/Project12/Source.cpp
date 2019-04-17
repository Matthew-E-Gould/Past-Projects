#include <Windows.h>
#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include "RandomNumber.h"
#include "Console.h"
#include "Food.h"
#include "Creature.h"
#include "Borders.h"

using namespace std;

void BorderSetup(const int, Console, Borders);
void WaitForUser(const int, Console, bool);
void CreatureLocation(const int, const int, RandomNumber, Creature[], bool);
void FoodLocation(const int, const int, RandomNumber, Food[], bool);
void CreatureFeed(const int, const int, Food[], Creature[]);

int FoodCrushing(int, int, const int, const int, const int, const int, Console, Food[], Creature[]);
int DisplayCreature(int, int, const int, const int, const int, Console, Creature[]);
int BorderType();

bool Stepping();
bool Stability();

int main() {

	const int GRID = 29; // affects the length (X&Y) of the grid
	const int CREATURE_AMOUNT = 900; // affect how many creatures will display [MAX is GRID + 1 squared]
	const int FOOD_AMOUNT = 7; // affects how many food will display [MAX is GRID + 1 squared]
	const int WINDOW_WIDTH = GRID + 8; // affects the height of thewindow
	const int WINDOW_HEIGHT = GRID + 11; // affects the width of thw window
	const int KILL_FEED = GRID + 2; // affects where the kill feed is shown
	const int BOTTOM = WINDOW_HEIGHT - 2; // for use with system("pause")
	const int MAX_FEED = BOTTOM - KILL_FEED - 3; // affects how many lines are shown in the kill feed
	
	const string FOOD = "F"; // affects how the food is displayed

	int killedCreatures = 0; // variable that stores how many creatures have been killed
	int round = 0; // variable that stores how many rounds that have passed

	bool viewEachStep = true; // statement that stores if the user wants to see each step of the simulation
	bool eachIsUnique; // statement that stores if each object will have its own location

	//setting up and initialising objects
	Console GUI(WINDOW_WIDTH, WINDOW_HEIGHT);
	Creature creature[CREATURE_AMOUNT];
	Food food[FOOD_AMOUNT];
	RandomNumber RNG;
	RNG.initialiseSeed();

	// asking user if they want to view each step of the simulation
	viewEachStep = Stepping();
	eachIsUnique = Stability();

	Borders gridBorder(BorderType());

	GUI.clear();

	// setting up grid border
	BorderSetup(GRID, GUI, gridBorder);

	// setting up creature locations
	CreatureLocation(CREATURE_AMOUNT, GRID, RNG, creature, eachIsUnique);

	// displaying creature locations
	DisplayCreature(killedCreatures, round, CREATURE_AMOUNT, KILL_FEED, MAX_FEED, GUI, creature);

	WaitForUser(BOTTOM, GUI, true);

	// dropping food and updating creatures
	while (killedCreatures < CREATURE_AMOUNT) {

		GUI.gotoXY(GRID + 2, 0);
		cout << "Round:";
		GUI.gotoXY(GRID + 2, 1);
		cout << round;

		// setting up food locations
		FoodLocation(FOOD_AMOUNT, GRID, RNG, food, eachIsUnique);

		// killing creatures if food lands on them
		killedCreatures = FoodCrushing(killedCreatures, round, FOOD_AMOUNT, CREATURE_AMOUNT, KILL_FEED, MAX_FEED, GUI, food, creature);

		// displaying food locations
		for (int i = 0; i < FOOD_AMOUNT; i++) {
			GUI.gotoXY(food[i].getLocationX(), food[i].getLocationY());
			GUI.setColour(GUI.LIGHT_GREEN, GUI.BLACK);
			cout << FOOD;
			GUI.setColour(GUI.WHITE, GUI.BLACK);
		}

		// creatures eat food & get/lose energy
		CreatureFeed(FOOD_AMOUNT, CREATURE_AMOUNT, food, creature);

		// killing creatures and updating display
		killedCreatures = DisplayCreature(killedCreatures, round, CREATURE_AMOUNT, KILL_FEED, MAX_FEED, GUI, creature);

		WaitForUser(BOTTOM, GUI, viewEachStep);

		//prepairing food & creatures for next round
		for (int i = 0; i < FOOD_AMOUNT; i++) {
			food[i].newRound();
		}
		for (int i = 0; i < CREATURE_AMOUNT; i++) {
			creature[i].newRound();
		}

		// removing food from grid
		for (int i = 0; i < FOOD_AMOUNT; i++) {
			GUI.gotoXY(food[i].getLocationX(), food[i].getLocationY());
			cout << " ";
		}

		round++;
	}

	WaitForUser(BOTTOM, GUI, true);
	return 0;
}

void BorderSetup(const int GRID, Console border, Borders borderType) {

	const int BORDER = GRID + 1; // for use as the border of the grid
	char borderV = borderType.GetVBorder();
	char borderC = borderType.GetCBorder();
	char borderH = borderType.GetHBorder();
	// verticle border, corner border, horizontal border

	for (int i = 0; i < BORDER; i++) {
		border.gotoXY(BORDER, i);
		cout << borderV;
		border.gotoXY(i, BORDER);
		cout << borderH;
	}
	border.gotoXY(BORDER, BORDER);
	cout << borderC;
}
void WaitForUser(const int BOTTOM, Console GUI, bool step) {
	if (step) {
		GUI.gotoXY(0, BOTTOM);
		system("pause");
	}
	GUI.gotoXY(0, BOTTOM);
	cout << "Running . . .                  ";
}
void CreatureLocation(const int CREATURES, const int GRID, RandomNumber RNG, Creature creature[], bool ownLocation) {

	bool unique;
	int xLocation;
	int yLocation;

	for (int i = 0; i < CREATURES; i++) {
		xLocation = RNG.random(0, GRID);
		yLocation = RNG.random(0, GRID);

		if (ownLocation) {
			// makes sure two objects cant occupy the same space
			unique = false;
			while (unique == false) {
				for (int j = 0; j < i + 1 || unique == false; j++) {
					if (xLocation == creature[j].getLocationX() && yLocation == creature[j].getLocationY()) {
						unique = false;
					}
					else {
						unique = true;
					}
				}
				if (unique == false) {
					xLocation = RNG.random(0, GRID);
					yLocation = RNG.random(0, GRID);
				}
			}
		}
		creature[i].setLocationX(xLocation);
		creature[i].setLocationY(yLocation);
	}
}
void FoodLocation(const int FOODS, const int GRID, RandomNumber RNG, Food food[], bool ownLocation) {
	
	bool unique;
	int xLocation;
	int yLocation;

	for (int i = 0; i < FOODS; i++) {
		xLocation = RNG.random(0, GRID);
		yLocation = RNG.random(0, GRID);

		if (ownLocation) {
			// makes sure two objects cant occupy the same space
			unique = false;
			while (unique == false) {
				for (int j = 0; j < i + 1 || unique == false; j++) {
					if (xLocation == food[j].getLocationX() && yLocation == food[j].getLocationY()) {
						unique = false;
					}
					else {
						unique = true;
					}
				}
				if (unique == false) {
					xLocation = RNG.random(0, GRID);
					yLocation = RNG.random(0, GRID);
				}
			}
		}
		food[i].setLocationX(xLocation);
		food[i].setLocationY(yLocation);
	}
}
void CreatureFeed(const int FOODS, const int CREATURES, Food food[], Creature creature[]) {

	const int DISTANCE = 5;

	int distanceX;
	int distanceY;

	for (int i = 0; i < CREATURES; i++) {
		for (int j = 0; j < FOODS; j++) {
			if (creature[i].isAlive() && creature[i].hasEaten() == false && food[j].isEdible()) {
				distanceX = creature[i].getLocationX() - food[j].getLocationX();
				distanceY = creature[i].getLocationY() - food[j].getLocationY();
				if (sqrt(pow(distanceX, 2) + pow(distanceY, 2)) <= DISTANCE) {
					creature[i].ate(true);
					food[j].eaten();
				}
			}
		}
		if (creature[i].hasEaten() == false && creature[i].isAlive()) {
			creature[i].ate(false);
		}
		// setting creatures to correct energy values (0-9)
		creature[i].energyCheck();
	}
}

int FoodCrushing(int killedCreatures, int round, const int FOODS, const int CREATURES, const int DEATH_FEED, const int MAX, Console GUI, Food food[], Creature creature[]) {

	for (int i = 0; i < FOODS; i++) {

		for (int j = 0; j < CREATURES; j++) {

			if (food[i].getLocationX() == creature[j].getLocationX()
				&& food[i].getLocationY() == creature[j].getLocationY()) {

				if (creature[j].isAlive()) {
					if (killedCreatures > MAX) {
						creature[j].kill();
						GUI.gotoXY(0, DEATH_FEED + MAX + 2);
						killedCreatures++;
						cout << "Creature " << j << " was crushed on turn " << round << " ";
					}
					else {
						creature[j].kill();
						GUI.gotoXY(0, DEATH_FEED + killedCreatures);
						killedCreatures++;
						cout << "Creature " << j << " was crushed on turn " << round;
					}
				}
			}
		}
	}
	return killedCreatures;
}
int DisplayCreature(int killedCreatures, int round, const int CREATURES, const int DEATH_FEED, const int MAX, Console GUI, Creature creature[]) {

	for (int i = 0; i < CREATURES; i++) {
		if (creature[i].isAlive() == true) {
			if (creature[i].getEnergy() <= 0) {
				if (killedCreatures > MAX) {
					GUI.gotoXY(0, DEATH_FEED + MAX + 2);
					killedCreatures++;
					cout << "Creature " << i << " starved on turn " << round << "       ";
					creature[i].kill();
					GUI.gotoXY(creature[i].getLocationX(), creature[i].getLocationY());
					cout << " ";
				}
				else {
					GUI.gotoXY(0, DEATH_FEED + killedCreatures);
					killedCreatures++;
					cout << "Creature " << i << " starved on turn " << round;
					creature[i].kill();
					GUI.gotoXY(creature[i].getLocationX(), creature[i].getLocationY());
					cout << " ";
				}
			}
			else {
				if (creature[i].getEnergy() <= 3) {
					GUI.setColour(GUI.LIGHT_RED, GUI.BLACK);
				}
				else if (creature[i].getEnergy() > 3 && creature[i].getEnergy() <= 6) {
					GUI.setColour(GUI.LIGHT_YELLOW, GUI.BLACK);
				}
				else {
					GUI.setColour(GUI.LIGHT_BLUE, GUI.BLACK);
				}
				GUI.gotoXY(creature[i].getLocationX(), creature[i].getLocationY());
				cout << creature[i].getEnergy();
				GUI.setColour(GUI.WHITE, GUI.BLACK);
			}
		}
	}
	return killedCreatures;
}
int BorderType() {

	int num;

	cout << "\nwhat border type do you want [1/2]:\n";
	cin >> num;
	while (num < 1 || num > 2) {
		cout << "ERROR: Not a valid input,\nPlease enter either 1 or 2:\n";
		cin >> num;
	}

	return num;
}

bool Stepping() {

	string yn;
	bool step;

	cout << "Do you want to view each step of the program? [Y/N]:\n";
	cin >> yn;
	while (yn != "Y" && yn != "y" && yn != "N" && yn != "n") {
		cout << "ERROR: Not a valid input,\nPlease enter [Y/y/N/n]:\n";
		cin >> yn;
	}
	if (yn == "Y" || yn == "y") {
		step = true;
	}
	else {
		step = false;
	}

	return step;
}
bool Stability() {

	string yn;
	bool unique;

	cout << "\nDo you want each creature / food to  have their own space on the grid\n[Y/N]:\n";
	cin >> yn;
	while (yn != "Y" && yn != "y" && yn != "N" && yn != "n") {
		cout << "ERROR: Not a valid input, Please enter [Y/y/N/n]:\n";
		cin >> yn;
	}
	if (yn == "Y" || yn == "y") {
		unique = true;
	}
	else {
		unique = false;
	}

	return unique;
}