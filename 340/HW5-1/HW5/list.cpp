/*
  Name: list.cpp--implementing the member functions
  Copyright: 
  Author: 
  Date: 19/09/11 18:43
  Description: 
*/


#include <iostream>
#include "list.h"  // header file

List::List(): size(0)
{

}  // end default constructor

bool List::isEmpty() const
{
   return size == 0;
}  // end isEmpty

int List::getLength() const
{
   return size;
}  // end getLength



void List::insert(const ListItemType& newItem)
   throw(ListIndexOutOfRangeException, ListException)
{
   ListException listEx("ListException: List full on insert");
   ListIndexOutOfRangeException outOfRange("ListIndexOutOfRangeException: Bad index on insert");                  
   int index = size + 1;

   if (size >= MAX_LIST)
      throw listEx;
      //ListException("ListException: List full on insert");

   if (index >= 1 && index <= size+1)
   {
       for (int pos = size; pos >= index; --pos)
         items[translate(pos+1)] = items[translate(pos)];
      // insert new item
      items[translate(index)] = newItem;
      ++size;  // increase the size of the list by one
	  bubbleSort();
   }
   else  // index out of range
      throw outOfRange;
      //ListIndexOutOfRangeException( "ListIndexOutOfRangeException: Bad index on insert");
   // end if
}  // end insert

// input an int to search for, if there is a match, index is returned.
int List::search(const ListItemType& dataItem){
	for (int i = 0; i < getLength(); i++) {
		if (items[i] == dataItem){
			return i+1;
		}
	}
	return -1;
}

// Print out list contents
void List::print(){
	for(int i=0; i< getLength(); i++){
		cout <<"The item at position " << i + 1 << " is: " << items[i] << endl;
	}
}
// sorts items array in ascending order
void List::bubbleSort(){
	bool swapped = true;
      int j = 0;
      int tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < getLength() - j; i++) {
                  if (items[i] > items[i + 1]) {
                        tmp = items[i];
                        items[i] = items[i + 1];
                        items[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}

// remove specified number from the list
void List::remove(const ListItemType& itemToRemove) 
     throw(ListIndexOutOfRangeException)
{
   int index = search(itemToRemove);
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
         items[translate(fromPosition - 1)] = items[translate(fromPosition)];
      --size;  // decrease the size of the list by one
   }  // end if

}  // end remove

// Assigns dataItem a specific list item by index
void List::retrieve(int index, ListItemType& dataItem) const
     throw(ListIndexOutOfRangeException)
{
   bool success;
   ListIndexOutOfRangeException outOfRange;
   
   success = (index >= 1) && (index <= size);
   
   if (!success) throw outOfRange;
   
   if (success)
      dataItem = items[translate(index)];
}  // end retrieve

int List::translate(int index) const
{
    return index-1;
}