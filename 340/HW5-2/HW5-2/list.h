/*
  Name: list.h--consisting of the interface of List
  Copyright: 
  Author: 
  Date: 19/09/11 18:42
  Description: 
*/

/** @file ListAexcept.h */
#ifndef _LIST_H
#define _LIST_H

#include <cstdlib>
#include <cctype>
#include "listExceptions.h"

const int MAX_LIST = 20;
typedef int ListItemType;

/** @class List
 * ADT list - Array-based implementation with exceptions */
class List
{
public:
   List();
   // destructor is supplied by compiler

   /** @throw None. */
   bool isEmpty() const;

   /** @throw None. */
   int getLength() const;

   /** @throw ListIndexOutOfRangeException  If index < 1 or index >
    *         getLength() + 1.
    *  @throw ListException  If newItem cannot be placed in the list
    *         because the array is full. */
   
// **************** OPERATOR OVERLOADING *****************

   friend List operator +(const List& num1, const List& num2);

   friend List operator -(const List& num1, const List& num2);

   friend List operator *(const List& num1, const int num2);

   friend List operator /(const List& num1, const int num2);

   friend List operator ++(const List& num1);


// ********************** END OVERLOADING ****************
   
   void print();
   
   int search(const ListItemType& dataItem);

   void bubbleSort();

   void insert(const ListItemType& newItem)
      throw(ListIndexOutOfRangeException, ListException);

   /** @throw ListIndexOutOfRangeException  If index < 1 or index >
    *         getLength(). */
   void remove(const ListItemType& dataItem)
      throw(ListIndexOutOfRangeException);

   /** @throw ListIndexOutOfRangeException  If index < 1 or index >
    *         getLength(). */
   void retrieve(int index, ListItemType& dataItem) const
        throw(ListIndexOutOfRangeException);

private:
   /** array of list items */
   ListItemType items[MAX_LIST];


   /** number of items in list */
   int          size;

   int translate(int index) const;
}; // end List
// End of header file.

#endif