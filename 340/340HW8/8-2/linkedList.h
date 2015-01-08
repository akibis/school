/*
  Name: listExceptions.h
  Desc: declare two exception classes that are specific to List
  Copyright: 
  Author: Aleksandr Kibis
  Date: 19/09/11 18:37
  Modified: November 20, 2013
  Description: 
*/

#ifndef LINKEDLIST_H_INCLUDED
#define	LINKEDLIST_H_INCLUDED

#include "listExceptions.h"
#include <iostream>
#include <string>

typedef int ListItemType;

/* @Class List
 ADT PTR based list */

class List
{
public:
    //default constructor
    List();
    
    //copy constructor; param aList for copying
    List(const List& aList);
    
    //destructor
    ~List();
    
    //functions
    
    int getLength() const;
    bool isEmpty() const;
    void show();
    
    bool retrieve (const ListItemType& dataItem) ;
    
    void insert (const ListItemType& newItem)
    throw (ListException);
    
    void remove (const ListItemType& newItem);
    
    //overload operators
    void operator = (const List& rhs);
    //friend overload operator
    friend ostream& operator << (ostream& os, const List& rhs);
    
    
private:
    //create a node for a list
    struct ListNode
    {
        //data item for dynamic list
        ListItemType item;
        //pointer to next node to create linked list
        ListNode *next;
    };
    
    //items contained in list
    int size;
    //pointer to start linked list
    ListNode *head;
    ListNode *find(ListItemType& dataItem) const;
    void simpleReverse(int sizeOf) const;    

};

#endif	/* LINKEDLIST_H */

