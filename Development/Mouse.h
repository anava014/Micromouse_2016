#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
using namespace std;

class Mouse{
private:
	//Eyes
	//Motors
	//Encoders
	//Position

	int xPos;
	int yPos;
	int facing;

public:
	Mouse();
	void step();
	string mouseChar();
	void delayProgram(double secondsToDelay);

	bool searchRunComplete(){
		return (xPos == 7 && yPos == 7) ||
				(xPos == 7 && yPos == 8) ||
				(xPos == 8 && yPos == 7) ||
				(xPos == 8 && yPos == 8)  ;
	}

	bool homeRunComplete(){
		return (xPos == 0 && yPos == 15);
	}

	int returnXPos(){
		return xPos;
	}

	int returnYPos(){
		return yPos;
	}

	int returnFacing(){
		return facing;
	}

	int returnReverseFacing(){
		if(facing == 0)
			return 2;
		else if(facing == 2)
			return 0;
		else if(facing == 1)
			return 3;
		else if(facing == 3)
			return 1;

		else return -1;
	}

	void transitionUTurn(){
		if(facing == 0)
			facing = 2;
		else if(facing == 2)
			facing = 0;
		else if(facing == 1)
			facing = 3;
		else if(facing == 3)
			facing = 1;
	}

	void transitionRightTurn(){
		facing = returnIncrementedFacing();
	}

	void transitionLeftTurn(){
		facing = returnDecrementedFacing();
	}

	int returnDecrementedFacing(){
		if(facing == 0)
			return 3;
		else
			return facing - 1;
	}

	int returnIncrementedFacing(){
		if(facing == 3)
			return 0;
		else
			return facing + 1;
	}

	void setFacing(int f){
		facing = f;
	}


};

#endif
