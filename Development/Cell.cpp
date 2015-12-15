#include "Cell.h"

Cell :: Cell(bool north, bool south, bool east, bool west){
	cellDrawing = "";
	hasTraversed = false;

	(north) ? (northWall.markPresent()) : (northWall.markNotPresent()); 
	(south) ? (southWall.markPresent()) : (southWall.markNotPresent()); 
	(east) ? (eastWall.markPresent()) : (eastWall.markNotPresent()); 
	(west) ? (westWall.markPresent()) : (westWall.markNotPresent()); 

	fillTop();
	fillLeftRight();
	fillBottom();
}

void Cell :: fillTop(){
	if(northWall.returnIsPresent())
		cellDrawing += "+----+\n";
	else
		cellDrawing += "+    +\n";
}

void Cell :: fillLeftRight(){
	if(eastWall.returnIsPresent() && westWall.returnIsPresent())
		cellDrawing += "|    |\n|    |\n";
	else if(!eastWall.returnIsPresent() && westWall.returnIsPresent())
		cellDrawing += "|     \n|     \n";
	else if(eastWall.returnIsPresent() && !westWall.returnIsPresent())
		cellDrawing += "     |\n     |\n";
	else
		cellDrawing += "      \n      \n";
}

void Cell :: fillBottom(){
	if(southWall.returnIsPresent())
		cellDrawing += "+----+\n";
	else
		cellDrawing += "+    +\n";
}

void Cell :: printCell(){
	cout << cellDrawing << endl;
}
