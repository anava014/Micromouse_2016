#include "Mouse.h"

Mouse :: Mouse(){
	xPos = 0;
	yPos = 15;
	facing = 0; //North
}

string Mouse :: mouseChar(){
	if(facing == 0)
		return "\033[1;32m^\033[0m";
	else if(facing == 1)
		return "\033[1;32m>\033[0m";
	else if(facing == 2)
		return "\033[1;32mV\033[0m";
	else if(facing == 3)
		return "\033[1;32m<\033[0m";
	else
		return "x";
}

void Mouse :: step(){
	// char temp;
	// cout << "Enter key:";
	// cin >> temp;

	delayProgram(.05);
	if(facing == 0){
		++xPos;
	}
	else if(facing == 1){
		--yPos;
	}
	else if(facing == 2){
		--xPos;
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




