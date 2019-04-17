#pragma once
class Borders
{
private:
	int BorderType;

public:
	int GetVBorder(); // sets the char code for the verticle borders
	int GetCBorder(); // sets the char code for the corner borders
	int GetHBorder(); // sets the char code for the horizontal borders
	// all the Get_Border arguments have the preconditions of the number 1 or 2

	Borders(int BorderNum);
	~Borders();
};

