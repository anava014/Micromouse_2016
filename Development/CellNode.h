#ifndef CELLNODE_H
#define CELLNODE_H

#include <iostream>
#include <string>
#include <vector>
#include "Cell.h"
using namespace std;

class CellNode{
private:

public:
	Cell data;
	CellNode *head;
	//CellLink *tail;
	CellNode *next;

	CellNode();

	CellNode(Cell _data);

	void pushCell(Cell _data);
	void print();
	void setNext(CellNode *n);
	void setData(Cell _Data);

};

#endif
