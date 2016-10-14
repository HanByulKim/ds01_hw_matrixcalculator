#pragma once
#include "NodeRow.h"
class ListRow {
public:
	ListRow();
	~ListRow();
	NodeRow* head;
	NodeRow* tail;
	int size = 0;

	void add(List* n);
	void print();

	inline void ListRow::operator=(const ListRow& b) {
		
		size = b.size;
		NodeRow* A;
		NodeRow* B;
		A = this->head;
		B = b.head;
		if (A->next != NULL && B->next != NULL) {
			for (int i = 0; i < size; i++) {
				std::cout << "okrow" << std::endl;
				A = A->next;
				B = B->next;

				A->n = B->n;
			}
		}
	}
	inline ListRow ListRow::operator+(const ListRow& b) {
		ListRow Mat;

		if (size == b.size) {
			NodeRow* A;
			NodeRow* B;
			A = head;
			B = b.head;
			for (int i = 0; i < size; i++) {
				std::cout << "okrow" << std::endl;
				A = A->next;
				B = B->next;
				List temp = *(A->n) + *(B->n);
				List* Row = new List();
				NodeEle* go = temp.head->next;
				std::cout << std::endl;
				for (int j = 0; j < temp.size; j++) {
					Row->add(go->n);
					go = go->next;
				}
				std::cout << "midterm result in +operator" << std::endl;
				Row->print();
				Mat.add(Row);
			}
		}
		else
			std::cout << "row size error! mismatch!" << std::endl;
		Mat.print();
		return Mat;
	}
	inline ListRow ListRow::operator-(const ListRow& b) {
		ListRow Mat;

		if (size == b.size) {
			NodeRow* A;
			NodeRow* B;
			A = head;
			B = b.head;
			for (int i = 0; i < size; i++) {
				std::cout << "ok" << std::endl;
				A = A->next;
				B = B->next;
				List temp = *(A->n) - *(B->n);
				List* Row = new List();
				NodeEle* go = temp.head->next;
				std::cout << std::endl;
				for (int i = 0; i < temp.size; i++) {
					Row->add(go->n);
					go = go->next;
				}
				Row->print();
				std::cout << "Rowprint" << std::endl;
				Mat.add(Row);
			}
		}
		else
			std::cout << "row size error! mismatch!" << std::endl;
		
		return Mat;
	}
	inline ListRow ListRow::operator*(const ListRow& b) {
		ListRow Mat;

		if (size == b.size) {
			NodeRow* A;
			NodeRow* B;
			A = head;
			B = b.head;
			for (int i = 0; i < size; i++) {
				std::cout << "ok" << std::endl;
				A = A->next;
				B = B->next;
				List temp = (*(A->n)) * (*(B->n));
				List* Row = new List();
				NodeEle* go = temp.head->next;
				std::cout << std::endl;
				for (int i = 0; i < temp.size; i++) {
					Row->add(go->n);
					go = go->next;
				}
				Row->print();
				std::cout << "Rowprint" << std::endl;
				Mat.add(Row);
			}
		}
		else
			std::cout << "row size error! mismatch!" << std::endl;

		return Mat;
	}
};
