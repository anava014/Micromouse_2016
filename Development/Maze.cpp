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
	// maze[0][15].setWall("east");

	// j = 15;
	// for(int i = 0; i < 16; ++i){
	// 	liveMaze[i][j].setWall("west"); //[k][15] 
	// }
	// i = 0;
	// for(int j = 0; j < 16; ++j){
	// 	liveMaze[i][j].setWall("south"); //[0][k] 
	// }
	// j = 0;
	// for(int i = 0; i < 16; ++i){
	// 	liveMaze[i][j].setWall("east");//[k][0] 
	// }
	// i = 15;
	// for(int j = 0; j < 16; ++j){
	// 	liveMaze[i][j].setWall("north");//[15][k] 
	// }
	// //Initial Cell
	// liveMaze[0][15].setWall("east");

	drawMap();

}

void Maze :: drawMap(){

	importMapFromFile();
}

void Maze :: importMapFromFile(){
	int i = 16;
	int j = 15;
    ifstream file("currentMap.txt");
    string str, temp; 
    while (getline(file, str))
    {
    	--i;
        if(str[0] == '1'){
        	setNorthSouthWalls(j, i);
        }
        if(str[1] == '1'){
        	setEastWestWalls(j, i);
        }
        if(i < 0){
        	i = 15;
        	--j;
        }
    }
}

// void Maze :: drawVerticalLine(int start, int end, int left){
// 	for(int i = start; i < end; ++i){
// 		setEastWestWalls(i, left);
// 	}
// }

// void Maze :: drawHorizontalLine(int start, int end, int up){
// 	for(int i = start; i < end; ++i){
// 		setNorthSouthWalls(up, i);
// 	}
// }

void Maze :: setEastWestWalls(int up, int left){
	if(left != 15)
		maze[up][left + 1].setWall("east");
	maze[up][left].setWall("west");
}

void Maze :: setNorthSouthWalls(int up, int left){
	maze[up][left].setWall("north");
	maze[up + 1][left].setWall("south");
}

// void Maze :: drawLineEnclosure(){
// 	//Row round about enclosure
// 	int j = 15;
// 	for(int i = 0; i < 16; ++i){
// 		maze[i][j].setWall("east"); //[k][15] 
// 	}
// 	j = 14;
// 	for(int i = 0; i < 16; ++i){
// 		maze[i][j].setWall("west"); //[k][15] 
// 	}
// }

// void Maze :: drawMiddleLine(){
// 	int i = 7;
// 	for(int j = 0; j < 16; ++j){
// 		maze[i][j].setWall("north");//[15][k] 
// 	}
// 	i = 8;
// 	for(int j = 0; j < 16; ++j){
// 		maze[i][j].setWall("south");//[15][k] 
// 	}
// }

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

bool Maze :: enclosedIn(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(maze[xPos][yPos].wallStatus(mouse->returnDecrementedFacing())
		&& maze[xPos][yPos].wallStatus(mouse->returnFacing())
		&& maze[xPos][yPos].wallStatus(mouse->returnIncrementedFacing()))
		return true;
	else
		return false;
}

bool Maze :: onlyRightOpen(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(maze[xPos][yPos].wallStatus(mouse->returnDecrementedFacing())
		&& maze[xPos][yPos].wallStatus(mouse->returnFacing())
		&& !(maze[xPos][yPos].wallStatus(mouse->returnIncrementedFacing())))
		return true;
	else
		return false;
}

bool Maze :: onlyLeftOpen(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(!maze[xPos][yPos].wallStatus(mouse->returnDecrementedFacing())
		&& maze[xPos][yPos].wallStatus(mouse->returnFacing())
		&& (maze[xPos][yPos].wallStatus(mouse->returnIncrementedFacing())))
		return true;
	else
		return false;
}

bool Maze :: leftAndRightOpen(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(!maze[xPos][yPos].wallStatus(mouse->returnDecrementedFacing())
		&& maze[xPos][yPos].wallStatus(mouse->returnFacing())
		&& !(maze[xPos][yPos].wallStatus(mouse->returnIncrementedFacing())))
		return true;
	else
		return false;
}

bool Maze :: forwardOpportunity(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(!maze[xPos][yPos].wallStatus(mouse->returnFacing()))
		return true;
	else
		return false;
}

bool Maze :: rightOpportunity(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(!maze[xPos][yPos].wallStatus(mouse->returnIncrementedFacing()))
		return true;
	else
		return false;
}

bool Maze :: leftOpportunity(){
	int xPos = mouse->returnXPos();
	int yPos = mouse->returnYPos();

	if(!maze[xPos][yPos].wallStatus(mouse->returnDecrementedFacing()))
		return true;
	else
		return false;
}

void Maze :: analyzePosition(){
	if(enclosedIn())
		mouse->transitionUTurn();
	else if(onlyRightOpen())
		mouse->transitionRightTurn();
	else if(onlyLeftOpen())
		mouse->transitionLeftTurn();
	else if(rightOpportunity() && leftOpportunity()){
		srand(time(NULL));
		int decision = rand() % 2;
		if(decision == 0)
			mouse->transitionLeftTurn();
		else if(decision == 1)
			mouse->transitionRightTurn();
		else{
			cout << "ERROR in right & left opp" << endl;
			while(1) {}
		}
	}
	else if(leftOpportunity() && forwardOpportunity()){
		srand(time(NULL));
		int decision = rand() % 2;
		if(decision == 0)
			mouse->transitionLeftTurn();
		else if(decision == 1)
			;
		else{
			cout << "ERROR in right & left opp" << endl;
			while(1) {}
		}
	}
	else if(rightOpportunity() && forwardOpportunity()){
		srand(time(NULL));
		int decision = rand() % 2;
		if(decision == 0)
			mouse->transitionRightTurn();
		else if(decision == 1)
			;
		else{
			cout << "ERROR in right & left opp" << endl;
			while(1) {}
		}
	}
	else if(rightOpportunity())
		mouse->transitionRightTurn();
	else if(leftOpportunity())
		mouse->transitionLeftTurn();
	else if(leftAndRightOpen())
		mouse->transitionLeftTurn();
}

















