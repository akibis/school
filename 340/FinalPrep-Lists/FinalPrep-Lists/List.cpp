/**
@File: List.cpp
@Author: Aleksandr Kibis
@Date: 12/18/2013
*/

#include "List.h"

using namespace std;

	// Create an empty list
List::List(){
	size = 0;
	head = NULL;
}
	// Delete list
List::~List(){
	Node* curr = head;
	while (curr!=NULL){
		head = curr->next;
		delete curr;
		curr = head;
	}
}

	// Search for node
List::Node* List::find(int index) const{
	Node* curr = head;
	if (index ==  0)
		return curr;
	for (int i =0; curr!= NULL && i < index; i++){
		curr = curr-> next;
	}
	return curr;
}
	// Insert new node
void List::insert(int index, ListItemType & newItem){
	// case 1: first item
	Node* newNode = new Node;
	if (head == NULL){
		head->next = newNode;
		head 
	}
	// case 2: one or more items in list

}

	// Delete node


