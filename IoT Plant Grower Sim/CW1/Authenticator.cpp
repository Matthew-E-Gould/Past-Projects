#include "Classes.h"

Authenticator::Authenticator()
{
	authenticated = false;

	Users.insert(pair<string, string>("User", "Pass"));

}
Authenticator::~Authenticator()
{
}

void Authenticator::authenticate() {
		cout << "Enter a Username and Password...\nUsername: ";
		cin >> uName;
		cout << "Password: ";
		cin >> uPass;

		validateUser();

		if (!authenticated) {
			cout << "WRONG USERNAME/PASS\n";
		}
		else {

			cout << "\nAuthenticated!";
			system("cls");

	}
}

void Authenticator::validateUser()
{
	map<string, string>::iterator it;
	it = Users.find(uName);
	if (it != Users.end()) {

		if (!(it->second.compare(uPass))) {
			authenticated = true;
		}
		else {
			authenticated = false;
		}
	}
	else {
		authenticated = false;
	}
}

void Authenticator::turnedOff() {

	uName.clear();
	uPass.clear();

	authenticated = false;

}