#include <iostream>
#include "Maze.h"
#include "Cell.h"
#include "Wall.h"

using namespace std;

int main(){
	//Menu
	Mouse *mighty = new Mouse();
	Maze mm(mighty);
	//mm.printMaze();
	mm.start();

	
	return 0;
}
