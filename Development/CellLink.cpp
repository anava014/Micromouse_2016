#include "CellLink.h"

CellLink :: CellLink(){
	//data = Cell();
	head = NULL;
	next = NULL;
}

CellLink :: CellLink(CellNode _node){
	node = _node;
	head = this;
	next = NULL;
}

void CellLink :: print(){
	// CellLink *current;
	// cout << "== In Traverse == " << endl;
	// for(current = head; current != NULL; current = next) {
	// 	cout <<	" distance: " << current->data.returnIntDistance() << " -> ";
	// }
	// cout << "NULL" << endl;
}