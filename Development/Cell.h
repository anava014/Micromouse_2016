#ifndef CELL_H
#define CELL_H

#include "Wall.h"

class Cell{
private:
	Wall northWall;
	Wall southWall;
	Wall eastWall;
	Wall westWall;

	bool hasTraversed = false;

public:
	Cell();
	void printCell();

};

#endif
