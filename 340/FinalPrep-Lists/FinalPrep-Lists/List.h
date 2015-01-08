/**
@File: List.h
@Author: Aleksandr Kibis
@Date: 12/18/2013
*/

#include <iostream>

typedef int ListItemType;
class List{
public:
	List();
	~List();
	void insert(ListItemType & item);
private:
	struct Node{
		ListItemType item;
		Node *next;
	};
	int size;
	Node* head;

	Node* find(int index) const;
};