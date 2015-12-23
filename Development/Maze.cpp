#include "Maze.h"

Maze :: Maze(Mouse *mouse){
	this->mouse = mouse;

	//Borders
	int j = 15;
	for(int i = 0; i < 16; ++i){
		maze[i][j].setWall("west"); //[k][15] 
	}
	int i = 0;
	for(int j = 0; j < 16; ++j){
		maze[i][j].setWall("south"); //[0][k] 
	}
	j = 0;
	for(int i = 0; i < 16; ++i){
		maze[i][j].setWall("east");//[k][0] 
	}
	i = 15;
	for(int j = 0; j < 16; ++j){
		maze[i][j].setWall("north");//[15][k] 
	}
	//Initial Cell
	maze[0][15].setWall("east");

	drawMiddleLine();

	//Row round about enclosure
	j = 15;
	for(int i = 0; i < 16; ++i){
		maze[i][j].setWall("east"); //[k][15] 
	}
	j = 14;
	for(int i = 0; i < 16; ++i){
		maze[i][j].setWall("west"); //[k][15] 
	}

}

void Maze :: drawMiddleLine(){
	int i = 7;
	for(int j = 0; j < 16; ++j){
		maze[i][j].setWall("north");//[15][k] 
	}
	i = 8;
	for(int j = 0; j < 16; ++j){
		maze[i][j].setWall("south");//[15][k] 
	}
}

void Maze :: printMaze(){
	for(int i = 15; i >= 0; --i){
		for(int j = 15; j >= 0; --j){
			if(maze[i][j].wallStatus("north"))
				cout << "+---+";
			else 
				cout << "+   +";
		}
		cout << endl;
		for(int j = 15; j >= 0; --j){
			if(mouse->returnXPos() == i && mouse->returnYPos() == j){
				if(maze[i][j].wallStatus("east") && maze[i][j].wallStatus("west"))
				cout << "| " << mouse->mouseChar() << " |";
			else if(!maze[i][j].wallStatus("east") && maze[i][j].wallStatus("west"))
				cout << "| " << mouse->mouseChar() << "  ";
			else if(maze[i][j].wallStatus("east") && !maze[i][j].wallStatus("west"))
				cout << "  " << mouse->mouseChar() << " |";
			else
				cout << "  " << mouse->mouseChar() << "  ";
			}
			else {
				if(maze[i][j].wallStatus("east") && maze[i][j].wallStatus("west"))
					cout << "|   |";
				else if(!maze[i][j].wallStatus("east") && maze[i][j].wallStatus("west"))
					cout << "|    ";
				else if(maze[i][j].wallStatus("east") && !maze[i][j].wallStatus("west"))
					cout << "    |";
				else
					cout << "     ";
			}
		}
		cout << endl;
		for(int j = 15; j >= 0; --j){
			if(maze[i][j].wallStatus("south"))
				cout << "+---+";
			else 
				cout << "+   +";
		}
		cout << endl;
	}

	cout << "Coordinates: " << mouse->returnXPos() << ", " << mouse->returnYPos() << endl;
	cout << "Facing: " << mouse->returnFacing() << endl;
}


void Maze :: start(){
	while(1){
		mouse->step();
		analyzePosition();
		cout << string(50, '\n');
		printMaze();
	}
}

void Maze :: analyzePosition(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();
	int facing = mouse->returnFacing();
	if(facing == 0 && maze[xPos][yPos].wallStatus("north"))
		mouse->setFacing(1);
	if(facing == 1 && maze[xPos][yPos].wallStatus("south"))
		mouse->setFacing(0);
}

















