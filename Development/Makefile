#Variables
COMPILE = g++
FLAGS = -g -Wall -ansi -pedantic
OBJS = Maze.o Cell.o Wall.o Mouse.o CellStack.o CellNode.o CellLink.o
# -W -Wall -Werror -ansi -pedantic
#Targets

all: main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -o a.out main.cpp $(OBJS)

Wall.o: Wall.cpp Wall.h
	$(COMPILE) $(FLAGS) -c Wall.cpp	

Cell.o: Cell.cpp Cell.h
	$(COMPILE) $(FLAGS) -c Cell.cpp	
	
Maze.o: Maze.cpp Maze.h
	$(COMPILE) $(FLAGS) -c Maze.cpp	

Mouse.o: Mouse.cpp Mouse.h
	$(COMPILE) $(FLAGS) -c Mouse.cpp

CellNode.o: CellNode.cpp CellNode.h
	$(COMPILE) $(FLAGS) -c CellNode.cpp

CellLink.o: CellLink.cpp CellLink.h
	$(COMPILE) $(FLAGS) -c CellLink.cpp

CellStack.o: CellStack.cpp CellStack.h
	$(COMPILE) $(FLAGS) -c CellStack.cpp
	
clean:
	rm -rf *~ *.o a.out*
	
run:
	clear
	clear
	make all
	
