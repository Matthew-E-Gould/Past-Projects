#include <vector>
#include <iostream>
#include <string>

#pragma once

using namespace std;

class State;
class StateContext;
class Transition;
class PoptartState;
class OutOfPoptart;
class NoCredit;
class HasCredit;
class DispensePoptart;
class Product;
class Poptart;
class Poptart_Dispenser;


enum state { Out_Of_Poptart, No_Credit, Has_Credit, Dispense_Poptart};
enum stateParameter { No_Of_Poptarts, Credit, Cost_Of_Poptart };

class State {
protected:
	StateContext* CurrentContext;

public:
	State(StateContext* Context) {
		CurrentContext = Context;
	}
	virtual ~State(void){}
	virtual void transition(void){}

};

class StateContext {
protected:
	State* CurrentState = nullptr;
	int stateIndex = 0;
	vector<State*> availableStates;
	vector<int> stateParameters;

public:
	virtual ~StateContext(void);
	virtual void setState(state newState);
	virtual int getStateIndex(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);

};

StateContext::~StateContext(void) {
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i];
	this->availableStates.clear();
	this->stateParameters.clear();
}

void StateContext::setState(state newState) {
	this->CurrentState = availableStates[newState];
	this->stateIndex = newState;
	this->CurrentState->transition();
}

int StateContext::getStateIndex(void) {
	return this->stateIndex;
}

void StateContext::setStateParam(stateParameter SP, int value) {
	this->stateParameters[SP] = value;
}

int StateContext::getStateParam(stateParameter SP) {
	return this->stateParameters[SP];
}

class Transition {
public:
	virtual bool insertMoney(int) { cout << "ERROR!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "ERROR!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "ERROR!" << endl; return false; }
	virtual bool addPoptart(int) { cout << "ERROR!" << endl; return false; }
	virtual bool dispense(void) { cout << "ERROR!" << endl; return false; }
};

class PoptartState : public State, public Transition {
public:
	PoptartState(StateContext* Context) : State(Context){}
};

class OutOfPoptart : public PoptartState {
public:
	OutOfPoptart(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

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

class Product
{
protected:
	string product_description;
	int itemCost = 0;

public:
	virtual int cost(void);
	virtual string description(void);
};

class Poptart : public Product{
public:
	Poptart(void);
};

class Poptart_Dispenser : public StateContext, public Transition
{
	friend class DispensesPoptart;
	friend class HasCredit;

private:
	PoptartState* PoptartCurrentState = nullptr;
	bool itemDispensed = false;
	Product* DispensedItem = nullptr;
	bool itemRetrieved = false;

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

Poptart_Dispenser::~Poptart_Dispenser(void) {
	if (!this->itemRetrieved) {
		delete this->DispensedItem;
	}
}

bool Poptart_Dispenser::insertMoney(int money) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->insertMoney(money);
}

bool Poptart_Dispenser::makeSelection(int option) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->makeSelection(option);
}

bool Poptart_Dispenser::moneyRejected(void) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->moneyRejected();
}

bool Poptart_Dispenser::addPoptart(int number) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->addPoptart(number);
}

bool Poptart_Dispenser::dispense(void) {
	PoptartCurrentState = (PoptartState*) this->CurrentState;
	return this->PoptartCurrentState->dispense();
}

Product* Poptart_Dispenser::getProduct(void) {
	if (this->itemDispensed) {
		this->itemDispensed = false;
		this->itemRetrieved = true;
		return this->DispensedItem;
	}

	return nullptr;
}

void Poptart_Dispenser::setStateParam(stateParameter SP, int value) {
	if (SP == Cost_Of_Poptart) return; // need to work out how to save the cost of a poptart... maybe i can just use a pointer and .cost();
	this->stateParameters[SP] = value;
}

int Poptart_Dispenser::getStateParam(stateParameter SP) {
	if (SP == Cost_Of_Poptart) {
		if (DispensedItem == nullptr) return 0;
		return DispensedItem->cost(); // money is take out of credit when item is despensed i guess...
	}
	return this->stateParameters[SP];
}

//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
//////////////
// ALL MY SHIT

////////////////
// poptart types

class PlainPoptart : public Poptart {
public:
	PlainPoptart(void);
};

PlainPoptart::PlainPoptart(void) {
	itemCost = 100;
	product_description = "plain poptart.";
}

class SpicyPoptart : public Poptart {
public:
	SpicyPoptart(void);
};

SpicyPoptart::SpicyPoptart(void) {
	itemCost = 150;
	product_description = "spicy poptart.";
}


class ChocolatePoptart : public Poptart {
public:
	ChocolatePoptart(void);
};

ChocolatePoptart::ChocolatePoptart(void) {
	itemCost = 200;
	product_description = "chocolate poptart.";
}


class CoconutPoptart : public Poptart {
public:
	CoconutPoptart(void);
};

CoconutPoptart::CoconutPoptart(void) {
	itemCost = 200;
	product_description = "coconut poptart.";
}


class FruityPoptart : public Poptart {
public:
	FruityPoptart(void);
};

FruityPoptart::FruityPoptart(void) {
	itemCost = 200;
	product_description = "fruity poptart.";
}

///////////////////
// poptart fillings

//////////////////
// dispenser codes

bool OutOfPoptart::insertMoney(int money)
{
	// return error because the machine shouldn't be used in this way
	this->CurrentContext->setStateParam(Credit, money);
	cout << "ERROR: No Poptarts in inventory! Returning cash..." << endl;
	this->moneyRejected();
	return false;
}

bool OutOfPoptart::makeSelection(int option)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: No Poptarts in inventory! Ignoring request..." << endl;
	return false;
}

bool OutOfPoptart::moneyRejected(void)
{
	cout << "Returning " << this->CurrentContext->getStateParam(Credit) << " pence..." << endl;
	this->CurrentContext->setStateParam(Credit, 0); // setting credit in machine to 0
	return true;
}

bool OutOfPoptart::addPoptart(int number)
{
	this->CurrentContext->setStateParam(No_Of_Poptarts, number);
	this->CurrentContext->setState(No_Credit);
	return true;
}

bool OutOfPoptart::dispense(void)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: No Poptarts left! Can't dispense." << endl;
	return false;
}


bool NoCredit::insertMoney(int money)
{

	this->CurrentContext->setStateParam(Credit, money);
	this->CurrentContext->setState(Has_Credit);

	// if cash inserted change state //this->CurrentContext->setState(Has_Credit);
	// add cash to total cash // this->CurrentContext->setStateParam(Credit, money);
	// if no cash inserted return error
	return true;
}

bool NoCredit::makeSelection(int option)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: Insert cash into the machine before making a selection." << endl;
	return false;
}

bool NoCredit::moneyRejected(void)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: No cash in the machine to reject." << endl;
	return false;
}

bool NoCredit::addPoptart(int number)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: Machine can't have add a new poptart until the machine runs out of poptarts." << endl;
	return false;
}

bool NoCredit::dispense(void)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: No selection made, Please select a poptart to dispense." << endl;
	return false;
}


bool HasCredit::insertMoney(int money)
{
	this->CurrentContext->setStateParam(Credit, Credit + money);

	// edit credit total enum // this->CurrentContext->setStateParam(Credit, money);
	return true;
}

bool HasCredit::makeSelection(int option)
{

	int cred = this->CurrentContext->getStateParam(Credit);
	Product* pPoptart = nullptr;

	switch (option) {
	case 1:
		pPoptart = new PlainPoptart();
		break;
	case 2:
		pPoptart = new SpicyPoptart();
		break;
	case 4:
		pPoptart = new ChocolatePoptart();
		break;
	case 8:
		pPoptart = new CoconutPoptart();
		break;
	case 16:
		pPoptart = new FruityPoptart();
		break;
		// do fillings below
	default:
		cout << "ERROR: Invalid selection, NOTE: Fillings not yet implemented." << endl;
	}

	// DEBUG
	cout << "Cost: " << pPoptart->cost() << endl;
	cout << "Cred: " << this->CurrentContext->getStateParam(Credit) << endl;
	// /DEBUG

	if (pPoptart != nullptr) {
		if (pPoptart->cost() <= this->CurrentContext->getStateParam(Credit)) {
			static_cast<Poptart_Dispenser*>(this->CurrentContext)->DispensedItem = pPoptart;
			this->CurrentContext->setStateParam(Credit, cred - pPoptart->cost());
			this->CurrentContext->setState(Dispense_Poptart);
			return true;
		}
		else {
			cout << "ERROR: Not enough cash inserted into the machine, you need " <<
				pPoptart->cost() - this->CurrentContext->getStateParam(Credit) <<
				" more pence." << endl;
			return false;
		}
	}

	// set machine state to dispense poptart //this->CurrentContext->setState(Dispense_Poptart);
}

bool HasCredit::moneyRejected(void)
{

	cout << "Returning " << this->CurrentContext->getStateParam(Credit) << " pence..." << endl;
	this->CurrentContext->setStateParam(Credit, 0);
	this->CurrentContext->setState(No_Credit);

	// return that the machine is returning cash
	// set state to "NoCredit" //this->CurrentContext->setState(No_Credit);
	return true;
}

bool HasCredit::addPoptart(int number)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: Machine can't have add a new poptart added to it while the machine is serving a customer." << endl;
	return false;
}

bool HasCredit::dispense(void)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: Can't dispense poptarts without making a selection." << endl;
	return false;
}


bool DispensePoptart::insertMoney(int money)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: can't insert money when machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::makeSelection(int option)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: can't select a poptart while the machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::moneyRejected(void)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: Can't return cash while the machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::addPoptart(int number)
{
	// return error because the machine shouldn't be used in this way
	cout << "ERROR: Can't add a poptart to the machine when the machine is dispensing poptart." << endl;
	return false;
}

bool DispensePoptart::dispense(void)
{

	int poptartCount = this->CurrentContext->getStateParam(No_Of_Poptarts);

	cout << "Dispensing poptart..." << endl;

	this->CurrentContext->setStateParam(No_Of_Poptarts, poptartCount - 1);

	if (this->CurrentContext->getStateParam(No_Of_Poptarts) == 0) {
		this->CurrentContext->setState(Out_Of_Poptart);
	}
	else if (this->CurrentContext->getStateParam(Credit) == 0) {
		this->CurrentContext->setState(No_Credit);
	}
	else if (this->CurrentContext->getStateParam(Credit) > 0) {
		this->CurrentContext->setState(Has_Credit);
	}
	else {
		cout << "ERROR: end of if's in DispensePoptart::dispense" << endl;
		return false;
	}

	// DEBUG
	cout << "Credit: " << this->CurrentContext->getStateParam(Credit) << endl;
	cout << "Poptarts: " << this->CurrentContext->getStateParam(No_Of_Poptarts) << endl;
	// /DEBUG

	// return poptarts being dispensed
	// if no poptarts left in machine set state to "OutOfPoptart" //this->CurrentContext->setState(Out_Of_Poptart);
	// else if credit == 0 set state to NoCredit
	// else if credit > 0 set state to HasCredit
	// else return error
	return true;
}


int Product::cost(void)
{
	return itemCost;
}

string Product::description(void)
{
	return product_description;
}


Poptart::Poptart(void) {
	//cout << "ERROR!" << endl;
}


Poptart_Dispenser::Poptart_Dispenser(int inventory_count)
{
	this->availableStates.push_back(new OutOfPoptart(this));
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensePoptart(this));
	this->stateParameters.push_back(0); // enum stateParameter { No_Of_Poptarts, ..., ...};
	this->stateParameters.push_back(0); // enum stateParameter { ..., Credit, ...};

	this->setState(Out_Of_Poptart);
	if (inventory_count) {
		this->addPoptart(inventory_count);
	}
}