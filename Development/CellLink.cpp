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
