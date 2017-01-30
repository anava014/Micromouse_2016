# Floodfill - Micromouse Algorithm
Andrew Nava-Juarez
anava806@icloud.com

I encourage you to read this readme before reviewing the code.

This is a micromouse floodfill simulator. It's intended purpose is to guide you in implementing your own floodfill solution for
your robotic mouse. If you solely copy and paste, your loss. 
Read the Psuedo Code below and use Google and Youtube for learning more in depth of what exactly is going on behind the scenes.
One video that helped me a ton from Green Ye: https://www.youtube.com/watch?v=he3y_U7M8ng
Goodluck!

Note: this is not the best solution for there are areas in the solution to consider such as straightaways are more efficient than 
making turns to reach the destination and for advanced techniques such as diagonal runs.

to compile: make

to run: ./a.out

Uncomment lines 23 - 25 of Mouse.cpp to enable step by step monitoring of algorithm solution. 
Line 27 of Mouse.cpp manages the delay when running at full speed in seconds.

Unsolved
![alt tag](http://i.imgur.com/S0WekoH.png)
Solved
![alt tag](http://i.imgur.com/Kv8Yob1.png)


# Psuedo Code

* Floodfill Algorithm
Immediately after advancing and preferably once in the center of the cell,
Check east, north, and west for new walls

For each check, if a new wall is found, set the wall in liveMaze,
push the currentCell and all of its adjacent cells to the stack.

While the stack is not empty:
	Pop the cell at the top of the stack. (currentCell)
	Iterate through all open wall's cells and store the minimum distance out of all.

	The distance of currentCell should be the minimum open neighbor + 1.
	If not, set that value and push all open neighbors to stack
  
* Analyze live mouse position
From floodfill, we have the information needed for cells.
This function uses that information to tell which direction to turn.

Using the current cell that the mouse is in,
for every open wall:
	find the cell with the minimum distance and store the position

If minPosition == -1, this means that the mouse has trapped itself between walls,
is confused and scared, and has now lost track of it's maze in memory.
I would recommend resorting to a random algorithm from here.

Using the current direction your mouse is facing, and comparing
with the minimum position of which path to traverse, face the mouse appropriately.

set facing position to new position.

