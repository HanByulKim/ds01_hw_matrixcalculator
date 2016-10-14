#pragma once
#include "List.h"
#include <iostream>

class NodeRow {
public:
	NodeRow();
	List* n;
	NodeRow* next;
};
