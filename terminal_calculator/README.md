
instructions for importing a project into eclipse

1. install eclipse (if you haven't already)
2. open git perspective
3. copy the link to this repository (https://github.com/ogolknev/main_mp)
4. in git perspective click "clone a git repository"
5. the link is automatically copied from the clipboard.
   click next, next, choose path to copy repository and click finish
6. in the copied repository in the folder "working tree" find the "terminal_calculator" project
   right click on it and select "import projects" and click finish in the window that appears

____________________________________________________________________________________________________

instructions for use:

the program works with files, and for its work you need a file with ready-made input data.
in this file, in the line, the first character is an operation, then a space indicates
the use of individual numbers (s) or vectors (v) (for vectors, an indication of their dimensions)
and then the required amount of data, each of the numbers is also separated by a space.
there can be several lines in the file with the input data separated by a space or a newline.
the output file will contain the original expression, the equal sign and the result.
parentheses are used to designate vectors in the output file.
when the program is finished you can start it again by selecting new input and output files.
____________________________________________________________________________________________________

what should the contents of the input file look like:

	operation(1) option(2) required data(3)
____________________________________________________________________________________________________

available operations and modes of operation:

v(vectors):

	+ - sum
	- - difference
	* - multiplication)
	/ - division
	' - dot product
	x - cross product(can only be used in size 3)

s(numbers):
	
	+ - sum
	- - difference
	* - multiplication)
	/ - division
	^ - exponentiation
	! - factorial
____________________________________________________________________________________________________
	
example:

input file:

	+ v 2 4 6 3 5
	! s 5
	
output file:

	(4.000000 6.000000) + (3.000000 5.000000) = (7.00000 11.00000)
	5! = 120
	
____________________________________________________________________________________________________

in the project folder there is an input file("input.txt") for checking all modes of the calculator

this file contain:
												
	+ v 2 1 2.1 3 4.2										
	- v 3 1 2.12 3 4 5 6									
	* v 4 1 2 3.213 4 5.1232 6 7 8							
	/ v 5 1 2 3.223 4 5 6 7 8 9.000 10						
	' v 6 1 2 3 4 5 6.22311 7 8 9 10 11 12					
	x v 3 5 6.245652 7 8 9.99999 10							
	+ s 1 2.1												
	- s -1.2 2												
	* s 1 -2.2												
	/ s -2 -1.1												
	^ s 3 10												
	! s 5
	
the output file should contain:

	( 1.000000 2.100000 ) + ( 3.000000 4.200000 ) = ( 4.000000 6.300000 )
	( 1.000000 2.120000 3.000000 ) - ( 4.000000 5.000000 6.000000 ) = ( -3.000000 -2.880000 -3.000000 )
	( 1.000000 2.000000 3.213000 4.000000 ) * ( 5.123200 6.000000 7.000000 8.000000 ) = ( 5.123200 12.000000 22.491001 32.000000 )
	( 1.000000 2.000000 3.223000 4.000000 5.000000 ) / ( 6.000000 7.000000 8.000000 9.000000 10.000000 ) = ( 0.166667 0.285714 0.402875 0.444444 0.500000 )
	( 1.000000 2.000000 3.000000 4.000000 5.000000 6.223110 ) ' ( 7.000000 8.000000 9.000000 10.000000 11.000000 12.000000 ) = 219.677322
	( 5.000000 6.245652 7.000000 ) x ( 8.000000 9.999990 10.000000 ) = ( -7.543411 6.000000 0.034737 )
	1.000000 + 2.100000 = 3.100000
	-1.200000 - 2.000000 = -3.200000
	1.000000 * -2.200000 = -2.200000
	-2.000000 / -1.100000 = 1.818182
	3.000000^10 = 59049.000000
	5! = 120
____________________________________________________________________________________________________

--- now you can use this project :) ---