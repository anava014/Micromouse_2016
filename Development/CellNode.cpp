#include "CellNode.h"

CellNode :: CellNode(){
	//data = Cell();
	head = NULL;
	next = NULL;
}

CellNode :: CellNode(Cell _data){
	data = _data;
	head = this;
	next = NULL;
}

void CellNode :: print(){
	CellNode *current;
	cout << "== In Traverse == " << endl;
	for(current = head; current != NULL; current = next) {
		cout <<	" distance: " << current->data.returnIntDistance() << " -> ";
	}
	cout << "NULL" << endl;
}
