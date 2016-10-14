#include "ListRow.h"
#include <iostream>

ListRow::ListRow() {
	head = new NodeRow();
	head->next = NULL;
	tail = head;
}

ListRow::~ListRow(){
	/*if (head != NULL && head->next != NULL){
		for (NodeRow* itr = head->next; itr; itr = itr->next){
			if (itr->next == NULL)
				delete itr;
		}
	}*/
}

void ListRow::add(List* n) {
	tail->next = new NodeRow();
	tail = tail->next;
	tail->n = n;
	tail->next = NULL;
	size++;
}

void ListRow::print(){
	std::cout << std::endl;
	std::cout << "--print matrix--" << std::endl;
	NodeRow* itr = head->next;
	for (int i = 0; i < size;i++) {
		itr->n->print();
		std::cout << std::endl;
		itr = itr->next;
	}
}

