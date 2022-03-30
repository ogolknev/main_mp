/*
 ===============================================================================================
 Name        : Terminal Calculator
 Author      : Ogolknev Nikita
 Version     : 1.0
 Description : this program is for calculating six arithmetic operations between two numbers
 	 	 	   (instructions are contained in the program itself. follow them to get the result)
 ===============================================================================================
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	/*
	variables description:
	degInd - degree indicator
	num1 - first number
	num2 - second number
	factorial - variable for calculation factorial
	op - operation
	repeat - variable to repeat
	*/
	int degInd;
	float num1, num2, deg;
	long long int factorial;
	char op;
	char repeat = 'y';
	do
	{
		//print instruction
		printf("enter first number: \n");
		//reads a variable num1
		scanf("%f", &num1);
		//print instruction
		printf("enter operation: \n\"+\" - sum\n\"-\" - subtraction\n\"*\" - multiplication\n\"\\\" - devision\n\"!\" - factorial\n\"^\" - exponentiation\n");
		//reads a variable op
		scanf(" %c", &op);
		//checking for operations using 1 number
		if (op == '!' || op == '^')
		{
			//operation selection
			switch (op)
			{
			//factorial calculation block
			case '!':
				factorial = 1;
				//factorial negative number
		        if(num1 < 0)
		        {
		        	//error warning
		        	printf("error\n\"invalid value\"\n");
		        }
		        //factorial 0
		        else if(num1 == 0)
		        {
		        	//output
		        	printf("%.0f! = 1\n", num1);
		        }
		        else
		        //main factorial
		        {
		        	for(int i=1;i<=num1;i++)
		        	{
		        		factorial=factorial*i;
		        	}
		        	//output
		        	printf("%.0f! = %I64i\n", num1, factorial);
		        }
				break;
			//degree calculation block
			case '^':
					deg = 1;
					//print instruction
					printf("enter degree indicator: \n");
					//reads a variable degInd
					scanf("%i",&degInd);
					//degree indicator 0
					if(degInd == 0)
					{
						//output
						printf("%f^%i = 1\n",  num1, degInd);
					}
					//negative degree indicator
					else if (degInd < 0)
					{
						for(int i=1;i<=-degInd;i++)
						{
							deg = deg / num1;
						}
						//output
						printf("%f^%i = %f\n", num1, degInd, deg);
					}
					//main degree calculation
					else
					{
						for(int i=1;i<=degInd;i++)
						{
							deg = deg * num1;
						}
						//output
						printf("%f^%i = %f\n", num1, degInd, deg);
					}
				break;
			default:
				//error warning
				printf("error\n");
				break;
			 }
		}
		else
		{
		//print instruction
		printf("enter second number: \n");
		//reads a variable num2
		scanf("%f", &num2);
		//operation selection
		switch (op)
		{
			//sum calculation block
			case '+':
				printf("%f + %f = %f\n", num1, num2, num1+num2);
				break;
			//subtraction calculation block
			case '-':
				printf("%f - %f = %f\n", num1, num2, num1-num2);
				break;
			//multiplication calculation block
			case '*':
				printf("%f * %f = %f\n", num1, num2, num1*num2);
				break;
			//division calculation block
			case '/':
				printf("%f / %f = %f\n", num1, num2, num1/num2);
				break;
			default:
				//error warning
				printf("error\n\"unknown operation or incorrect input\"\n");
				break;
		}
		}
		printf("\nstart over? (\"y\" - yes, other - no): \n");
		//reads a variable repeat
		scanf(" %c", &repeat);
	}
	//repeat condition
	while(repeat == 'y');
	return 0;
}


