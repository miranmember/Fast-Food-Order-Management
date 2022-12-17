# Fast-Food-Order-Management
A program for managing fast food orders. It allows users to add orders to a customer data structure list and provides functions for modifying and accessing the list.


## Compiling the program
To compile the program, navigate to the directory containing the source code and run the following command:
```
gcc queue.c list.c Program1.c program
```
This will create an executable file called **program**.


#Running the program
To run the program, enter the following command:
```
./program
```

## Available functions

+ newNode(char status, int burgers, int salads, char * name): Creates a new linked list node.
+ createQueue(): Creates an empty queue.
+ nameIndex(struct QUEUE * q, char * name): Returns the index of a given name in the queue.
+ orderIndex(struct QUEUE * q, int burgers, int salads): Returns the index of an order with the specified number of burgers and salads.
+ addToList(struct QUEUE* q, char status, int burgers, int salads, char * name, int debug): Adds a new order to the queue.
+ deQueue(struct QUEUE* q): Removes the first element from the queue.
+ resetQueue(struct QUEUE * q): Removes all elements from the queue.
+ deleteQueue(struct QUEUE * q): Deletes the queue and frees all memory associated with it.
+ doesNameExist(struct QUEUE * q, char * name): Returns whether a given name exists in the queue.
+ inRestaurant: Returns true if the node with the given name
