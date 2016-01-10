#include "Maze.h"

//CHECK FOR OUT OF BOUNDS

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

	j = 15;
	for(int i = 0; i < 16; ++i){
		liveMaze[i][j].setWall("west"); //[k][15] 
	}
	i = 0;
	for(int j = 0; j < 16; ++j){
		liveMaze[i][j].setWall("south"); //[0][k] 
	}
	j = 0;
	for(int i = 0; i < 16; ++i){
		liveMaze[i][j].setWall("east");//[k][0] 
	}
	i = 15;
	for(int j = 0; j < 16; ++j){
		liveMaze[i][j].setWall("north");//[15][k] 
	}
	//Initial Cell
	liveMaze[0][15].setWall("east");


	//distances
	liveMaze[7][7].setDistance(0);
	liveMaze[7][8].setDistance(0);
	liveMaze[8][7].setDistance(0);
	liveMaze[8][8].setDistance(0);

	for(int x = 0; x < 16; ++x){
		for(int y = 0; y < 16; ++y){
			liveMaze[x][y].setCoordinates(x, y);
		}
	}


	for(int x = 0; x < 16; ++x){
		for(int y = 0; y < 16; ++y){
			if(x < 8 && y < 8)
				liveMaze[x][y].setDistance(abs(7 - x) + abs(7 - y));
			else if(x < 8 && y >= 8)
				liveMaze[x][y].setDistance(abs(7 - x) + abs(8 - y));
			else if(x >= 8 && y >= 8)
				liveMaze[x][y].setDistance(abs(8 - x) + abs(8 - y));
			else if(x >= 8 && y < 8)
				liveMaze[x][y].setDistance(abs(8 - x) + abs(7 - y));
		}
	}

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

void Maze :: setEastWestWalls(int up, int left){
	if(left != 15)
		maze[up][left + 1].setWall("east");
	maze[up][left].setWall("west");
}

void Maze :: setNorthSouthWalls(int up, int left){
	maze[up][left].setWall("north");
	maze[up + 1][left].setWall("south");
}

void Maze :: setLiveEastWestWalls(int up, int left){
	if(left != 15)
		liveMaze[up][left + 1].setWall("east");
	liveMaze[up][left].setWall("west");
}

void Maze :: setLiveNorthSouthWalls(int up, int left){
	liveMaze[up][left].setWall("north");
	liveMaze[up + 1][left].setWall("south");
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

void Maze :: printLiveMaze(){
	for(int i = 15; i >= 0; --i){
		for(int j = 15; j >= 0; --j){
			if(liveMaze[i][j].wallStatus("north"))
				cout << "+---+";
			else 
				cout << "+   +";
		}
		cout << endl;
		for(int j = 15; j >= 0; --j){
			if(mouse->returnXPos() == i && mouse->returnYPos() == j){
				if(liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
				cout << "|" << liveMaze[i][j].returnDistance() << mouse->mouseChar() << "|";
			else if(!liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
				cout << "|" << liveMaze[i][j].returnDistance() << mouse->mouseChar() << " ";
			else if(liveMaze[i][j].wallStatus("east") && !liveMaze[i][j].wallStatus("west"))
				cout << " " << liveMaze[i][j].returnDistance() << mouse->mouseChar() << "|";
			else
				cout << " " << liveMaze[i][j].returnDistance() << mouse->mouseChar() << " ";
			}
			else {
				if(liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
					cout << "|" << liveMaze[i][j].returnDistance() << " |";
				else if(!liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
					cout << "|" << liveMaze[i][j].returnDistance() << "  ";
				else if(liveMaze[i][j].wallStatus("east") && !liveMaze[i][j].wallStatus("west"))
					cout << " " << liveMaze[i][j].returnDistance() << " |";
				else
					cout << " " << liveMaze[i][j].returnDistance() << "  ";
			}
		}
		cout << endl;
		for(int j = 15; j >= 0; --j){
			if(liveMaze[i][j].wallStatus("south"))
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
	floodStack.push(liveMaze[mouse->returnXPos()][mouse->returnYPos()]); // Start Cell
	while(1){ // Not Goal Reached
		cout << string(50, '\n');
		printLiveMaze();

		floodFill();
		analyzePosition();
		
		mouse->step();
		//printMaze();
	}
}

void Maze :: setNewWall(int wallDirection, int x, int y){
	if(wallDirection == 0)
		setLiveNorthSouthWalls(x, y);
	else if(wallDirection == 1)
		setLiveEastWestWalls(x, y-1);
	else if(wallDirection == 2)
		setLiveNorthSouthWalls(x-1, y);
	else if(wallDirection == 3)
		setLiveEastWestWalls(x-1, y-1);
}

void Maze :: pushSelfAndAdjacentCells(int x, int y){
	for(int i = y + 1; i >= y - 1; --i){
		for(int j = x + 1; j >= x - 1; --j){
			floodStack.push(liveMaze[j][i]);
		}
	}
	
}

void Maze :: floodFill(){
	for(int i = 0; i < 4; ++i){
		//If NEW wall discovered
		//Pushing Current Cell And Adjacent Cells
		if(maze[mouse->returnXPos()][mouse->returnYPos()].wallStatus(i) &&
		 	!liveMaze[mouse->returnXPos()][mouse->returnYPos()].wallStatus(i)){
			setNewWall(i, mouse->returnXPos(), mouse->returnYPos());
			pushSelfAndAdjacentCells(mouse->returnXPos(), mouse->returnYPos());
			// printLiveMaze();
			// cout << "YES" << i << endl;
			// while(1) {}
		}
	}
	while(!floodStack.isEmpty()){
		Cell cellCheck = floodStack.pop();
		int minDistance = 99;
		//Grabbing Minimum Distance
		for(int i = 0; i < 4; ++i){
			if(!cellCheck.wallStatus(i)){
				if(i == 0){
					int cellDistance = liveMaze[cellCheck.returnXCoor() + 1]
					[cellCheck.returnYCoor()].returnIntDistance();
					if(cellDistance < minDistance)
						minDistance = cellDistance;
				}
				else if(i == 1){
					int cellDistance = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() - 1].returnIntDistance();
					if(cellDistance < minDistance)
						minDistance = cellDistance;
				}
				else if(i == 2){
					int cellDistance = liveMaze[cellCheck.returnXCoor() - 1]
					[cellCheck.returnYCoor()].returnIntDistance();
					if(cellDistance < minDistance)
						minDistance = cellDistance;
				}
				else if(i == 3){
					int cellDistance = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() + 1].returnIntDistance();
					if(cellDistance < minDistance)
						minDistance = cellDistance;
				}
			}
		}
		//The distance of currCell should be the minimum open neighbor + 1
		//If not, set that value and push all open neighbors to stack
		if(cellCheck.returnIntDistance() != 0 &&
		 	cellCheck.returnIntDistance() != minDistance + 1){
			if(minDistance != 99)
				liveMaze[cellCheck.returnXCoor()][cellCheck.returnYCoor()].
				setDistance(minDistance + 1);

			//Pushing all open neighbors to stack
			for(int i = 0; i < 4; ++i){
				if(!cellCheck.wallStatus(i)){
					if(i == 0){
						floodStack.push(liveMaze[cellCheck.returnXCoor() + 1]
							[cellCheck.returnYCoor()]);
					}
					else if(i == 1){
						floodStack.push(liveMaze[cellCheck.returnXCoor()]
							[cellCheck.returnYCoor() - 1]);
					}
					else if(i == 2){
						floodStack.push(liveMaze[cellCheck.returnXCoor() - 1]
							[cellCheck.returnYCoor()]);
					}
					else if(i == 3){
						floodStack.push(liveMaze[cellCheck.returnXCoor()]
							[cellCheck.returnYCoor() + 1]);
					}
				}
			}
		}
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
	int minDistance = 99;
	int minPosition = -1;
	//Grabbing Minimum Distance
	printLiveMaze();
	for(int i = 0; i < 4; ++i){
		if(!liveMaze[mouse->returnXPos()]
				[mouse->returnYPos()].wallStatus(i)){
			if(i == 0){
				int cellDistance = liveMaze[mouse->returnXPos() + 1]
				[mouse->returnYPos()].returnIntDistance();

				if(cellDistance < minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 1){
				int cellDistance = liveMaze[mouse->returnXPos()]
				[mouse->returnYPos() - 1].returnIntDistance();
				if(cellDistance < minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 2){
				int cellDistance = liveMaze[mouse->returnXPos() - 1]
				[mouse->returnYPos()].returnIntDistance();
				if(cellDistance < minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 3){
				int cellDistance = liveMaze[mouse->returnXPos()]
				[mouse->returnYPos() + 1].returnIntDistance();
				if(cellDistance < minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
		}
	}

	if(minPosition == -1){
		cout << "DEAD" << endl;
		while(1) {}
	}
	mouse->setFacing(minPosition);


}



// void Maze :: analyzePosition(){
// 	if(enclosedIn())
// 		mouse->transitionUTurn();
// 	else if(onlyRightOpen())
// 		mouse->transitionRightTurn();
// 	else if(onlyLeftOpen())
// 		mouse->transitionLeftTurn();
// 	else if(rightOpportunity() && leftOpportunity()){
// 		srand(time(NULL));
// 		int decision = rand() % 2;
// 		if(decision == 0)
// 			mouse->transitionLeftTurn();
// 		else if(decision == 1)
// 			mouse->transitionRightTurn();
// 		else{
// 			cout << "ERROR in right & left opp" << endl;
// 			while(1) {}
// 		}
// 	}
// 	else if(leftOpportunity() && forwardOpportunity()){
// 		srand(time(NULL));
// 		int decision = rand() % 2;
// 		if(decision == 0)
// 			mouse->transitionLeftTurn();
// 		else if(decision == 1)
// 			;
// 		else{
// 			cout << "ERROR in right & left opp" << endl;
// 			while(1) {}
// 		}
// 	}
// 	else if(rightOpportunity() && forwardOpportunity()){
// 		srand(time(NULL));
// 		int decision = rand() % 2;
// 		if(decision == 0)
// 			mouse->transitionRightTurn();
// 		else if(decision == 1)
// 			;
// 		else{
// 			cout << "ERROR in right & left opp" << endl;
// 			while(1) {}
// 		}
// 	}
// 	else if(rightOpportunity())
// 		mouse->transitionRightTurn();
// 	else if(leftOpportunity())
// 		mouse->transitionLeftTurn();
// 	else if(leftAndRightOpen())
// 		mouse->transitionLeftTurn();
// }

















