#include "Borders.h"

// preconditions BorderType must have a value #, either 1 or 2 otherwise it will not return a value
int Borders::GetVBorder(){
	if (BorderType == 1) {
		return 186;
	}
	if (BorderType == 2) {
		return 179;
	}
	return 0;
}
int Borders::GetCBorder(){
	if (BorderType == 1) {
		return 188;
	}
	if (BorderType == 2) {
		return 217;
	}
	return 0;
}
int Borders::GetHBorder(){
	if (BorderType == 1) {
		return 205;
	}
	if (BorderType == 2) {
		return 196;
	}
	return 0;
}

// BorderType is set on creation of the object
Borders::Borders(int BorderNum)
{
	BorderType = BorderNum;
}

Borders::~Borders()
{
}
