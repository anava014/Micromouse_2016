#Variables
COMPILE = g++
FLAGS = -g -Wall -ansi -pedantic
OBJS = Maze.o Cell.o Wall.o Mouse.o
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
	
clean:
	rm -rf *~ *.o a.out*
	
run:
	clear
	clear
	make all
	