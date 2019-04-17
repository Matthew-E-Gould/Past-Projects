#pragma once
class Creature
{
private:
	int locationX; // stores the X location
	int locationY; // stores the Y location
	int energy; // stores the energy value
	bool alive;  // boolian statement defining weather the creature is alive or not
	bool fed; // boolian statement defining weather the creature has eaten or not

public:
	void setLocationX(int X); // sets the locationX variable with an int value given by X
	void setLocationY(int Y); // sets the locationY variable with an int value given by Y
	void ate(bool tOrF); // boolian argument that dictates weather or not the creature has eaten in the current round
	void kill(); // kills the creature by setting the alive variable to false
	void energyCheck();  // sets the energy values to either 0 or 9 depening if it is out of these boundries
	void newRound(); // sets variables so the creature is ready for the next round in the program

	int getLocationX(); // returns the locationX variable
	int getLocationY(); // returns the locationX variable
	int getEnergy(); //  returns the energy variable

	bool isAlive();  //  returns the alive variable
	bool hasEaten(); // returns the fed variable

	Creature();
	~Creature();
};

