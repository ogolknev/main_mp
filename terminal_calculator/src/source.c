/*
__________________________________________________________________________________________________________________

 Name        : Terminal Calculator
 Author      : Ogolknev Nikita
 Version     : 2.2
 Description : this program is for calculating six arithmetic operations between two numbers
 Instruction : the program works with files, and for its work you need a file with ready-made input data.
 		       in this file, in the line, the first character is an operation, then a space indicates
		       the use of individual numbers (s) or vectors (v) (for vectors, an indication of their dimensions)
		       and then the required amount of data, each of the numbers is also separated by a space.
		       there can be several lines in the file with the input data separated by a space or a newline.
		       the output file will contain the original expression, the equal sign and the result.
               parentheses are used to designate vectors in the output file.

               more details in the README
__________________________________________________________________________________________________________________

 */

#include <stdio.h>
#include <stdlib.h>

//definition of functions for working with lists

//structure for storing list item data
struct input_data{
    char operation;
    char mode;
    int size;
    float *data;
};

//definition of new type - list
typedef struct type_list{
    struct input_data data;
    struct type_list *next;
}list;

//creating new list
list *newlist(struct input_data input_data){
    list *newlist = malloc(sizeof(list));
    newlist->data = input_data;
    newlist->next = NULL;
    return newlist;
}

//adding to beginning of list
void addfirst(list **headlist, struct input_data input_data){
    list *addfirst = newlist(input_data);
    addfirst->next = *headlist;
    *headlist = addfirst;
}

//adding to end of list
void addlast(list **headlist, struct input_data input_data){
    list *addlast = newlist(input_data);
    list *currentlist = *headlist;
    while(currentlist->next != NULL){
        currentlist = currentlist->next;
    }
    currentlist->next = addlast;
}

//adding after a definite element
void add(list **headlist, struct input_data input_data, int serialnum){
    list *addlist = newlist(input_data);
    list *currentlist = *headlist;
    int current_serialnum = 0;
    while(currentlist->next != NULL){
        if(current_serialnum == serialnum){
            addlist->next = currentlist->next;
            currentlist->next = addlist;
        }
        current_serialnum++;
        currentlist = currentlist->next;
    }
}


//main function
int main(int argc, char *argv[]){
	//fix console output and input
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    //repeat - variable for repeating the program
    char repeat = 'n';
    //loop to repeat the program and select new input and output files
    do{
		/*
		variable description:
		input - variable for opening input file
		output - variable for opening output file
		path - variable to store path
		*/
		FILE *input, *output;
		char *path;
		//allocation memory
		path = calloc(100, sizeof(char));
		//entering path to input file
		printf("enter the path to the file with input data:\n");
		scanf(" %100s", path);
		//opening input file
		input = fopen(path, "r");
		//freeing memory
		free(path);
		//definition structure for storing list item data
		struct input_data element;
		//definition new list
		list *input_data = newlist(element);
		//reading an input file and saving the data to a list
		while(feof(input) == 0){
			fscanf(input, " %c", &element.operation);
			fscanf(input, " %c", &element.mode);
			if (element.mode == 'v'){
				fscanf(input, "%i", &element.size);
				element.data = malloc(element.size*sizeof(double));
				for(int i=0; i < element.size*2; i++)
				{
					fscanf(input, "%f", &element.data[i]);
				}
				addlast(&input_data, element);
			} else if(element.mode == 's') {
				if(element.operation == '!'){
					element.data = malloc(sizeof(double));
					fscanf(input, "%f", &element.data[0]);
				}
				else {
					element.data = malloc(2 * sizeof(double));
					fscanf(input, "%f", &element.data[0]);
					fscanf(input, "%f", &element.data[1]);
				}
				//adding new element to end of list
				addlast(&input_data, element);
			}
		}
		//closing file
		fclose(input);
		//definition new list
		list *pointer = input_data;
		//definition structure for storing list item data
		struct input_data output_element;
		//allocation memory
		output_element.data = malloc(input_data->data.size*sizeof(double));
		//definition new list
		list *output_list = newlist(output_element);
		//input
		while(pointer->next != NULL) {
			//move to next element of list
			pointer = pointer->next;
			//allocation memory
			output_element.data = malloc(input_data->data.size*sizeof(double));
			//vector mode
			if(pointer->data.mode == 'v')
			{
				switch (pointer->data.operation)
				{
					//calculating and output of result one of operations
					case '+':
						for(int i=0; i < pointer->data.size; i++)
						{
							output_element.data[i] = pointer->data.data[i] + pointer->data.data[pointer->data.size+i];
						}
						break;
					//calculating and output of result one of operations
					case '-':
						for(int i=0; i < pointer->data.size; i++)
						{
							output_element.data[i] = pointer->data.data[i] - pointer->data.data[pointer->data.size+i];
						}
						break;
					//calculating and output of result one of operations
					case '*':
						for(int i=0; i < pointer->data.size; i++)
						{
							output_element.data[i] = pointer->data.data[i] * pointer->data.data[pointer->data.size+i];
						}
						break;
					//calculating and output of result one of operations
					case '/':
						for(int i=0; i < pointer->data.size; i++)
						{
							output_element.data[i] = pointer->data.data[i] / pointer->data.data[pointer->data.size+i];
						}
						break;
					//calculating and output of result one of operations
					case '\'':
						for(int i=0; i < pointer->data.size; i++)
						{
							output_element.data[0] += pointer->data.data[i] * pointer->data.data[pointer->data.size+i];
						}
						break;
					//calculating and output of result one of operations
					case 'x':
						if (pointer->data.size == 3)
						{
							output_element.data[0] = pointer->data.data[1] * pointer->data.data[5] - pointer->data.data[4] * pointer->data.data[2];
							output_element.data[1] = -(pointer->data.data[0] * pointer->data.data[5] - pointer->data.data[2] * pointer->data.data[3]);
							output_element.data[2] = pointer->data.data[0] * pointer->data.data[4] - pointer->data.data[1] * pointer->data.data[3];
						}
						//error warning
						else
						{
							output_element.operation = 'e';
						}
						break;
						//error warning
					default:
						output_element.operation = 'e';
						break;
				}
			}
			//number mode
			else if(pointer->data.mode == 's')
			{
				/*
				variables description:
				deg - variable for calculation factorial degree
				factorial - variable for calculation factorial
				 */
				int deg;
				int factorial;
				//checking for operations using 1 number
				if (pointer->data.operation == '!' || pointer->data.operation == '^')
				{
					//operation selection
					switch (pointer->data.operation)
					{
						//factorial calculation block
						case '!':
							factorial = 1;
							//factorial negative number
							if(pointer->data.data[0] < 0)
							{
								//error warning
								output_element.operation = 'e';
							}
							//factorial 0
							else if(pointer->data.data[0] == 0)
							{
								output_element.data[0] = 1;
							}
							//main factorial
							else
							{
								for(int i=1; i <= pointer->data.data[0]; i++)
								{
									factorial=factorial*i;
								}
								//output
								output_element.data[0] = factorial;
							}
							break;
						//degree calculation and output
						case '^':
							deg = 1;
							//degree indicator 0
							if(pointer->data.data[1] == 0)
							{
								output_element.data[0] = 1;
							}
							//negative degree indicator
							else if (pointer->data.data[1] < 0)
							{
								for(int i=1;i <= pointer->data.data[1];i++)
								{
									deg = deg / pointer->data.data[0];
								}
								output_element.data[0] = deg;
							}
							//main degree calculation
							else
							{
								for(int i=1;i<=pointer->data.data[1];i++)
								{
									deg = deg * pointer->data.data[0];
								}
								output_element.data[0] = deg;
							}
							break;
						default:
							//error warning
							output_element.operation = 'e';
							break;
					}
				}
				else
				{
					//operation selection
					switch (pointer->data.operation)
					{
						//sum calculation
						case '+':
							output_element.data[0] = pointer->data.data[0]+pointer->data.data[1];
							break;
						//subtraction calculation
						case '-':
							output_element.data[0] = pointer->data.data[0]-pointer->data.data[1];
							break;
						//multiplication calculation
						case '*':
							output_element.data[0] = pointer->data.data[0]*pointer->data.data[1];
							break;
						//division calculation
						case '/':
							output_element.data[0] = pointer->data.data[0]/pointer->data.data[1];
							break;
						default:
							//error warning
							output_element.operation = 'e';
							break;
					}
				}
			}
			//error warning
			else
			{
				output_element.operation = 'e';
			}
			//adding new element to end of list
			addlast(&output_list,output_element);
		}
		//entering path to output file
		path = calloc(100, sizeof(char));
		printf("enter the path to the file where the output will be placed:\n");
		scanf(" %100s", path);
		//opening output file
		output = fopen(path, "w");
		free(path);
		//moving pointer to start
		pointer = input_data;
		//output
		while(pointer->next != NULL){
			//move to next element of list
			pointer = pointer->next;
			//move to next element of list
			output_list = output_list->next;
			//error warning
			if(output_list->data.operation == 'e'){
				fprintf(output, "error\n");
			}
			//output vector mode
			else if(pointer->data.mode == 'v'){
				fprintf(output, "( ");
				for(int i = 0; i < pointer->data.size; i++){
					fprintf(output, "%f ", pointer->data.data[i]);
				}
				fprintf(output, ")");
				fprintf(output, " %c ", pointer->data.operation);
				fprintf(output, "( ");
				for(int i = 0; i < pointer->data.size; i++){
					fprintf(output, "%f ", pointer->data.data[pointer->data.size + i]);
				}
				fprintf(output, ") = ");
				if(pointer->data.operation == '\''){
					fprintf(output,"%f\n", output_list->data.data[0]);
				} else {
					fprintf(output, "( ");
					for(int i = 0; i < pointer->data.size; i++){
						fprintf(output, "%f ", output_list->data.data[i]);
					}
					fprintf(output, ")\n");
				}
			//output number mode
			} else if (pointer->data.mode == 's'){
				if(pointer->data.operation == '!'){
					fprintf(output, "%f! = %f\n", pointer->data.data[0], output_list->data.data[0]);
				} else {
					fprintf(output, "%f %c %f = %f\n", pointer->data.data[0],pointer->data.operation, pointer->data.data[1], output_list->data.data[0]);
				}
			}
		}
		//closing output file
		fclose(output);
		free(input_data);
		free(pointer);
		free(output_list);
		//prompt to repeat the program and select new files
		printf("select new files and start over?\n'y' - yes\nother - no\n");
		scanf(" %c", &repeat);
    }
    while(repeat == 'y');
    return 0;
}
//the end :)
