#include "CellStack.h"

CellStack :: CellStack(){
	top = -1;
}

void CellStack :: push(Cell c){
	if(top >= 512){
		cout << "MAJOR ERROR IN STACK OVERFLOW" << endl;
		while(1) {}
	}

	stack[++top] = c;
}

Cell CellStack :: pop(){
	if(top == -1){
		cout << "MAJOR ERROR IN STACK REACHING -1" << endl;
		while(1) {}
	}

	Cell temp = stack[top--];
	return temp;

}

bool CellStack :: isEmpty(){
	return (top == -1);
}

Cell CellStack :: peek(){
	if(top == -1){
		cout << "MAJOR ERROR IN STACK PEEK REACHING -1" << endl;
		while(1) {}
	}

	return stack[top];
}




