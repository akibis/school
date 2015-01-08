/*
  Name: testList.cpp
  Copyright: 
  Author: Aleksandr Kibis
  Date: 11/14/2013
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
   List			copy;


   try {
	   cout << "Adding 5, 23, 4, 67, 1 to list 1...\n";
       list1.insert(5);
	   list1.insert(23);
	   list1.insert(4);
	   list1.insert(67);
	   list1.insert(1);
	   

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

   list1.print();

   cout << "Removing item #2 from list 1...\n";
   list1.remove(1);
   list1.print();

   cout << "Copying list 1...\n";
   copy = list1;
   copy.print();

   cout << "Removing 3rd item from copy of list 1...\n";
   copy.remove(3);
   copy.print();

   
   return 0;

}