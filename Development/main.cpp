#include <iostream>
#include "Maze.h"
//#include "CellArray.h"
#include "CellLink.h"
#include "CellNode.h"

using namespace std;

int main(){
	//Menu
	Mouse *mighty = new Mouse();
	Maze mm(mighty);
	//mm.printMaze();
	mm.start();
	// Cell cellCheck = Cell(true, true, true, true);

	// CellLink *root;
	// CellLink *conductor;
	// CellNode *rootNode = new CellNode(cellCheck);
	// CellNode *rootConductor;

	// //Created Cell Node
	// //Pushing rootNode toCellLink
	// root = new CellLink(rootNode);
	// root->next = 0;   //  Otherwise it would not work well
	// root->data = cellCheck;
	// conductor = root;

	// //createNodein ptr One
	// root.node = new CellNode(cellCheck);
    	
	// conductor->next = new CellNode();  // Creates a node at the end of the list
	// conductor = conductor->next; // Points to that node
	// conductor->next = 0;         // Prevents it from going any further
	// conductor->data = cellCheck;
	
	return 0;
}


// struct node {
//   int x;
//   node *next;
// };

// int main()
// {
//   node *root;       // This won't change, or we would lose the list in memory
//   node *conductor;  // This will point to each node as it traverses the list

//   root = new node;  // Sets it to actually point to something
//   root->next = 0;   //  Otherwise it would not work well
//   root->x = 12;
  
//   conductor = root;
//   conductor->next = new node;  // Creates a node at the end of the list
//   conductor = conductor->next; // Points to that node
//   conductor->next = 0;         // Prevents it from going any further
//   conductor->x = 42;

//   conductor = root; // The conductor points to the first node
//   if ( conductor != 0 ) {
//     while ( conductor != 0){
//       cout << conductor->x << endl;
//       conductor = conductor->next;
//     }
//   }
// }






