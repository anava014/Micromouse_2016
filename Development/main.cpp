#include <iostream>
#include "Maze.h"
#include "Cell.h"
#include "Wall.h"

using namespace std;

int main(){
	Cell testCell = Cell(true, true, true, true);

	testCell.printCell();
	
	return 0;
}
