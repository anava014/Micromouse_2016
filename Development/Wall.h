#ifndef WALL_H
#define WALL_H

class Wall{
private:
	bool isPresent;

public:
	Wall(bool iP);
	Wall();

	void markPresent();
	void markNotPresent();
	bool returnIsPresent();
};

#endif
