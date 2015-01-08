/*
  Name: list.h--consisting of the interface of List
  Copyright: 
  Author: Aleksandr Kibis
  Date: 11/14/2013
  Description: 
*/

/** @file ListAexcept.h */
#ifndef _LIST_H
#define _LIST_H

#include <cstdlib>
#include <cctype>
#include "listExceptions.h"


typedef int ListItemType;

/** @class List
 * ADT list - Array-based implementation with exceptions */
class List
{
public:
	// constructor
   List();

   // destructor
   ~List();

   // copy constructor
   List::List(const List & copyList);

   /** @throw None. */
   bool isEmpty() const;

   /** @throw None. */
   int getLength() const;

   void List::operator =(const List& rhs);
   
   void print();

   void insert(const ListItemType& newItem)
      throw(ListIndexOutOfRangeException, ListException);

   /** @throw ListIndexOutOfRangeException  If index < 1 or index >
    *         getLength(). */
   void remove(int index)
      throw(ListIndexOutOfRangeException);



private:
   /** array of list items */
   ListItemType *items;


   /** number of items in list */
   int          size;

   int translate(int index) const;
}; // end List
// End of header file.

#endif