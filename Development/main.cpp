#include <iostream>
#include "Maze.h"

using namespace std;

int main(){
	Mouse *mighty = new Mouse();
	Maze mm(mighty);
	mm.start();
	return 0;
}
