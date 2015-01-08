/*
  Name: list.cpp--implementing the member functions
  Copyright: 
  Author: Aleksandr Kibis
  Date: 11/14/2013
  Description: 
*/

#include <cstdlib>
#include <cctype>
#include <iostream>
#include "list.h"  // header file

// default constructor
List::List(): size(0)
{
	
}

// destructor
List::~List()
{
	if (items != NULL){
		delete [] items;
        items = NULL;
        size = 0;
    }
}

// copy constructor
List::List(const List & copyList) : size(copyList.size)
{	
	// check if 0
	if (copyList.size == 0){
		items = NULL;
	}
	// otherwise create new list of same size 
	else {
		items = new ListItemType(copyList.size);
		// initialize every list[i] to copyList[i]
		for (int i=0; i < copyList.size; i++){
			*(items + i) = copyList.items[i];
		}
	}
}

// Overload assignment operator
void List::operator =(const List& rhs)
{
  if (size > 0)
      delete [] items; 
      size = rhs.size;
  (*this).items = new int [size];
  for (int i=0; i < size; i++)
          *(items + i) = rhs.items[i];
}

// Empty list
bool List::isEmpty() const
{
   return size == 0;
}  // end isEmpty

// Get length of list
int List::getLength() const
{
   return size;
}  // end getLength

// Insert new item into list
void List::insert(const ListItemType& newItem)
   throw(ListIndexOutOfRangeException, ListException)
{
	 if(size == 0){
        items = new ListItemType[1];
        items[0] = newItem;
    }else{
        int *tmpPtr = new ListItemType[size];
        if(tmpPtr == NULL){
        cerr << "Mem error 0x1 \n";
        return;
        }
        for(int i = 0; i<size; i++){
            tmpPtr[i] = items[i];
        }
        delete [] items;
        items = new ListItemType[size+1];
        if (items == NULL ){
          cerr << "Mem error 0x2 \n";
          return;
          }
        for (int i = 0; i < size; i++){
            items[i] = tmpPtr[i];
        }
        items[size] = newItem;
        delete [] tmpPtr;
    }
        size++;


}  // end insert



// Print out list contents
void List::print(){
	for(int i=0; i< getLength(); i++){
		cout <<"The item at position " << i + 1 << " is: " << *(items + i) << endl;
	}
}


// Remove specified number from the list
void List::remove(int index) 
     throw(ListIndexOutOfRangeException)
{

   bool success;
   ListIndexOutOfRangeException outOfRange;
   
   success = (index >= 1) && (index <= size);
   
   if (!success) throw outOfRange;
   
   if (success)
   {  // delete item by shifting all items at positions >
      // index toward the beginning of the list
      // (no shift if index == size)
      for (int fromPosition = index + 1;
	   fromPosition <= size;
	   ++fromPosition)
         *(items + translate(fromPosition - 1)) = *(items + translate(fromPosition));
      --size;  // decrease the size of the list by one
   }  // end if

}  // end remove

int List::translate(int index) const
{
    return index-1;
}