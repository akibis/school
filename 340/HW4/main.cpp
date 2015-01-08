/**
	@file: main.cpp
	Description: Demonstrating separate compilation and exception throwing using a simple
	array access function.
	@Author: Aleksandr Kibis
	@Date: 10/3/2013


One problem with this implementation of the getProductID() function is that it returns the 
special error code of -1 if the target name is not found.  The caller might either ignore the 
-1 or later we might actually want to have -1 as a valid product ID number. Rewrite the program 
so that it throws an appropriate exception when a product is not found instead of returning 
-1.  Please define an exception class Exception_ID_Not_Found. Then modify the getProductID() 
function to include a throw list. Finally, test handle this type of exceptions properly in the 
main() function.

Note: You are required to use separate compilation for this problem. 

**/

#include "myException.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

int main() // Sample code to test the getProductID function
{

	int productIds[]= {4, 5, 8, 10, 13};
	string products[] = { "computer", "flash drive", "mouse", "printer", "camera" };
	cout << getProductID(productIds, products, 5, "mouse") << endl;
	cout << getProductID(productIds, products, 5, "camera") << endl;
	cout << getProductID(productIds, products, 5, "laptop") << endl;
	return 0;
}