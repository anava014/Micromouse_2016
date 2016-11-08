#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"
#include "Mouse.h"
#include "CellStack.h"
#include "CellNode.h"
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Maze{
private:
	Cell maze[16][16];
	Cell liveMaze[16][16];
	CellStack floodStack;
	Cell optimalRoute[100];
	CellNode *root;       // This won't change, or we would lose the list in memory
    CellNode *conductor;  // This will point to each node as it traverses the list

	//CellArray paths[100];
	int sizeOfPaths;
	//int pathElement;

	int optimalRouteSize;
	int optimalRouteIterator;
	void drawMiddleLine();
	void drawLineEnclosure();
	void drawMap();
	void drawVerticalLine(int start, int end, int left);
	void drawHorizontalLine(int start, int end, int up);
	void importMapFromFile();

	void setEastWestWalls(int up, int left);
	void setNorthSouthWalls(int up, int left);

	void setLiveEastWestWalls(int up, int left);
	void setLiveNorthSouthWalls(int up, int left);

	bool enclosedIn();
	bool onlyRightOpen();
	bool onlyLeftOpen();
	bool leftAndRightOpen();
	bool rightOpportunity();
	bool leftOpportunity();
	bool forwardOpportunity();

	void pushSelfAndAdjacentCells(int x, int y);
	Mouse *mouse;

public:
	Maze(Mouse *mouse);
	void printMaze();
	void printLiveMaze();
	void start();
	void analyzePosition();
	void floodFill();
	void setNewWall(int wallDirection, int x, int y);
	void speedRun();
	void optimizeRoute();
	void analyzePositionAndOptimize();
	int traverse(int currPosX, int currPosY, int distance);


};

#endif
