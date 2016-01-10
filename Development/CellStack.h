#ifndef CELLSTACK_H
#define CELLSTACK_H

#include "Cell.h"

class CellStack{
private:

	Cell stack[512];
	int top;

public:
	CellStack();

	void push(Cell c);
	Cell pop();
	bool isEmpty();
	Cell peek();

	void printStack();
};


#endif
