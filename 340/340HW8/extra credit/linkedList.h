/*
  Name: linkedList.h
  Copyright: 
  Author: Aleksandr Kibis
  Date: 03/10/11 22:49
  Modified: 11/19/2013
  Description: 
*/
#include "listExceptions.h"

typedef int ListItemType;
//typedef desired-type-of-list-item ListItemType;

/** @class List
* ADT list - Pointer-based implementation. */
class List
{
public:
// Constructors and destructor:

  /** Default constructor. */
  List();

  /** Copy constructor.
    * @param aList The list to copy. */
  List(const List& aList);

  //overload the assignment operator
 List operator=(const List&  rhs);
  /** Destructor. */
  ~List();

// List operations:
  bool isEmpty() const;
  int getLength() const;
  void insert(int index, const ListItemType& newItem)
      throw(ListIndexOutOfRangeException, ListException);
  void remove(int index)
      throw(ListIndexOutOfRangeException);
  void retrieve(int index, ListItemType& dataItem) const
      throw(ListIndexOutOfRangeException);
      
  //overload the << operator: idea is similar to the find()
  friend ostream & operator << (ostream & out, const List & aList);

private:
  /** A node on the list. */
  struct ListNode
  {
	  /** Pointer to previous node */
	  ListNode *prev;
      /** A data item on the list. */
      ListItemType item;
      /** Pointer to next node. */
      ListNode *next;
  }; // end ListNode

  /** Number of items in list. */
  int      size;
  /** Pointer to beginning of linked list of items. */
  ListNode *head;
  /** Pointer to end of linked list of items. */
  ListNode *tail;

  /** Locates a specified node in a linked list.
    * @pre index is the number of the desired node.
    * @post None.
    * @param index The index of the node to locate.
    * @return A pointer to the index-th node. If index < 1
    *        or index > the number of nodes in the list,
    *        returns NULL. */
  ListNode *find(int index) const;
}; // end List
// End of header file.
