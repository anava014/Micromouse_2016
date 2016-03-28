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

// CellNode :: CellNode(Cell _data, CellNode *n){
// 	data = _data;
// 	head = this;
// 	next = n;
// }

// void CellNode :: pushCell(Cell _Data){
// 	CellNode *temp = new CellNode();
// 	//temp->setData(_Data);
// 	temp->setNext(head);
// 	head = temp;
// }

void CellNode :: print(){
	CellNode *current;
	cout << "== In Traverse == " << endl;
	for(current = head; current != NULL; current = next) {
		cout <<	" distance: " << current->data.returnIntDistance() << " -> ";
	}
	cout << "NULL" << endl;
}

// void CellNode :: setNext(CellNode *n){
// 	head->next = n;
// }

// void CellNode :: setData(Cell _Data){
// 	head->data = _Data;
// }