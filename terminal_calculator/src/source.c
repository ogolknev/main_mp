/*
__________________________________________________________________________________________________________________
 Name        : Terminal Calculator
 Author      : Ogolknev Nikita
 Version     : 3.1
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
#include "containers.h"

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
        //definition new container
        Container *input_data = newContainer();
        //reading an input file and saving the data to a queue
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
            }
            //adding new element to end of queue
            addToQueue(&input_data, element);
        }
        //closing file
        fclose(input);
        //definition new queue
        struct input_data input_pointer, output_pointer;
        //definition structure for storing queue item data
        struct input_data output_element;
        //allocation memory
        input_pointer.data = malloc(input_data->data.size*sizeof(double));
        output_pointer.data = malloc(input_data->data.size*sizeof(double));
        output_element.data = malloc(input_data->data.size*sizeof(double));
        //definition new queue
        Container *output_list = newContainer();
        Container *output_queue_op = newContainer();
        //input
        while(isEmpty(&input_data) != 0) {
        	//getting an element from the queue
            input_pointer = getQueue(&input_data);
            //adding new element to end of queue
            addToQueue(&output_queue_op,input_pointer);
            //allocation memory
            output_element.data = malloc(input_data->data.size*sizeof(double));
            //vector mode
            if(input_pointer.mode == 'v')
            {
                switch (input_pointer.operation)
                {
                    //calculating and output of result one of operations
                    case '+':
                        for(int i=0; i < input_pointer.size; i++)
                        {
                            output_element.data[i] = input_pointer.data[i] + input_pointer.data[input_pointer.size+i];
                        }
                        break;
                        //calculating and output of result one of operations
                    case '-':
                        for(int i=0; i < input_pointer.size; i++)
                        {
                            output_element.data[i] = input_pointer.data[i] - input_pointer.data[input_pointer.size+i];
                        }
                        break;
                        //calculating and output of result one of operations
                    case '*':
                        for(int i=0; i < input_pointer.size; i++)
                        {
                            output_element.data[i] = input_pointer.data[i] * input_pointer.data[input_pointer.size+i];
                        }
                        break;
                        //calculating and output of result one of operations
                    case '/':
                        for(int i=0; i < input_pointer.size; i++)
                        {
                            output_element.data[i] = input_pointer.data[i] / input_pointer.data[input_pointer.size+i];
                        }
                        break;
                        //calculating and output of result one of operations
                    case '\'':
                        for(int i=0; i < input_pointer.size; i++)
                        {
                            output_element.data[0] += input_pointer.data[i] * input_pointer.data[input_pointer.size+i];
                        }
                        break;
                        //calculating and output of result one of operations
                    case 'x':
                        if (input_pointer.size == 3)
                        {
                            output_element.data[0] = input_pointer.data[1] * input_pointer.data[5] - input_pointer.data[4] * input_pointer.data[2];
                            output_element.data[1] = -(input_pointer.data[0] * input_pointer.data[5] - input_pointer.data[2] * input_pointer.data[3]);
                            output_element.data[2] = input_pointer.data[0] * input_pointer.data[4] - input_pointer.data[1] * input_pointer.data[3];
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
            else if(input_pointer.mode == 's')
            {
                /*
                variables description:
                deg - variable for calculation factorial degree
                factorial - variable for calculation factorial
                 */
                int deg;
                int factorial;
                //checking for operations using 1 number
                if (input_pointer.operation == '!' || input_pointer.operation == '^')
                {
                    //operation selection
                    switch (input_pointer.operation)
                    {
                        //factorial calculation block
                        case '!':
                            factorial = 1;
                            //factorial negative number
                            if(input_pointer.data[0] < 0)
                            {
                                //error warning
                                output_element.operation = 'e';
                            }
                                //factorial 0
                            else if(input_pointer.data[0] == 0)
                            {
                                output_element.data[0] = 1;
                            }
                                //main factorial
                            else
                            {
                                for(int i=1; i <= input_pointer.data[0]; i++)
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
                            if(input_pointer.data[1] == 0)
                            {
                                output_element.data[0] = 1;
                            }
                                //negative degree indicator
                            else if (input_pointer.data[1] < 0)
                            {
                                for(int i=1;i <= input_pointer.data[1];i++)
                                {
                                    deg = deg / input_pointer.data[0];
                                }
                                output_element.data[0] = deg;
                            }
                                //main degree calculation
                            else
                            {
                                for(int i=1;i<=input_pointer.data[1];i++)
                                {
                                    deg = deg * input_pointer.data[0];
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
                    switch (input_pointer.operation)
                    {
                        //sum calculation
                        case '+':
                            output_element.data[0] = input_pointer.data[0]+input_pointer.data[1];
                            break;
                            //subtraction calculation
                        case '-':
                            output_element.data[0] = input_pointer.data[0]-input_pointer.data[1];
                            break;
                            //multiplication calculation
                        case '*':
                            output_element.data[0] = input_pointer.data[0]*input_pointer.data[1];
                            break;
                            //division calculation
                        case '/':
                            output_element.data[0] = input_pointer.data[0]/input_pointer.data[1];
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
            //adding new element to end of queue
            addToQueue(&output_list,output_element);
        }
        //entering path to output file
        path = calloc(100, sizeof(char));
        printf("enter the path to the file where the output will be placed:\n");
        scanf(" %100s", path);
        //opening output file
        output = fopen(path, "w");
        free(path);
        //output
        while(isEmpty(&output_list) != 0){
        	//getting an element from the queue
            input_pointer = getQueue(&output_queue_op);
            output_pointer = getQueue(&output_list);
            //error warning
            if(output_pointer.operation == 'e'){
                fprintf(output, "error\n");
            }
            //output vector mode
            else if(input_pointer.mode == 'v'){
                fprintf(output, "( ");
                for(int i = 0; i < input_pointer.size; i++){
                    fprintf(output, "%f ", input_pointer.data[i]);
                }
                fprintf(output, ")");
                fprintf(output, " %c ", input_pointer.operation);
                fprintf(output, "( ");
                for(int i = 0; i < input_pointer.size; i++){
                    fprintf(output, "%f ", input_pointer.data[input_pointer.size + i]);
                }
                fprintf(output, ") = ");
                if(input_pointer.operation == '\''){
                    fprintf(output,"%f\n", output_pointer.data[0]);
                } else {
                    fprintf(output, "( ");
                    for(int i = 0; i < input_pointer.size; i++){
                        fprintf(output, "%f ", output_pointer.data[i]);
                    }
                    fprintf(output, ")\n");
                }
            //output number mode
            } else if (input_pointer.mode == 's'){
                if(input_pointer.operation == '!'){
                    fprintf(output, "%f! = %f\n", input_pointer.data[0], output_pointer.data[0]);
                } else {
                    fprintf(output, "%f %c %f = %f\n", input_pointer.data[0],input_pointer.operation, input_pointer.data[1], output_pointer.data[0]);
                }
            }
        }
        //closing output file
        fclose(output);
        free(input_data);
        free(output_list);
        //prompt to repeat the program and select new files
        printf("select new files and start over?\n'y' - yes\nother - no\n");
        scanf(" %c", &repeat);
    }
    while(repeat == 'y');
    return 0;
}
//the end ^-^
