#pragma once
class Food
{
private:
	int locationX; // stores the X location
	int locationY; // stores the Y location
	bool edible; // stores weather the food is available to be eaten

public:

	void setLocationX(int X); // sets the locationX variable with an int value given by X
	void setLocationY(int Y); // sets the locationY variable with an int value given by Y
	void eaten(); // sets variable edible to false
	void newRound(); // sets variables so the creature is ready for the next round in the program

	int getLocationX(); // returns the locationX variable
	int getLocationY(); // returns the locationY variable

	bool isEdible(); // returns weather the food is edible or not

	Food();
	~Food();
};

