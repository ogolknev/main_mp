/*
__________________________________________________________________________________________________________________

 Name        : Terminal Calculator
 Author      : Ogolknev Nikita
 Version     : 4.0
 Description : this program is for calculating four arithmetic operations between multiple numbers
 Instruction : the program works with files, and for its work you need a file with ready-made input data.
 		       this file must contain a calculated expression written in reverse Polish notation (2 2 2 + *).
 		       the output file will contain all the steps needed to evaluate this expression
 		       and the answer (1. 2 + 2 = 4; 2. 4 * 2 = 8; answer: 8).
__________________________________________________________________________________________________________________

 */

#include <stdio.h>
#include <stdlib.h>

//definition of element of container structure
typedef struct element_data{
	float data;
	struct element_data *head, *previos;
}Container;

//emptiness check function
int isEmpty(Container **head_container){
    Container *pointer = *head_container;
	if(pointer->head == NULL){
		return 1;
	}
		return 0;
}

//element counter function
int elementCount(Container **head_container){
    Container *pointer = *head_container;
	int count = 0;
	if(isEmpty(&pointer) != 1)
	{
		count++;
		while(pointer->previos != NULL){
			count++;
            pointer = pointer->previos;
		}
	}
	return count;
}

//definition of new container and 1 empty element
Container* newContainer(){
	Container* new_container = malloc(sizeof(Container));
	new_container->head = NULL;
	new_container->previos = NULL;
	return new_container;
}

//adding element to stack
void addToStack(Container **head_container, float data){
    Container *pointer = *head_container;
	if(isEmpty(&pointer) == 1){
        pointer->data = data;
        pointer->head = pointer;
	}
	else
	{
		Container* new_element = newContainer();
		new_element->data = data;
		new_element->previos = pointer;
		new_element->head = new_element;
        pointer->head = new_element;
		while(pointer->previos != NULL){
            pointer = pointer->previos;
            pointer->head = new_element;
		}
        *head_container = pointer->head;
	}
}

//getting element from stack
float getStack(Container **head_container){
    Container *pointer = *head_container;
    float get_data = pointer->data;
    if(elementCount(&pointer) > 1)
    {
        pointer = pointer->previos;
        *head_container = pointer;
        free(pointer->head);
        pointer->head = pointer;
        while (pointer->previos != NULL) {
            pointer->previos->head = pointer->head;
            pointer = pointer->previos;
        }
    }
    else
    {
        pointer->head = NULL;
    }
    return get_data;
}

//main function
int main(int argc, char* argv[])
{
	//console fix
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    //variable declaration
	float data;
	char operation, extra;
	float num1, num2;
	int counter = 0;
	//creating new empty container
	Container* data_store = newContainer();
	//streams variables declaration
	FILE *input1, *input2, *output;
	//allocating memory
	char *path = malloc(20*sizeof(char));
	char *path_output = malloc(20*sizeof(char));
	//entering path to input file
	printf("enter input file:\n");
	scanf("%s", path);
	//opening file for reading floats
	input1 = fopen(path, "r");
	//opening file foe reading symbols
	input2 = fopen(path, "r");
	//entering path to output file
	printf("enter output file:\n");
	scanf("%s", path_output);
	output = fopen(path_output, "w");
	//calculating and printing to file cycle
	while(feof(input1) == 0 && feof(input2) == 0){
		//variables definition
		operation = 0;
		data = 0;
		//reading numbers
		fscanf(input1, "%f", &data);
		//fix reading symbols as float
		if(data == 0){
			fscanf(input1, "%c", &extra);
		}
		//reading operations
		fscanf(input2, " %c", &operation);
		//calculating and printing to file
		if(operation == '+')
		{
			counter++;
			num2 = getStack(&data_store);
			num1 = getStack(&data_store);
			addToStack(&data_store, num1 + num2);
			fprintf(output, "%i. %f + %f = %f;\n", counter, num1, num2, num1 + num2);
		}
		else if(operation == '-')
		{
			counter++;
			num2 = getStack(&data_store);
			num1 = getStack(&data_store);
			addToStack(&data_store, num1 - num2);
			fprintf(output, "%i. %f - %f = %f;\n", counter, num1, num2, num1 - num2);
		}
		else if(operation == '*')
		{
			counter++;
			num2 = getStack(&data_store);
			num1 = getStack(&data_store);
			addToStack(&data_store, num1 * num2);
			fprintf(output, "%i. %f * %f = %f;\n", counter, num1, num2, num1 * num2);
		}
		else if(operation == '/')
		{
			counter++;
			num2 = getStack(&data_store);
			num1 = getStack(&data_store);
			addToStack(&data_store, num1 / num2);
			fprintf(output, "%i. %f / %f = %f;\n", counter, num1, num2, num1 / num2);
		}
		//adding to stack
		else{
			addToStack(&data_store, data);
		}
		//fix reading each character of a number separately
		while((operation != ' ') && (feof(input2) == 0)){
			fscanf(input2, "%c", &operation);
		}
	}
	//printing of answer
	fprintf(output, "answer: %f", getStack(&data_store));
	return 0;
}
//the end ^-^
