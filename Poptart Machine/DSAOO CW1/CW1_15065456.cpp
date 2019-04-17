///////////////////////////////
// Appendix.h
#include <vector>
#include <iostream>
#include <string>

#pragma once

using namespace std;

// StateContext class is prototyped here because StateContext uses State and State uses StateContext.
class StateContext;

// Enumerators are used to keep track of the machine state and the state parameters when changing states
// later in the program the states will be linked to a class and the parameters will be linked to a storage space
enum state { Out_Of_Poptart, No_Credit, Has_Credit, Dispense_Poptart };
enum stateParameter { No_Of_Poptarts, Credit, Cost_Of_Poptart };

// The product class are inherited in both the PoptartType class and Filling class
// it is used to give poptarts their structure and variables.
class Product
{
protected:
	string product_description;
	int itemCost = 0; // setting the default value of itemCost to 0 because values should be initialised

public:
	// Virtual arguments are used so the class can be inherited, the virtual allows variables and functions to
	// be different from the inherited class to the inheritor meaning that you can copy the structure but maintain uniqueness
	virtual int cost(void);
	virtual string description(void);
};

// The Poptart class that is used to inherit from the above product class from the poptart_<type> class
class Poptart : public Product {
public:
	Poptart(void);
};

// The state class handles the various states what the system does when running for example from a Has_Credit state
// compaired to the Dispense_Poptart state but it isn't used to change the state itself
class State {
protected:
	//pointer to store the current system state
	StateContext* CurrentContext;

public:
	State(StateContext* Context) {
		CurrentContext = Context;
	}
	// Class destructor used to dispose of the object once the state is changed
	virtual ~State(void) {}
	virtual void transition(void) {}

};

// Class to change the StateContext to the current system context
class StateContext {
protected:
	State* CurrentState = nullptr;
	int stateIndex = 0;
	// Vectors used to store the various states the system can go through as well as the various parameters
	vector<State*> availableStates;
	vector<int> stateParameters;

public:
	// Destructor for the class to dispose of the objects when they are finsihed with
	virtual ~StateContext(void);
	// Virtual function to set the machine state based off the classes in the vectors
	virtual void setState(state newState);
	// Function returns the current machine state so it can be set in here
	virtual int getStateIndex(void);
	// Function that actually set the parameter from the vector based off the value that is passed
	virtual void setStateParam(stateParameter SP, int value);
	// Function to retrieve the current parameter out of the vector to be used as a value in the program
	virtual int getStateParam(stateParameter SP);

};

// Transiton class to deal with what happens when the program runs a function.
class Transition {
public:
	// Functions that each state of the machine runs
	// Default functionality outputs an error for debugging purpouses and also because functions should be unique
	virtual bool insertMoney(int) { cout << "ERROR!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "ERROR!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "ERROR!" << endl; return false; }
	virtual bool addPoptart(int) { cout << "ERROR!" << endl; return false; }
	virtual bool dispense(void) { cout << "ERROR!" << endl; return false; }
};

// Class for the poptart state, this inherits the state Transition from the State class and the transtion class to
// inherit the above functions
class PoptartState : public State, public Transition {
public:
	PoptartState(StateContext* Context) : State(Context) {}
};

// The class for the OutofPoptart state of the program, should be made to be different from other classes that inherit from PoptartState
class OutOfPoptart : public PoptartState {
public:
	OutOfPoptart(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

//The class for the NoCredit state of the program, should be made to be different from other classes that inherit from PoptartState
class NoCredit : public PoptartState
{
public:
	NoCredit(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

//The class for the HasCredit state of the program, should be made to be different from other classes that inherit from PoptartState
class HasCredit : public PoptartState
{
public:
	HasCredit(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

//The class for the DispensePoptart state of the program, should be made to be different from other classes that inherit from PoptartState
class DispensePoptart : public PoptartState
{
public:
	DispensePoptart(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

// Poptart_Dispenser class represents the poptart dispenser itself,
// The DispensePoptart and HasCredit classes need to access the pointer to the product. Therefore they are friend classes with this class
// giving them access to private values. Friend classes have direct access to the values in the variables.
class Poptart_Dispenser : public StateContext, public Transition
{
	friend class DispensePoptart;
	friend class HasCredit;

private:
	PoptartState* PoptartCurrentState = nullptr; // current state is the current state of the program, should point to a class like NoCredit
	bool itemDispensed = false; // boolean value storing if an item has been dispensed, used for getProduct
	Product* DispensedItem = nullptr; 	// boolean for storing waht item has been created so the program knows how much
										// to charge the customer, the true description of the item and what the item consists of
	bool itemRetrieved = false; // boolean value storing if an item has been taken from the machine, used for getProduct

public:
	Poptart_Dispenser(int inventory_count);
	~Poptart_Dispenser(void);
	bool insertMoney(int money);
	bool makeSelection(int Option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
	Product* getProduct(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);
};

// Destructor for stateContext class that clears the vectors of there states and parameters
StateContext::~StateContext(void) {
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i];
	this->availableStates.clear();
	this->stateParameters.clear();
}

// sets the current state of the program, used for changing whats sate the program is in and therefore change how the program runs
void StateContext::setState(state newState) {
	this->CurrentState = availableStates[newState];
	this->stateIndex = newState; // sets the current state of the program to the passed state
	this->CurrentState->transition();
}

// Return the current machine state
int StateContext::getStateIndex(void) {
	return this->stateIndex;
}

// Sets the value of either [No_Of_Poptarts, Credit, Cost_Of_Poptart] so storage can be used across different states
//														^ however this will not be edited properly
void StateContext::setStateParam(stateParameter SP, int value) {
	this->stateParameters[SP] = value; // sets the stateParameter to the value passed forward via the second overload
}

// Returns the value that is stored in a stateParameter for use with calculations etc.
int StateContext::getStateParam(stateParameter SP) {
	return this->stateParameters[SP];
}

// Class destrcutor to delete the dispensed item pointer once it has been dispensed and collected
Poptart_Dispenser::~Poptart_Dispenser(void) {
	if (!this->itemRetrieved) {
		delete this->DispensedItem; // destroys the pointer DispensedItem
	}
}

// When the insertMoney function is called, Poptart_Dispenser will run the insertMoney function from the current state the Poptart_Dispenser is in
// This fucntion is used to insert cash into the machine
bool Poptart_Dispenser::insertMoney(int money) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->insertMoney(money);
}

// When the makeSelection function is called, Poptart_Dispenser will run the makeSelection function from the current state the Poptart_Dispenser is in
// This function allows the user to make a selection of what poptart they want
bool Poptart_Dispenser::makeSelection(int option) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->makeSelection(option);
}

// When the moneyRejected function is called, Poptart_Dispenser will run the moneyRejected function from the current state the Poptart_Dispenser is in
// This function allows the user to get their cash returned to them when they want to stop using the machine
bool Poptart_Dispenser::moneyRejected(void) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->moneyRejected();
}

// When the addPoptart function is called, Poptart_Dispenser will run the addPoptart function from the current state the Poptart_Dispenser is in
// This function allows the owner of the machine to add poptarts the the machines inventory
bool Poptart_Dispenser::addPoptart(int number) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->addPoptart(number);
}

// When the dispense function is called, Poptart_Dispenser will run the dispense function from the current state the Poptart_Dispenser is in
// This function allows the machine to dispense the poptart for the user to collect
bool Poptart_Dispenser::dispense(void) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->dispense();
}

// The getProduct function is used to reset the status of the system so a poptart can be selected from makeSelection
// this function is effectively a sensor sensing if a poptart / item is in the dispensery
Product* Poptart_Dispenser::getProduct(void) {
	if (this->itemDispensed) {
		// making machine recognise that the item has been taken
		this->itemDispensed = false;
		this->itemRetrieved = true;
		return this->DispensedItem; // returning the despensed item pointer maybe for use in a video gmae or something...
	}
	//Nullptr to reset the poptart pointer ready for new poptart to be created
	return nullptr;
}

// setStateParam is used for setting a value inside the stateParameter
// The vector value and the new value are passed into this function in order to update the state parameter
void Poptart_Dispenser::setStateParam(stateParameter SP, int value) {
	if (SP == Cost_Of_Poptart) return; // if the passed stateParameter is Cost_Of_Poptart then the value can't be edited
	this->stateParameters[SP] = value;
}

// The function that finds the current parameter from the stateParameter vector 
int Poptart_Dispenser::getStateParam(stateParameter SP) {
	if (SP == Cost_Of_Poptart) {
		if (DispensedItem == nullptr) return 0;
		return DispensedItem->cost(); // this will return the cost of the poptart stored in DispensedItem pointer allowing for use of Cost_Of_Poptart without having to pass a value towards it
	}
	return this->stateParameters[SP]; // return the value in the stateParameter passed through as long as it isn't Cost_Of_Poptart
}
// End of Appendix.h
///////////////////////////////

///////////////////////////////
// MY PROGRAM BELOW

///////////////////////////////
// poptart types

// when this is run it will return the itemCost variable in any class that inherits from Product
int Product::cost(void)
{
	return itemCost;
}

// when this is run it will return the product_description variable in any class that inherits from Product
string Product::description(void)
{
	return product_description;
}


Poptart::Poptart(void) {}


class PlainPoptart : public Poptart {
public:
	PlainPoptart(void);
};

PlainPoptart::PlainPoptart(void) {
	itemCost = 100;
	product_description = "plain poptart base";
}

class SpicyPoptart : public Poptart {
public:
	SpicyPoptart(void);
};

SpicyPoptart::SpicyPoptart(void) {
	itemCost = 150;
	product_description = "spicy poptart base";
}


class ChocolatePoptart : public Poptart {
public:
	ChocolatePoptart(void);
};

ChocolatePoptart::ChocolatePoptart(void) {
	itemCost = 200;
	product_description = "chocolate poptart base";
}


class CoconutPoptart : public Poptart {
public:
	CoconutPoptart(void);
};

CoconutPoptart::CoconutPoptart(void) {
	itemCost = 200;
	product_description = "coconut poptart base";
}


class FruityPoptart : public Poptart {
public:
	FruityPoptart(void);
};

FruityPoptart::FruityPoptart(void) {
	itemCost = 200;
	product_description = "fruity poptart base";
}
// end poptart types
///////////////////////////////

///////////////////////////////
// dispenser codes

bool OutOfPoptart::insertMoney(int money)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: No Poptarts in inventory! Returning cash..." << endl;
	return false;
}

bool OutOfPoptart::makeSelection(int option)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: No Poptarts in inventory! Ignoring request..." << endl;
	return false;
}

bool OutOfPoptart::moneyRejected(void)
{
	cout << "Returning " << this->CurrentContext->getStateParam(Credit) << " pence..." << endl; // informing user on how much credit is being returned to them
	this->CurrentContext->setStateParam(Credit, 0); // setting credit in machine to 0 since money has been rejected
	return true;
}

bool OutOfPoptart::addPoptart(int number)
{
	this->CurrentContext->setStateParam(No_Of_Poptarts, number); // setting the parameter No_Of_Poptarts to number
	this->CurrentContext->setState(No_Credit); // setting the state of the machine to No_Credit
	return true;
}

bool OutOfPoptart::dispense(void)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: No Poptarts left! Can't dispense." << endl;
	return false;
}


bool NoCredit::insertMoney(int money)
{
	this->CurrentContext->setStateParam(Credit, money); // setting the credit to the money inserted, this assumes that all past operations are correct and the current credit is 0

	this->CurrentContext->setState(Has_Credit); // setting the state to has credit because there is now credit in the machine

	cout << "Balance: " << this->CurrentContext->getStateParam(Credit) << endl; // informing the customer how much credit is in the machine, also useful for debugging

	return true;
}

bool NoCredit::makeSelection(int option)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: Insert cash into the machine before making a selection." << endl;
	return false;
}

bool NoCredit::moneyRejected(void)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: No cash in the machine to reject." << endl;
	return false;
}

bool NoCredit::addPoptart(int number)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: Machine can't have add a new poptart until the machine runs out of poptarts." << endl;
	return false;
}

bool NoCredit::dispense(void)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: No selection made, Please select a poptart to dispense." << endl;
	return false;
}


bool HasCredit::insertMoney(int money)
{
	this->CurrentContext->setStateParam(Credit, CurrentContext->getStateParam(Credit) + money); // setting Credit to how much credit there was in the machine plus the credit that was added to the machine
	
	cout << "Balance: " << this->CurrentContext->getStateParam(Credit) << endl; // informing the customer how much credit is in the machine, also useful for debugging

	return true;
}

bool HasCredit::makeSelection(int option)
{
	Product* pSelection = nullptr; // initialising a pointer for use in the switch statement, doing this rteduces the code needed for the program and allows the program to be edited more easily

		// this switch statement sets the pointer pSelection to a selected class so the machine can get the value of the poptart and its description
		switch (option) {
			// poptarts below
		case 1:
			pSelection = new PlainPoptart();
			break;
		case 2:
			pSelection = new SpicyPoptart();
			break;
		case 4:
			pSelection = new ChocolatePoptart();
			break;
		case 8:
			pSelection = new CoconutPoptart();
			break;
		case 16:
			pSelection = new FruityPoptart();
			break;

		default:
			cout << "ERROR: Invalid selection, NOTE: Fillings not yet implemented." << endl; // informs user when an invalid selection has occured
		}

	if (pSelection != nullptr) { // checks if the selection that has been made is valid
		static_cast<Poptart_Dispenser*>(this->CurrentContext)->DispensedItem = pSelection; // setting the "global" DispensedItem to the pointer pPoptart
		if (this->CurrentContext->getStateParam(Cost_Of_Poptart) <= this->CurrentContext->getStateParam(Credit)) { // checks if the user has inserted enough cash for the transaction
			this->CurrentContext->setState(Dispense_Poptart); // sets the state of the machine to Dispense_Poptart so it can dispense the poptart
			return true;
		}
		else {
			cout << "ERROR: Not enough cash inserted into the machine, you need " <<
				pSelection->cost() - this->CurrentContext->getStateParam(Credit) <<
				" more pence." << endl; // informs the user they have not got enough cash in the machine, will also inform them on how much more cash is needed for desired transaction
		}
	}

	return false;
}

bool HasCredit::moneyRejected(void)
{

	cout << "Returning " << this->CurrentContext->getStateParam(Credit) << " pence..." << endl; // informing customer how much change is being given out to them
	this->CurrentContext->setStateParam(Credit, 0); // setting credit value to zero since all credit has been returned to customer
	this->CurrentContext->setState(No_Credit); // setting machine state to No_Credit because the machine has returned all credit to customer

	return true;
}

bool HasCredit::addPoptart(int number)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: Machine can't have add a new poptart added to it while the machine is serving a customer." << endl;
	return false;
}

bool HasCredit::dispense(void)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: Can't dispense poptarts without making a selection." << endl;
	return false;
}


bool DispensePoptart::insertMoney(int money)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: can't insert money when machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::makeSelection(int option)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: can't select a poptart while the machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::moneyRejected(void)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: Can't return cash while the machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::addPoptart(int number)
{
	// return error because the machine shouldn't be used in this way (can't be done in state diagram)
	cout << "ERROR: Can't add a poptart to the machine when the machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::dispense(void)
{

	Poptart_Dispenser* poptartDispenser = static_cast<Poptart_Dispenser*>(this->CurrentContext); // getting the current machine class


	cout << "Dispensing " << poptartDispenser->DispensedItem->description() << "..." << endl; // informing that a poptart is being dispensed
	this->CurrentContext->setStateParam(No_Of_Poptarts, this->CurrentContext->getStateParam(No_Of_Poptarts) - 1); // removing one poptart from the dispenser when it has been dispensed
	poptartDispenser->itemDispensed = true; // setting the machine value of if the item being dispensed to true for the getproduct function

	cout << "Removing " << this->CurrentContext->getStateParam(Cost_Of_Poptart) << " from your balance of "  << this->CurrentContext->getStateParam(Credit) << endl; // Informing user how much cash is being removed
	this->CurrentContext->setStateParam(Credit, this->CurrentContext->getStateParam(Credit) - this->CurrentContext->getStateParam(Cost_Of_Poptart)); // setting credit in machine to "current credit in machine" - "cost of poptart" so the machine knows the correct amount of credit it has

	if (this->CurrentContext->getStateParam(No_Of_Poptarts) == 0) {
		this->CurrentContext->setState(Out_Of_Poptart); // if the machine has no credit in it and has no poptarts in it after a transaction then the state is set to Out_Of_Poptart
		cout << "NOTE: The machine is now out of poptarts." << endl; // informing user that the machine is out of paptarts
	}
	else if (this->CurrentContext->getStateParam(Credit) == 0) {
		this->CurrentContext->setState(No_Credit); // if the machine has no credit in it and has poptarts in it after a transaction then the state is set to No_Credit
		cout << "Next customer please." << endl; // asking for next customer because a polite machine is a profitable machine
	}
	else if (this->CurrentContext->getStateParam(Credit) > 0) {
		this->CurrentContext->setState(Has_Credit); // if the machine has credit in it and has poptarts in it after a transaction then the state is set to Has_Credit
		cout << "Please make your next selection." << endl; // informing the user that the machine is ready for their next selection
	}
	else {
		cout << "ERROR: end of if's in DispensePoptart::dispense" << endl;	// mainly used for debugging but this will inform the user that an error has occured
																			// Will inform at what point of the program the error occured in
																			// (likely to only go off if credit has gone below 0)
		return false;
	}
	return true;
}

Poptart_Dispenser::Poptart_Dispenser(int inventory_count)
{
	this->availableStates.push_back(new OutOfPoptart(this));	// storing class OutOfPoptart so the state of the program can run what is defined in that class when state is set to Out_Of_Poptart
	this->availableStates.push_back(new NoCredit(this));		// storing class NoCredit so the state of the program can run what is defined in that class when state is set to No_Credit
	this->availableStates.push_back(new HasCredit(this));		// storing class HasCredit so the state of the program can run what is defined in that class when state is set to Has_Credit
	this->availableStates.push_back(new DispensePoptart(this)); // storing class DispensePoptart so the state of the program can run what is defined in that class when state is set to Dispense_Poptart
	this->stateParameters.push_back(0); // neumerical storage for the enum stateParameter No_Of_Poptarts
	this->stateParameters.push_back(0); // neumerical storage for the enum stateParameter Credit

	this->setState(Out_Of_Poptart); // sets the default state of the program to Out_Of_Poptart when the program is run
	if (inventory_count) { // if the Poptart_Dispenser has 1 or more poptarts in its overflow variable on creation it will run the add poptarts function
		this->addPoptart(inventory_count);
	}
}

// End of dispenser codes
///////////////////////////////