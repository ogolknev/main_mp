
#ifndef CONTAINERS_H_
#define CONTAINERS_H_
#include <stdio.h>
#include <stdlib.h>

//structure for storing list item data
struct input_data{
    char operation;
    char mode;
    int size;
    float *data;
};

//definition of new type - Container
typedef struct Element{
	struct input_data data;
    struct Element *next, *previous, *head, *tail;
}Container;


Container *newContainer();

//checking if the container is empty
int isEmpty(Container **headcontainer);

//counting container elements
int elementCount(Container **headcontainer);

//stack

//function to add a new element to the stack
void addToStack(Container **headstack, struct input_data data);

//function to pop an element from the stack
struct input_data getStack(Container **headstack);


//queue

//function to add a new element to the queue
void addToQueue(Container **headqueue, struct input_data data);

//function to pop an element from the queue
struct input_data getQueue(Container **headqueue);


//list

//function to add a new element to the beginning of the list
void addFirst(Container **headlist, struct input_data data);

//function to add a new element to the end of the list
void addLast(Container **headlist, struct input_data data);

//function to add a new element after the specified number
void addToList(Container **headlist, struct input_data data, int number);

//function to remove a new element to the beginning of the list
void delFirst(Container **headlist);

//function to remove a new element to the end of the list
void delLast(Container **headlist);

//function to remove the specified element
void delElement(Container **headlist, int number);

//function to get the address of the specified element
Container *getList(Container **headlist, int number);

#endif /* CONTAINERS_H_ */
