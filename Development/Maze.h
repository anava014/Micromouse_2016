#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"
#include "Mouse.h"

class Maze{
private:
	Cell maze[16][16];
	void drawMiddleLine();
	Mouse *mouse;

public:
	Maze(Mouse *mouse);
	void printMaze();
	void start();
	void analyzePosition();
};

#endif
