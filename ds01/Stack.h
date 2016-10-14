#pragma once
#include "StackEle.h"

class Stack{
public:
	Stack();
	~Stack();
	StackEle* bottom;
	StackEle* top;
	int size = 0;

	void push(char n);
	bool isEmpty();
	char pop();
	void print();
};