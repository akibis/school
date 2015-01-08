/*
  Name: testList.cpp
  Copyright: 
  Author: 
  Date: 19/09/11 18:49
  Description: 
*/

#include <iostream>
#include "list.h" // ADT list operations

using namespace std;

int main()
{
   List         aList;
   ListItemType dataItem;
   bool         success;

   try {
	   cout << "Adding, 20, 5, 27, and 1 to the list...\n";
       aList.insert(20);
	   aList.insert(5);
	   aList.insert(27);
	   aList.insert(1);
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
   aList.retrieve(1, dataItem); 
   cout <<"The item at position 1 is: "<< dataItem <<endl;
   aList.retrieve(2, dataItem); 
   cout <<"The item at position 2 is: "<< dataItem <<endl;
   aList.retrieve(3, dataItem); 
   cout <<"The item at position 3 is: "<< dataItem <<endl;
   aList.retrieve(4, dataItem); 
   cout <<"The item at position 4 is: "<< dataItem <<endl;

   cout << "\n\nREMOVE 20 FROM LIST\n\n";

   aList.remove(20); 
   aList.retrieve(1, dataItem); 
   cout <<"The item at position 1 is: "<< dataItem <<endl;
   aList.retrieve(2, dataItem); 
   cout <<"The item at position 2 is: "<< dataItem <<endl;
   aList.retrieve(3, dataItem); 
   cout <<"The item at position 3 is: "<< dataItem <<endl;

    cout << "\n\nPRINT FUNCTION TEST\n\n";

	aList.print();
   
   return 0;

}