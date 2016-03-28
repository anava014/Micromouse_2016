#ifndef CELLLINK_H
#define CELLLINK_H

#include <iostream>
#include <string>
#include <vector>
#include "CellLink.h"
#include "CellNode.h"
using namespace std;

class CellLink{
private:

public:
	CellNode node;
	CellLink *head;
	//CellLink *tail;
	CellLink *next;

	CellLink();

	CellLink(CellNode _node);

	void pushCell(CellNode _node);
	void print();
	void setNext(CellLink *n);
	void setData(CellNode _node);

};

#endif
