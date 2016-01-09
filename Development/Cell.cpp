#include "Cell.h"

Cell :: Cell(){
	cellDrawing = "";
	hasTraversed = false;

	northWall.markNotPresent(); 
	southWall.markNotPresent(); 
	eastWall.markNotPresent(); 
	westWall.markNotPresent(); 

	fillTop();
	fillLeftRight();
	fillBottom();
}

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

void Cell :: setMouseInCell(){
	liveMouse = true;
}

void Cell :: removeMouseInCell(){
	liveMouse = false;
}

void Cell :: setWall(string direction){
	if(direction == "north")
		northWall.markPresent();
	else if(direction == "south")
		southWall.markPresent();
	else if(direction == "east")
		eastWall.markPresent();
	else if(direction == "west")
		westWall.markPresent();
}

bool Cell :: wallStatus(string direction){
	if(direction == "north")
		return northWall.returnIsPresent();
	else if(direction == "south")
		return southWall.returnIsPresent();
	else if(direction == "east")
		return eastWall.returnIsPresent();
	else if(direction == "west")
		return westWall.returnIsPresent();
	cout << endl << "ERROR: Reached end of wallStatus in Cell.cpp" << endl;
	return false;
}

bool Cell :: wallStatus(int facing){
	if(facing == 0)
		return northWall.returnIsPresent();
	else if(facing == 2)
		return southWall.returnIsPresent();
	else if(facing == 1)
		return eastWall.returnIsPresent();
	else if(facing == 3)
		return westWall.returnIsPresent();
	cout << endl << "ERROR: Reached end of wallStatus in Cell.cpp" << endl;
	return false;
}

void Cell :: fillTop(){
	if(northWall.returnIsPresent())
		cellDrawing += "+---+\n";
	else
		cellDrawing += "+   +\n";
}

void Cell :: fillLeftRight(){
	if(eastWall.returnIsPresent() && westWall.returnIsPresent())
		cellDrawing += "|   |\n";
	else if(!eastWall.returnIsPresent() && westWall.returnIsPresent())
		cellDrawing += "|    \n";
	else if(eastWall.returnIsPresent() && !westWall.returnIsPresent())
		cellDrawing += "    |\n";
	else
		cellDrawing += "     \n";
}

void Cell :: fillBottom(){
	if(southWall.returnIsPresent())
		cellDrawing += "+---+";
	else
		cellDrawing += "+   +";
}

void Cell :: printCell(){
	cout << cellDrawing;
}
