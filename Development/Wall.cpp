#include "Wall.h"

Wall :: Wall(bool iP){
	isPresent = iP;
}

Wall :: Wall(){
	isPresent = false;
}

void Wall :: markPresent(){
	isPresent = true;
}

void Wall :: markNotPresent(){
	isPresent = false;
}
