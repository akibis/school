/*
  Name: testList.cpp
  Copyright: 
  Author: 
  Date: 19/09/11 18:49
  Description: 
*/
#include <cstdlib>
#include <cctype>
#include <iostream>
#include "list.h" // ADT list operations

using namespace std;

int main()
{

   List         list1;
   List			list2;

   try {
	   cout << "Adding 3 and 4 to list 1...\n";
       list1.insert(3);
	   list1.insert(4);

	   cout << "Adding 9 and 1 to list 2...\n";
       list2.insert(9);
	   list2.insert(3);
   }
   catch( ListException & e1)
   {
          cerr << e1.what();
   }
   catch ( ListIndexOutOfRangeException & e2)
   {
       //handling the exception here
   } 
   catch (...)
   {
         //handling all the other exceptions here
   }

    cout << "\n\nPRINT FUNCTION TEST\n\n";

	list1.print();
	cout << endl;
	list2.print();

	cout << "\nLIST1 + LIST2\n";
	List total;
	total = list1 + list2;
	total.print();

	cout << "\nLIST1 - LIST2\n";
	total = list1 - list2;
	total.print();

	cout << "\nLIST1 * 5\n";
	total = list1 * 5;
	total.print();

	cout << "\nLIST2 / 3\n";
	total = list2 / 3;
	total.print();

	cout << "\nLIST1++\n";
	total = list1++;
	total.print();

	cout << "\n++LIST1\n";
	total = ++list1;
	total.print();
   
   return 0;

}