#include "Classes.h"

DataLoadSave::DataLoadSave(Machine &m, Plant (&p)[5]) {

	pMachine = &m;

	for (int i = 0; i < 5; i++) {
		pPlant[i] = &p[i];
	}

}
DataLoadSave::~DataLoadSave() {

	pMachine = nullptr;
	for (uint16_t i = 0; i < 5; i++){
		pPlant[i] = nullptr;
	}

}

void DataLoadSave::appendD(){

	append.open("log.txt", std::ios_base::app); // saying that i want to append to file
	if (append.fail()) { // output error if it has failed opening file
		cout << "ERROR: opening file for appening failed";
	}
	else {
		// appending data in a user friendly format
		append << "--------------------\n";
		append << "Day: " << pMachine->getDay() << endl;
		append << "Month: " << pMachine->getMonth() << endl;
		append << "Year: " << pMachine->getYear() << endl;
		append << "--------------------\n";
		if (pMachine->isOn()) {
			append << "Plant count: " << pMachine->getPlantCount() << endl;
			for (uint16_t i = 0; i < 5; i++) {
				append << "Plant [" << i + 1 << "] height (mm): " << pPlant[i]->getheight() << endl;
			}
		}
		else {
			append << "Machine is off\n";
		}
	}
	append.close();

}

void DataLoadSave::readD(){

	FILE *pLoad = nullptr;

	uint16_t plantCount = 0;
	uint64_t plantHeight[5];

	fopen_s(&pLoad, "system.txt", "r"); // saying that i want to read from file

	if (pLoad == NULL) {
		cout << "NOTICE: No file found\n";
	}
	else {

		int temp = 0;
		temp = fscanf_s(pLoad, "%" PRIu16, &plantCount); // PRIu16 is used because the values passer are of type uint16_t

		for (int i = 0; i < 5; i++) {
			temp += fscanf_s(pLoad, "%" PRIu64 "\n", &plantHeight[i]); // PRIu64 is used because the values passer are of type uint64_t
		}

		if (temp < 0) {
			cout << "Error reading data\n";
		}

		else {

			cout << "plants in machine: " << plantCount << endl;
			for (int i = 0; i < 5; i++) {
				cout << "plant [" << i + 1 << "] height: " << plantHeight[i] << endl;
			}
		}
		fclose(pLoad);
	}

}

void DataLoadSave::saveD(){
	// saving data in a format that is readable to the loadD function
	save.open("system.txt");
	if (save.fail()) {
		cout << "ERROR: opening file for saving failed";
	}
	else {
		save << pMachine->getPlantCount() << endl;
		for (uint16_t i = 0; i < 5; i++) {
			save << pPlant[i]->getheight() << endl;
		}
	}
	save.close();

}
