/*
	 __________________________________________________________________________________________________________________
	/																												   \
    |  Name        : Terminal Calculator																			   |
	|  Author      : Ogolknev Nikita																				   |
	|  Version     : 2.2																							   |
	|  Description : this program is for calculating six arithmetic operations between two numbers					   |
	|  Instruction : the program works with files, and for its work you need a file with ready-made input data.		   |
	|	 		     in this file, in the line, the first character is an operation, then a space indicates			   |
	|			     the use of individual numbers (s) or vectors (v) (for vectors, an indication of their dimensions) |
	|			     and then the required amount of data, each of the numbers is also separated by a space.		   |
	|			     there can be several lines in the file with the input data separated by a space or a newline.	   |
	|			     the output file will contain the original expression, the equal sign and the result.			   |
	|			     parentheses are used to designate vectors in the output file.                                     |
	|          																									       |
	|                more details in the README                                                                        |
	\__________________________________________________________________________________________________________________/

 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	//repeat - variable for repeating the program
	char repeat = 'n';
	//loop to repeat the program and select new input and output files
	do
	{
		/*
		variable description:
		input - variable for working with file input.txt
		output - variable for working with file output.txt
		select - variable for selecting operating mode
		operation - variable for selecting operation
		path - variable to store path
		*/
		FILE *input, *output;
		char *path, select, operation;
		//allocation memory and opening input and output files
		path = calloc(100, sizeof(char));
		printf("enter the path to the file with input data:\n");
		scanf(" %100s", path);
		input = fopen(path, "r");
		printf("enter the path to the file where the output will be placed:\n");
		scanf(" %100s", path);
		output = fopen(path, "w");
		//loop processing input file to end
		while(feof(input) == 0)
		{
			//selecting operation
			fscanf(input, " %c", &operation);
			//selecting operating mode
			fscanf(input, " %c", &select);
			//vector mode
			if(select == 'v')
			{
			/*
			variable description:
			vector_1 - variable to store the coordinates of the first vector
			vector_2 - variable to store the coordinates of the second vector
			result - variable to store resulting vector
			res  - variable to store result of some operations
			size - variable for selecting size of vectors used
			*/
			float *vector_1, *vector_2, *result, res = 0;
			int size;
			fscanf(input, "%i", &size);
			//memory allocation
			vector_1 = malloc(size*sizeof(float));
			vector_2 = malloc(size*sizeof(float));
			result = malloc(size*sizeof(float));
			fprintf(output,"(");
			//entering vectors and output of original expression
			for(int i=0; i < size; i++)
			{
				fscanf(input, "%f", &vector_1[i]);
				fprintf(output, " %f", vector_1[i]);
			}
			fprintf(output," ) ");
			fprintf(output,"%c", operation);
			fprintf(output," (");
			for(int i=0; i < size; i++)
			{
				fscanf(input, "%f", &vector_2[i]);
				fprintf(output, " %f", vector_2[i]);
			}
			fprintf(output," ) = ");
			//calculation block
			switch (operation)
			{
				//calculating and output of result one of operations
				case '+':
					fprintf(output, "( ");
					for(int i=0; i < size; i++)
					{
						result[i] = vector_1[i] + vector_2[i];
						fprintf(output, "%f ", result[i]);
					}
					fprintf(output, ")\n");
					break;
				//calculating and output of result one of operations
				case '-':
					fprintf(output, "( ");
					for(int i=0; i < size; i++)
					{
						result[i] = vector_1[i] - vector_2[i];
						fprintf(output, "%f ", result[i]);
					}
					fprintf(output, ")\n");
					break;
				//calculating and output of result one of operations
				case '*':
					fprintf(output, "( ");
					for(int i=0; i < size; i++)
					{
						result[i] = vector_1[i] * vector_2[i];
						fprintf(output, "%f ", result[i]);
					}
					fprintf(output, ")\n");
					break;
				//calculating and output of result one of operations
				case '/':
					fprintf(output, "( ");
					for(int i=0; i < size; i++)
					{
						result[i] = vector_1[i] / vector_2[i];
						fprintf(output, "%f ", result[i]);
					}
					fprintf(output, ")\n");
					break;
				//calculating and output of result one of operations
				case '\'':
					for(int i=0; i < size; i++)
					{
						res += vector_1[i] * vector_2[i];
					}
					fprintf(output, "%f\n", res);
					break;
				//calculating and output of result one of operations
				case 'x':
					if (size == 3)
					{
						fprintf(output, "( ");
						fprintf(output, "%f ", (vector_1[1] * vector_2[2] - vector_1[2] * vector_2[1]));
						fprintf(output, "%f ", -(vector_1[0] * vector_2[2] - vector_1[2] * vector_2[0]));
						fprintf(output, "%f ", (vector_1[0] * vector_2[1] - vector_1[1] * vector_2[0]));
						fprintf(output, ")\n");
					}
					//error warning
					else
					{
						fprintf(output, "error\n");
					}
					break;
				//error warning
				default:
					fprintf(output, "error\n");
					break;
			}
			//freeing memory
			free(vector_1);
			free(vector_2);
			free(result);
			}
			//number mode
			else if(select == 's')
			{
				/*
				variables description:
				degInd - degree indicator
				num1 - first number
				num2 - second number
				factorial - variable for calculation factorial
				 */
				int degInd;
				float num1, num2, deg;
				long long int factorial;
				//reads a variable num1
				fscanf(input, "%f", &num1);
				//checking for operations using 1 number
				if (operation == '!' || operation == '^')
				{
					//operation selection
					switch (operation)
					{
					//factorial calculation block
						case '!':
							factorial = 1;
							//factorial negative number
							if(num1 < 0)
							{
								//error warning
								fprintf(output, "error\n\"invalid value\"\n");
							}
							//factorial 0
							else if(num1 == 0)
							{
								fprintf(output, "%.0f! = 1\n", num1);
							}
							else
							//main factorial
							{
								for(int i=1;i<=num1;i++)
								{
									factorial=factorial*i;
								}
									//output
								fprintf(output, "%.0f! = %I64i\n", num1, factorial);
							}
							break;
						//degree calculation and output
						case '^':
						deg = 1;
						//reads a variable degInd
						fscanf(input, "%i", &degInd);
						//degree indicator 0
						if(degInd == 0)
						{
							printf("%f^%i = 1\n",  num1, degInd);
						}
						//negative degree indicator
						else if (degInd < 0)
						{
							for(int i=1;i<=-degInd;i++)
							{
								deg = deg / num1;
							}
							fprintf(output, "%f^%i = %f\n", num1, degInd, deg);
						}
						//main degree calculation
						else
						{
							for(int i=1;i<=degInd;i++)
							{
								deg = deg * num1;
							}
							fprintf(output, "%f^%i = %f\n", num1, degInd, deg);
						}
						break;
					default:
						//error warning
						fprintf(output, "error\n");
						break;
					}
				}
				else
				{
					//reads a variable num2
					fscanf(input, "%f", &num2);
					//operation selection
					switch (operation)
					{
					//sum calculation
					case '+':
						fprintf(output, "%f + %f = %f\n", num1, num2, num1+num2);
						break;
						//subtraction calculation
						case '-':
						fprintf(output, "%f - %f = %f\n", num1, num2, num1-num2);
						break;
					//multiplication calculation
					case '*':
						fprintf(output, "%f * %f = %f\n", num1, num2, num1*num2);
						break;
					//division calculation
					case '/':
						fprintf(output, "%f / %f = %f\n", num1, num2, num1/num2);
						break;
					default:
						//error warning
						fprintf(output, "error\n\"unknown operation or incorrect input\"\n");
						break;
					}
				}
			}
			//error warning
			else
			{
				fprintf(output, "error\n\"incorrect input\"\n");
			}
		}
		//closing files
		fclose(output);
		fclose(input);
		//prompt to repeat the program and select new files
		printf("select new files and start over?\n'y' - yes\nother - no\n");
		scanf(" %c", &repeat);
	}
	while(repeat == 'y');
	return 0;
}
//the end :)
