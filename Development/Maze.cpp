#include "Maze.h"

//CHECK FOR OUT OF BOUNDS

Maze :: Maze(Mouse *mouse){
	this->mouse = mouse;
	optimalRouteIterator = 0;
	sizeOfPaths = 0;
	//pathElement = -1;

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
	setLiveEastWestWalls(0,14);
	//liveMaze[0][15].setWall("east");


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

	//cout << "Coordinates: " << mouse->returnXPos() << ", " << mouse->returnYPos() << endl;
	//cout << "Facing: " << mouse->returnFacing() << endl;
}


void Maze :: start(){
	bool searchOver = false;
	floodStack.push(liveMaze[mouse->returnXPos()][mouse->returnYPos()]); // Start Cell
	while(!searchOver){ // Not Goal Reached
		cout << string(50, '\n');
		printLiveMaze();

		floodFill();
		analyzePosition();
		
		mouse->step();
		if(mouse->searchRunComplete())
			searchOver = true;
	}

	liveMaze[7][7].setDistance(99);
	liveMaze[7][8].setDistance(99);
	liveMaze[8][7].setDistance(99);
	liveMaze[8][8].setDistance(99);

	liveMaze[0][15].setDistance(0);

	printLiveMaze();

	searchOver = false;

	floodStack.push(liveMaze[mouse->returnXPos()][mouse->returnYPos()]); // Start Cell
	while(!searchOver){ // Not Goal Reached
		cout << string(50, '\n');
		printLiveMaze();

		floodFill();
		analyzePosition();
		//analyzePositionAndOptimize();
		
		mouse->step();
		if(mouse->homeRunComplete())
			searchOver = true;
	}

	optimizeRoute();
	// cout << "== RUN TERMINATED == " << endl;
	// cout << "Size of paths: " << sizeOfPaths << endl;

	// CellNode *current;
	// cout << "== In Traverse == " << endl;
	// for(current = root; current != NULL; current = current->next) {
	// 	cout <<	" distance: " << current->data.returnIntDistance() << " -> ";
	// }
	// cout << "NULL" << endl;

	// for (int i = 0; i < sizeOfPaths; ++i){
	// 	cout << "Path " << i << ": " << endl;
	// 	for(int j = 0; j < paths[i].sizeOf(); ++j){
	// 		cout << "\t" << paths[i].path[j].returnIntDistance() << endl;
	// 	}
	// 	cout << "---------------------------------------------\n" << endl;
	// }


	printLiveMaze();
	speedRun();
}

void Maze :: speedRun(){
	int optimalRouteIterator = optimalRouteSize-1;
	while(optimalRouteIterator >= 0){
		// cout << "optimalRouteIterator:" << optimalRouteIterator << endl;
		// cout << "Cell X: " << optimalRoute[optimalRouteIterator].returnXCoor() << endl;
		// cout << "Cell Y: " << optimalRoute[optimalRouteIterator].returnYCoor() << endl;
		// cout << "Mouse X: " << mouse->returnXPos() << endl;
		// cout << "Mouse Y: " << mouse->returnYPos() << endl;
		// char temp;
		// cout << "Enter key:";
		// cin >> temp;

		if(optimalRoute[optimalRouteIterator].returnXCoor() > mouse->returnXPos()
			&& optimalRoute[optimalRouteIterator].returnYCoor() == mouse->returnYPos()){
			mouse->setFacing(0);
		}
		else if(optimalRoute[optimalRouteIterator].returnXCoor() < mouse->returnXPos()
				&& optimalRoute[optimalRouteIterator].returnYCoor() == mouse->returnYPos()){
			mouse->setFacing(2);
		}
		else if(optimalRoute[optimalRouteIterator].returnXCoor() == mouse->returnXPos()
					&& optimalRoute[optimalRouteIterator].returnYCoor() < mouse->returnYPos()){
			mouse->setFacing(1);
		}
		else if(optimalRoute[optimalRouteIterator].returnXCoor() == mouse->returnXPos()
					&& optimalRoute[optimalRouteIterator].returnYCoor() > mouse->returnYPos()){
			mouse->setFacing(3);
		}
		optimalRouteIterator--;
		cout << string(50, '\n');
		printLiveMaze();
		// cout << "Cell X: " << optimalRoute[optimalRouteIterator].returnXCoor() << endl;
		// cout << "Cell Y: " << optimalRoute[optimalRouteIterator].returnYCoor() << endl;
		cout << "Mouse X: " << mouse->returnXPos() << endl;
		cout << "Mouse Y: " << mouse->returnYPos() << endl;
		
		mouse->step();
	}
}

// Default
void Maze :: optimizeRoute(){
	int minPosition = -1;
	int minDistance = 99;
	int optimalRouteIterator = 0;
	Cell cellCheck = liveMaze[7][7];
	optimalRoute[optimalRouteIterator++] = liveMaze[7][7];
	cout << "X: " << cellCheck.returnXCoor() << "Y: " << cellCheck.returnYCoor()
			<< "D: " << cellCheck.returnDistance() << endl;
	while(cellCheck.returnIntDistance() != 0){
		
		for(int i = 0; i < 4; ++i){
			if(!cellCheck.wallStatus(i)){
				if(i == 0){
					int cellDistance = liveMaze[cellCheck.returnXCoor() + 1]
					[cellCheck.returnYCoor()].returnIntDistance();
					if(cellDistance < minDistance){
						minDistance = cellDistance;
						minPosition = i;
					}
				}
				else if(i == 1){
					int cellDistance = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() - 1].returnIntDistance();
					if(cellDistance < minDistance){
						minDistance = cellDistance;
						minPosition = i;
					}
				}
				else if(i == 2){
					int cellDistance = liveMaze[cellCheck.returnXCoor() - 1]
					[cellCheck.returnYCoor()].returnIntDistance();
					if(cellDistance < minDistance){
						minDistance = cellDistance;
						minPosition = i;
					}
				}
				else if(i == 3){
					int cellDistance = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() + 1].returnIntDistance();
					if(cellDistance < minDistance){
						minDistance = cellDistance;
						minPosition = i;
					}
				}
			}
		}
		if(minPosition == 0){
			cellCheck = liveMaze[cellCheck.returnXCoor() + 1]
					[cellCheck.returnYCoor()];
			// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor() + 1]
			// 		[cellCheck.returnYCoor()];
		}
		else if(minPosition == 1){
			cellCheck = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() - 1];
			// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor()]
			// 		[cellCheck.returnYCoor() - 1];
		}
		else if(minPosition == 2){
			cellCheck = liveMaze[cellCheck.returnXCoor() -1]
					[cellCheck.returnYCoor()];
			// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor() -1]
			// 		[cellCheck.returnYCoor()];
		}
		else if(minPosition == 3){
			cellCheck = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor()+1];
			// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor()]
			// 		[cellCheck.returnYCoor()+1];
		}

		optimalRoute[optimalRouteIterator++] = cellCheck;
	}

	optimalRouteSize = optimalRouteIterator-1;
}

//New Algorithm
// void Maze :: optimizeRoute(){
// 	traverse(mouse->returnXPos(), mouse->returnYPos(), 0);
	// int minPosition = -1;
	// int maxDistance = 99;
	// int optimalRouteIterator = 0;
	// Cell cellCheck = liveMaze[7][7];
	// optimalRoute[optimalRouteIterator++] = liveMaze[7][7];
	// printLiveMaze();
	// cout << "X: " << cellCheck.returnXCoor() << "Y: " << cellCheck.returnYCoor()
	// 		<< "D: " << cellCheck.returnDistance() << endl;

	// while(cellCheck.returnIntDistance() != 0){
		
	// 	for(int i = 0; i < 4; ++i){
	// 		if(!cellCheck.wallStatus(i)){
	// 			if(i == 0){
	// 				int cellDistance = liveMaze[cellCheck.returnXCoor() + 1]
	// 				[cellCheck.returnYCoor()].returnIntDistance();
	// 				if(cellDistance < maxDistance){
	// 					maxDistance = cellDistance;
	// 					minPosition = i;
	// 				}
	// 			}
	// 			else if(i == 1){
	// 				int cellDistance = liveMaze[cellCheck.returnXCoor()]
	// 				[cellCheck.returnYCoor() - 1].returnIntDistance();
	// 				if(cellDistance < maxDistance){
	// 					maxDistance = cellDistance;
	// 					minPosition = i;
	// 				}
	// 			}
	// 			else if(i == 2){
	// 				int cellDistance = liveMaze[cellCheck.returnXCoor() - 1]
	// 				[cellCheck.returnYCoor()].returnIntDistance();
	// 				if(cellDistance < maxDistance){
	// 					maxDistance = cellDistance;
	// 					minPosition = i;
	// 				}
	// 			}
	// 			else if(i == 3){
	// 				int cellDistance = liveMaze[cellCheck.returnXCoor()]
	// 				[cellCheck.returnYCoor() + 1].returnIntDistance();
	// 				if(cellDistance < maxDistance){
	// 					maxDistance = cellDistance;
	// 					minPosition = i;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	if(minPosition == 0){
	// 		cellCheck = liveMaze[cellCheck.returnXCoor() + 1]
	// 				[cellCheck.returnYCoor()];
	// 		// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor() + 1]
	// 		// 		[cellCheck.returnYCoor()];
	// 	}
	// 	else if(minPosition == 1){
	// 		cellCheck = liveMaze[cellCheck.returnXCoor()]
	// 				[cellCheck.returnYCoor() - 1];
	// 		// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor()]
	// 		// 		[cellCheck.returnYCoor() - 1];
	// 	}
	// 	else if(minPosition == 2){
	// 		cellCheck = liveMaze[cellCheck.returnXCoor() -1]
	// 				[cellCheck.returnYCoor()];
	// 		// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor() -1]
	// 		// 		[cellCheck.returnYCoor()];
	// 	}
	// 	else if(minPosition == 3){
	// 		cellCheck = liveMaze[cellCheck.returnXCoor()]
	// 				[cellCheck.returnYCoor()+1];
	// 		// optimalRoute[optimalRouteIterator++] = liveMaze[cellCheck.returnXCoor()]
	// 		// 		[cellCheck.returnYCoor()+1];
	// 	}
	// 	cout << "X: " << cellCheck.returnXCoor() << "Y: " << cellCheck.returnYCoor()
	// 		<< "D: " << cellCheck.returnDistance() << endl;

	// 	optimalRoute[optimalRouteIterator++] = cellCheck;
	// }

	// optimalRouteSize = optimalRouteIterator-1;
// }

int Maze :: traverse(int currPosX, int currPosY, int distance){
	Cell cellCheck = liveMaze[currPosX][currPosY];
	
	printLiveMaze();
	cout << "Coordinates: " << currPosX << ", " << currPosY << endl;
	
	for(int i = 0; i < 4; ++i){
		if(!cellCheck.wallStatus(i)){
			if(i == 0)
				cout << "North Wall Open" << endl;
			else if(i == 1)
				cout << "East Wall Open" << endl;
			else if(i == 2)
				cout << "South Wall Open" << endl;
			else if(i == 3)
				cout << "West Wall Open" << endl;
		}
	}

	if(root == NULL){
		root = new CellNode(cellCheck);
		root->next = 0;   //  Otherwise it would not work well
    	root->data = cellCheck;
    	conductor = root;
    	
    }
	else {
		conductor->next = new CellNode();  // Creates a node at the end of the list
		conductor = conductor->next; // Points to that node
		conductor->next = 0;         // Prevents it from going any further
		conductor->data = cellCheck;
	}

	char temp;
	cout << "Enter key:";
	cin >> temp;
	
	int pathElement = -1;
	//printLiveMaze();
	//pathLink.pushCell(cellCheck);
	// cout << "== In Traverse == " << endl;
	// cout << "Stats: currPosX: " << cellCheck.returnXCoor() << " currPosY: "
	// 	 << cellCheck.returnYCoor()
	// 	 <<	" distance: " << cellCheck.returnIntDistance() << endl;
	//char temp;
	//cout << "Enter key:";
	//cin >> temp;

	
	liveMaze[currPosX][currPosY].setEffTraversed();
	for(int i = 0; i < 4; ++i){
		if(!cellCheck.wallStatus(i)){
			if(i == 0){
				int futureCellDistance = liveMaze[currPosX + 1]
				[currPosY].returnIntDistance();
				int cellDistance = liveMaze[currPosX]
				[currPosY].returnIntDistance();	
				//If cell ahead is higher and we've traversed it once
				if((liveMaze[currPosX + 1]
				[currPosY].returnHasTraversed() &&
				futureCellDistance > cellDistance) ||
				(!liveMaze[currPosX + 1]
				[currPosY].returnHasEffTraversed() &&
				futureCellDistance < cellDistance)){
					//cout << "Completed main conditional" << endl;
					pathElement = traverse(currPosX + 1, currPosY, distance);
					
					// else{
					
					//cout << "Path Element: " << pathElement << endl;
				    if(((currPosX + 1 == 7 && currPosY == 7) ||
						(currPosX + 1 == 7 && currPosY == 8) ||
						(currPosX + 1 == 8 && currPosY == 7) ||
						(currPosX + 1 == 8 && currPosY == 8))) {
				    		++pathElement;
							++sizeOfPaths;
							cout << "Path Element: " << pathElement << endl;
							//return pathElement;
				    }
				 //    if(pathElement >=0){
				 //    	//cout << "EVER IN HERE: " << i << endl;
					//     cellCheck = liveMaze[currPosX + 1][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	 //return pathElement;
					// }
				 	//    else if(pathElement >= 0 && ((currPosX + 1 == 7 && currPosY == 7) ||
					// 	(currPosX + 1 == 7 && currPosY == 8) ||
					// 	(currPosX + 1 == 8 && currPosY == 7) ||
					// 	(currPosX + 1 == 8 && currPosY == 8))) {

					// 	cellCheck = liveMaze[currPosX + 1][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	 cout << "In Second If" << endl;
					// 	return pathElement;
					// }
					// else if(pathElement >= 0){
					// 	cellCheck = liveMaze[currPosX][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	//return pathElement;
					// }
				}
				// else 
				// 	return -1;
			}
			else if(i == 1){
				int futureCellDistance = liveMaze[currPosX]
				[currPosY - 1].returnIntDistance();
				int cellDistance = liveMaze[currPosX]
				[currPosY].returnIntDistance();
				//If cell ahead is higher and we've traversed it once
				if((liveMaze[currPosX]
				[currPosY - 1].returnHasTraversed() &&
				futureCellDistance > cellDistance) ||
				(!liveMaze[currPosX]
				[currPosY - 1].returnHasEffTraversed() &&
				futureCellDistance < cellDistance)){
					pathElement = traverse(currPosX, currPosY - 1, distance);
					// if(pathElement < 0)
					// 	return -1;
					// else{
					if(((currPosX == 7 && currPosY - 1 == 7) ||
						(currPosX == 7 && currPosY - 1 == 8) ||
						(currPosX == 8 && currPosY - 1 == 7) ||
						(currPosX == 8 && currPosY - 1 == 8))) {
							++pathElement;
							++sizeOfPaths;
							cout << "Path Element: " << pathElement << endl;
				    }
				 //    if(pathElement >=0){
				 //    	//cout << "EVER IN HERE: " << i << " " << cellCheck.returnIntDistance() << endl;
					//     cellCheck = liveMaze[currPosX][currPosY - 1];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	//return pathElement;
					// }
					//return pathElement;

				 //    else if(pathElement >= 0 && ((currPosX == 7 && currPosY - 1 == 7) ||
					// 	(currPosX == 7 && currPosY - 1 == 8) ||
					// 	(currPosX == 8 && currPosY - 1 == 7) ||
					// 	(currPosX == 8 && currPosY - 1 == 8))) {

					// 	cellCheck = liveMaze[currPosX][currPosY - 1];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	return pathElement;
					// }
					// else if(pathElement >= 0){
					// 	cellCheck = liveMaze[currPosX][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	//return pathElement;
					// }
				}
				// else 
				// 	return -1;
			}
			//X - 1, Y
			else if(i == 2){
				int futureCellDistance = liveMaze[currPosX - 1]
				[currPosY].returnIntDistance();
				int cellDistance = liveMaze[currPosX]
				[currPosY].returnIntDistance();
				//If cell ahead is higher and we've traversed it once
				if((liveMaze[currPosX - 1]
				[currPosY].returnHasTraversed() &&
				futureCellDistance > cellDistance) ||
				(!liveMaze[currPosX - 1]
				[currPosY].returnHasEffTraversed() &&
				futureCellDistance < cellDistance)){
					pathElement = traverse(currPosX - 1, currPosY, distance);
					// if(pathElement < 0)
					// 	return -1;
					// else{
					if(((currPosX - 1 == 7 && currPosY == 7) ||
						(currPosX - 1 == 7 && currPosY == 8) ||
						(currPosX - 1 == 8 && currPosY == 7) ||
						(currPosX - 1 == 8 && currPosY == 8))) {
							++pathElement;
							++sizeOfPaths;
							cout << "Path Element: " << pathElement << endl;
				    }
				 //    if(pathElement >=0){
				 //    	//cout << "EVER IN HERE: " << i << endl;
					// 	paths[pathElement].upSize();
					//     cellCheck = liveMaze[currPosX - 1][currPosY];
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	 //return pathElement;
					// }

				 //    else if(pathElement >= 0 && ((currPosX - 1 == 7 && currPosY == 7) ||
					// 	(currPosX - 1 == 7 && currPosY == 8) ||
					// 	(currPosX - 1 == 8 && currPosY == 7) ||
					// 	(currPosX - 1 == 8 && currPosY == 8))) {

					// 	cellCheck = liveMaze[currPosX - 1][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	return pathElement;
					// }
					// else if(pathElement >= 0){
					// 	cellCheck = liveMaze[currPosX][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	//return pathElement;
					// }
				}
				// else 
				// 	return -1;
			}
			//X , Y + 1
			else if(i == 3){
				int futureCellDistance = liveMaze[currPosX]
				[currPosY + 1].returnIntDistance();
				int cellDistance = liveMaze[currPosX]
				[currPosY].returnIntDistance();
				//If cell ahead is higher and we've traversed it once
				if((liveMaze[currPosX]
				[currPosY + 1].returnHasTraversed() &&
				futureCellDistance > cellDistance) ||
				(!liveMaze[currPosX]
				[currPosY + 1].returnHasEffTraversed() &&
				futureCellDistance < cellDistance)){
					pathElement = traverse(currPosX, currPosY + 1, distance);
					if(((currPosX == 7 && currPosY + 1 == 7) ||
						(currPosX == 7 && currPosY + 1 == 8) ||
						(currPosX == 8 && currPosY + 1 == 7) ||
						(currPosX == 8 && currPosY + 1 == 8))) {
							++pathElement;
							++sizeOfPaths;
							cout << "Path Element: " << pathElement << endl;
				    		
				    }
				 //    if(pathElement >=0){
				 //    	// cout << "EVER IN HERE: " << i << " " << cellCheck.returnIntDistance() << endl;
					//     cellCheck = liveMaze[currPosX][currPosY + 1];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	 //return pathElement;
					// }

				 //    else if(pathElement >= 0 && ((currPosX == 7 && currPosY + 1 == 7) ||
					// 	(currPosX == 7 && currPosY + 1 == 8) ||
					// 	(currPosX == 8 && currPosY + 1 == 7) ||
					// 	(currPosX == 8 && currPosY + 1 == 8))) {

					// 	cellCheck = liveMaze[currPosX][currPosY + 1];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	return pathElement;
					// }
					// else if(pathElement >= 0){
					// 	cellCheck = liveMaze[currPosX][currPosY];
					// 	paths[pathElement].upSize();
					// 	paths[pathElement].path[cellCheck.returnIntDistance()]
					// 	 = cellCheck;
					// 	//return pathElement;
					// }
				}
				// else 
				// 	return pathElement;
			}
		}
	}
	return pathElement;
}

void Maze :: setNewWall(int wallDirection, int x, int y){
	if(wallDirection == 0)
		setLiveNorthSouthWalls(x, y);
	else if(wallDirection == 1)
		setLiveEastWestWalls(x, y-1);
	else if(wallDirection == 2)
		setLiveNorthSouthWalls(x-1, y);
	else if(wallDirection == 3)
		setLiveEastWestWalls(x, y);
}

void Maze :: pushSelfAndAdjacentCells(int x, int y){
	for(int i = y + 1; i >= y - 1; --i){
		for(int j = x + 1; j >= x - 1; --j){
			floodStack.push(liveMaze[j][i]);
		}
	}
	
}

void Maze :: floodFill(){
	liveMaze[mouse->returnXPos()][mouse->returnYPos()].setTraversed();
	for(int i = 0; i < 4; ++i){
		//If NEW wall discovered
		//Pushing Current Cell And Adjacent Cells
		if(maze[mouse->returnXPos()][mouse->returnYPos()].wallStatus(i) &&
		 	!liveMaze[mouse->returnXPos()][mouse->returnYPos()].wallStatus(i)){
			setNewWall(i, mouse->returnXPos(), mouse->returnYPos());
			pushSelfAndAdjacentCells(mouse->returnXPos(), mouse->returnYPos());
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
					if(cellDistance <= minDistance)
						minDistance = cellDistance;
				}
				else if(i == 1){
					int cellDistance = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() - 1].returnIntDistance();
					if(cellDistance <= minDistance)
						minDistance = cellDistance;
				}
				else if(i == 2){
					int cellDistance = liveMaze[cellCheck.returnXCoor() - 1]
					[cellCheck.returnYCoor()].returnIntDistance();
					if(cellDistance <= minDistance)
						minDistance = cellDistance;
				}
				else if(i == 3){
					int cellDistance = liveMaze[cellCheck.returnXCoor()]
					[cellCheck.returnYCoor() + 1].returnIntDistance();
					if(cellDistance <= minDistance)
						minDistance = cellDistance;
				}
			}
		}
		//The distance of currCell should be the minimum open neighbor + 1
		//If not, set that value and push all open neighbors to stack
		if(cellCheck.returnIntDistance() != 0 &&
		 	cellCheck.returnIntDistance() != minDistance + 1){
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
	int priority = -1;
	//Grabbing Minimum Distance
	liveMaze[mouse->returnXPos()][mouse->returnYPos()].setTraversed();
	printLiveMaze();
	for(int i = 0; i < 4; ++i){
		if(!liveMaze[mouse->returnXPos()]
				[mouse->returnYPos()].wallStatus(i)){
			
			if(i == 0){
				int cellDistance = liveMaze[mouse->returnXPos() + 1]
				[mouse->returnYPos()].returnIntDistance();

				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 1){
				int cellDistance = liveMaze[mouse->returnXPos()]
				[mouse->returnYPos() - 1].returnIntDistance();
				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 2){
				int cellDistance = liveMaze[mouse->returnXPos() - 1]
				[mouse->returnYPos()].returnIntDistance();
				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 3){
				int cellDistance = liveMaze[mouse->returnXPos()]
				[mouse->returnYPos() + 1].returnIntDistance();
				if(cellDistance <= minDistance){
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
	if(priority > 0)
		mouse->setFacing(priority);
	else
		mouse->setFacing(minPosition);


}

void Maze :: analyzePositionAndOptimize(){
	int minDistance = 99;
	int minPosition = -1;
	Cell cellCheck = liveMaze[7][7];
	//Grabbing Minimum Distance
	printLiveMaze();
	for(int i = 0; i < 4; ++i){
		if(!liveMaze[mouse->returnXPos()]
				[mouse->returnYPos()].wallStatus(i)){
			
			if(i == 0){
				int cellDistance = liveMaze[mouse->returnXPos() + 1]
				[mouse->returnYPos()].returnIntDistance();
				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 1){
				int cellDistance = liveMaze[mouse->returnXPos()]
				[mouse->returnYPos() - 1].returnIntDistance();
				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 2){
				int cellDistance = liveMaze[mouse->returnXPos() - 1]
				[mouse->returnYPos()].returnIntDistance();
				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
			}
			else if(i == 3){
				int cellDistance = liveMaze[mouse->returnXPos()]
				[mouse->returnYPos() + 1].returnIntDistance();
				if(cellDistance <= minDistance){
					minDistance = cellDistance;
					minPosition = i;
				}
				
			}

			
		}

		
	}

	if(minPosition == 0){
		liveMaze[cellCheck.returnXCoor()+1
			][cellCheck.returnYCoor()].
			setDistance(minDistance + 1);
		cellCheck = liveMaze[cellCheck.returnXCoor() + 1]
				[cellCheck.returnYCoor()];
	}
	else if(minPosition == 1){
		liveMaze[cellCheck.returnXCoor()][cellCheck.returnYCoor() - 1].
			setDistance(minDistance + 1);
		cellCheck = liveMaze[cellCheck.returnXCoor()]
				[cellCheck.returnYCoor() - 1];
	}
	else if(minPosition == 2){
		liveMaze[cellCheck.returnXCoor() - 1][cellCheck.returnYCoor()].
			setDistance(minDistance + 1);
		cellCheck = liveMaze[cellCheck.returnXCoor() -1]
				[cellCheck.returnYCoor()];
	}
	else if(minPosition == 3){
		liveMaze[cellCheck.returnXCoor()][cellCheck.returnYCoor() + 1].
			setDistance(minDistance + 1);
		cellCheck = liveMaze[cellCheck.returnXCoor()]
				[cellCheck.returnYCoor()+1];
	}

	optimalRoute[optimalRouteIterator++] = cellCheck;

	cout << "X: " << optimalRoute[optimalRouteIterator-1].returnXCoor() << "Y: " << 
	optimalRoute[optimalRouteIterator-1].returnYCoor()
	<< "D: " << optimalRoute[optimalRouteIterator-1].returnDistance() << endl;
	cout << "optimalRouteIterator: " << optimalRouteIterator-1 << endl;
 
	char temp;
	cout << "Enter key:";
	cin >> temp;

	optimalRouteSize = optimalRouteIterator-1;

	if(minPosition == -1){
		cout << "DEAD" << endl;
		while(1) {}
	}

	mouse->setFacing(minPosition);
}

/*
Currenly, working with min distance and following the mouse back home to store
path
Mainly in analyzePositionAndOptimize to track array of optimzedRoute
*/








