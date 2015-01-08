
/*
  Name: linkedList.cpp
  Copyright: 
  Author: Aleksandr Kibis
  Date: 03/10/11 22:49
  Modified: 11/19/2013
  Description: 
*/
#include "linkedList.h"    // header file

using namespace std;

List::List():size(0),head(NULL) //initializer or initialization segment
{
}

List::List(const List& aList)
  : size(aList.size)
{
  if (aList.head == NULL){
      head = NULL;  // original list is empty
size = 0;
}
  else
  {  // copy first node
      head = new ListNode;
      head->item = aList.head->item;

      // copy rest of list
      ListNode *newPtr = head;  // new list pointer
      // newPtr points to last node in new list
      // origPtr points to nodes in original list
      for (ListNode *origPtr = aList.head->next;
  origPtr != NULL;
  origPtr = origPtr->next)
      {  newPtr->next = new ListNode;
        newPtr = newPtr->next;
newPtr->item = origPtr->item;
      }  // end for

      newPtr->next = NULL;
  }  // end if
}  // end copy constructor

List::~List()
{
 // while (!isEmpty())
 //   remove(1);
  /*ListNode *curr=head;
  while (curr!=NULL){
  head = curr->next;
  delete curr; 
  curr = head; */
  }  // end destructor

bool List::isEmpty() const
{
  return size == 0;
}  // end isEmpty

int List::getLength() const
{
  return size;
}  // end getLength

List::ListNode *List::find(ListItemType& dataItem) const
{

   // count from the beginning of the list.
  {  ListNode *cur = head;
      while (cur != NULL)
	  {
         if (cur->item == dataItem){
			 return cur;
		 }
		 cur = cur->next;
	  }
	   cout << "Item not found";
  }  // end if
  return NULL;
}  // end find

bool List::retrieve(const ListItemType& dataItem) 
{
	// case 1: empty list
	if (head == NULL)
	{
		cout << "List is empty, no items can be retrieved." << endl;
	}
	// case 2: non-empty list traversal
	else
	{
		ListNode *cur = head;
		while (cur != NULL)
		{
			// check item match
			if (cur->item == dataItem)
			{
				return true;
			}
				cur = cur->next;		
		}
		
	}
	return false;
}  // end retrieve

void List::insert(const ListItemType& newItem)
  throw(ListException)
{
	// add new node to the beginning of the list
	ListNode *newPtr = new ListNode;
	newPtr->item = newItem;
	// empty list
	if (head == NULL){
		head = newPtr;
		head->item = newItem;
		size++;
		return;
	} 
	else
	{
		ListNode *prev = NULL;
		ListNode *cur = head;

		// search list
		while (cur != NULL)
		{
			if (cur->item >= newPtr->item)
			{
				break;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
		// one item in list
		if (cur == head)
		{
			newPtr->next = head;
			head = newPtr;
		}
		else
		{
			// insert between nodes
			newPtr->next = cur;
			prev->next = newPtr;
		}
	}

	size++;
}

void List::remove(const ListItemType& newItem) 
{
	
	// empty list
	if (head == 0)
	{
		cout << "Nothing to remove\n";
	}

	else
	{
		ListNode *prev = NULL;
		ListNode *cur = head;

		// search list for node
		while(cur != NULL)
		{
			if(cur->item == newItem)
			{
				break;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}

		// Item not found
		if(cur == NULL)
		{
			cout << "Item: " << newItem << " not found." << endl;
		}
		else
		{
			// Delete from head
			if(head == cur)
			{
				head = head->next;
			}
			// Delete from between two nodes
			else
			{
				prev->next = cur->next;
			}
			delete cur;
			size--;
		}
		
	}
}

void List::operator=(const List& rhs){
    
    size = rhs.size;
    if (this->head !=NULL) {
        head = NULL;
        head = new ListNode;
        head->item = rhs.head->item;
        
        ListNode *newPtr = head; //points to last node in new list
        
        for (ListNode *strtPtr = rhs.head->next; strtPtr != NULL; strtPtr = strtPtr->next)
        {
            newPtr->next = new ListNode;
            newPtr = newPtr->next;
            newPtr->item = strtPtr->item;
        }
        newPtr->next = NULL; //cleanup
    }
}

ostream& operator << (ostream& os, const List& rhs)
{
    List::ListNode *cur = rhs.head;
    
    for (int i=0; i <rhs.getLength(); i++){
        os << cur->item << " ";
        cur = cur->next;
    }
    cout << endl;
    return os;
}

void List::show()
{
    ListNode *cur;
    cur = head;
    
    while (cur != NULL) {
        cout << cur->item << " ";
        cur = cur->next;
    }
    cout << endl;
}
