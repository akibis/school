/**
@File: main.cpp
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

#include "swap.h"
#include "array.h"

using namespace std;

int main(){

	cout << "************ Question #1 ************\n\n"; // Start question 1

	int x = 1;
	int y = 2;

	cout << "Before swap." << endl;
	cout << "X: " << x << endl;
	cout << "Y: " << y << endl;

	swap(x, y);

	cout << "\nAfter swap." << endl;
	cout << "X: " << x << endl;
	cout << "Y: " << y << endl;

	string a = "starve";
	string b = "now";

	cout << "\nBefore swap." << endl;
	cout << "A: " << a << endl;
	cout << "B: " << b << endl;

	swap(a, b);

	cout << "\nAfter swap." << endl;
	cout << "A: " << a << endl;
	cout << "B: " << b << endl;

	cout << "\n\n************ Question #2 ************\n\n"; // Start question 2

	Array<int> intArray(5);
	intArray[3] = 456;

	Array<string> stringArray(10);
	stringArray[6] = "ghostride";

	cout << "Array of ints[3]\n\t" << intArray[3] << endl;
	cout << "Array of strings[6]\n\t" <<stringArray[6] << endl;



	return 0;
}