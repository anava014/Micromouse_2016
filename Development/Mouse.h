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
	char mouseChar();
	void delayProgram(double secondsToDelay);

	int returnXPos(){
		return xPos;
	}

	int returnYPos(){
		return yPos;
	}

	int returnFacing(){
		return facing;
	}

	void setFacing(int f){
		facing = f;
	}


};

#endif
