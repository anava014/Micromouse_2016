#include "Mouse.h"

Mouse :: Mouse(){
	xPos = 0;
	yPos = 15;
	facing = 0; //North
}

char Mouse :: mouseChar(){
	if(facing == 0)
		return '^';
	else if(facing == 1)
		return '_';
	else if(facing == 2)
		return '>';
	else if(facing == 3)
		return '<';
}

void Mouse :: step(){
	// char temp;
	// cout << "Enter key:";
	// cin >> temp;

	delayProgram(.3);
	if(facing == 0){
		++xPos;
	}
	else if(facing == 1){
		--xPos;
	}
	else if(facing == 2){
		--yPos;
	}
	else if(facing == 3){
		++yPos;
	}
}

void Mouse :: delayProgram(double secondsToDelay)
{
	double startTime = double(clock()); //Start timer
	double secondsPassed;
	bool flag = true;
	while(flag)
	{
		secondsPassed = (double(clock() - startTime)) / double(CLOCKS_PER_SEC);;
		if(secondsPassed >= secondsToDelay)
		{
			flag = false;
		}
	}
}




