#include "List.h"
#include <iostream>

List::List() {
	head = new NodeEle();
	head->next = NULL;
	tail = head;
}

List::~List(){
	/*while (head != NULL){
		for (NodeEle* itr = head->next; itr->next; itr = itr->next){
			if (itr->next == NULL)
				delete itr;
		}
	}*/
}


void List::add(double n) {
	tail->next = new NodeEle();
	tail = tail->next;
	tail->n = n;
	tail->next = NULL;
	size++;
}

void List::print(){
	NodeEle* itr = head->next;
	for (int i = 0; i < size; i++) {
		std::cout << itr->n << " ";
		itr = itr->next;
	}
}