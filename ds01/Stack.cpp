#include "Stack.h"
#include <iostream>

Stack::Stack(){
	bottom = new StackEle();
	bottom->next = NULL;
}

Stack::~Stack(){
	while (top != NULL){
		pop();
		size--;
	}
	delete bottom;
}

void Stack::push(char n){
	StackEle* nNode = new StackEle();
	nNode->n = n;
	nNode->next = top;
	top = nNode;

	size++;
}

char Stack::pop(){
	if (isEmpty())
		return 0;

	char temp = top->n;
	StackEle* del = top;
	top = top->next;
	delete del;
	size--;

	return temp;
}

bool Stack::isEmpty(){
	if (size == 0)
		return true;
	return false;
}

void Stack::print(){
	std::cout << "stack : ";
	for (StackEle* itr = top; itr; itr = itr->next)
		std::cout << itr->n << " " ;
	std::cout << std::endl;
}