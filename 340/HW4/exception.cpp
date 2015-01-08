/**
	@file: exception.cpp
	Description: Define function that throws exception
	@Author: Aleksandr Kibis
	@Date: 10/3/2013
**/

#include "myException.h"

int getProductID(int ids[], string names[], int numProducts, string target) throw(myException_ID_Not_Found)
{
	try{
	myException_ID_Not_Found e_notFound;

	for (int i=0; i < numProducts; i++)
	{
		if (names[i] == target)
			return ids[i]; 
	}
	throw e_notFound;
	}
	catch (exception & e){
		cerr << e.what() << "\n\n";
	return -1;  // not found 
	}
}



