#ifndef CELL_H
#define CELL_H

#include "Wall.h"
#include <iostream>
using namespace std;

class Cell{
private:
	Wall northWall;
	Wall southWall;
	Wall eastWall;
	Wall westWall;

	bool hasTraversed;

	string cellDrawing;

	void fillTop();
	void fillLeftRight();
	void fillBottom();
	bool liveMouse;

public:
	Cell();
	Cell(bool north, bool south, bool east, bool west);
	void printCell();
	bool wallStatus(string direction);
	void setWall(string direction);
	void setMouseInCell();
	void removeMouseInCell();

};

#endif
