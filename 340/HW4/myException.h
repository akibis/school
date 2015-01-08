/**
  @file: myException.h 
  Description: 
  @Author: 
  @Date: 
*/

#include <stdexcept>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

class myException_ID_Not_Found: public exception 
{	
	public:
		virtual const char* what() const throw() 
		{
			return "Caught an ID_Not_Found exception! Please enter a valid ID.";
		}
};

int getProductID(int ids[], string names[], int numProducts, string target) throw(myException_ID_Not_Found);