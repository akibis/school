#include <string>
#include <iostream>
#include "exception.h"
#include "Account.cpp"

using namespace std;

int main()
{	
	double initialBalance = 0;
	cout << "Please enter an initial account balance:";
	cin >> initialBalance;
	Account account1(initialBalance);

	cout << account1.getBalance << endl;

	return 0;
}

