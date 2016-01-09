#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"
#include "Mouse.h"
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Maze{
private:
	Cell maze[16][16];
	//Cell *liveMaze[16][16];
	void drawMiddleLine();
	void drawLineEnclosure();
	void drawMap();
	void drawVerticalLine(int start, int end, int left);
	void drawHorizontalLine(int start, int end, int up);
	void importMapFromFile();

	void setEastWestWalls(int up, int left);
	void setNorthSouthWalls(int up, int left);

	bool enclosedIn();
	bool onlyRightOpen();
	bool onlyLeftOpen();
	bool leftAndRightOpen();
	bool rightOpportunity();
	bool leftOpportunity();
	bool forwardOpportunity();
	Mouse *mouse;

public:
	Maze(Mouse *mouse);
	void printMaze();
	void start();
	void analyzePosition();
};

#endif
