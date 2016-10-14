#pragma once
#include "NodeEle.h"
#include <iostream>
class List {
public:
	List();
	~List();
	NodeEle* head;
	NodeEle* tail;
	int size = 0;

	void add(double n);
	void print();

	inline void List::operator=(const List& b) {
		//List Mat;

		size = b.size;
		NodeEle* A;
		NodeEle* B;
		A = this->head;
		B = b.head;
		for (int i = 0; i < size - 1; i++) {
			std::cout << "okList" << std::endl;
			A = A->next;
			B = B->next;
			A->n = B->n;
			//Mat.add(B->n);
			//Mat.print();
		}
	}
	inline List List::operator+(const List& b) {
		List Mat;

		if (size == b.size) {
			NodeEle* A;
			NodeEle* B;
			A = head;
			B = b.head;
			for (int i = 0; i < size-1; i++) {
				std::cout << "okList" << std::endl;
				A = A->next;
				B = B->next;
				Mat.add(A->n + B->n);
				Mat.print();
			}
		}
		else
			std::cout << "column size error! mismatch!" << std::endl;

		return Mat;
	}
	inline List List::operator-(const List& b) {
		List Mat;

		if (size == b.size) {
			NodeEle* A;
			NodeEle* B;
			A = head;
			B = b.head;
			for (int i = 0; i < size-1; i++) {
				std::cout << "okList";
				A = A->next;
				B = B->next;
				Mat.add(A->n - B->n);
				Mat.print();
				std::cout << std::endl;
			}
		}
		else {
			std::cout << "column size error! mismatch!" << std::endl;
		}

		return Mat;
	}
	inline List List::operator*(const List& b) {
		List Mat;

		if (size == b.size) {
			NodeEle* A;
			NodeEle* B;
			A = head;
			B = b.head;
			for (int i = 0; i < size-1; i++) {
				std::cout << "okList" << std::endl;
				A = A->next;
				B = B->next;
				Mat.add(A->n * B->n);
				Mat.print();
			}
		}
		else {
			std::cout << "column size error! mismatch!" << std::endl;
		}

		return Mat;
	}
};