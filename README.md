# BFS-Breadth-First-Search

Serial part:

This code is to solve the 8-puzzle problem using the breadth first search algorithm.

Note that we will be having two 4’s and two 5’s in this problem and no 3 or 6. 

The program will ask the user to enter the starting position as a string (i.e. 142045578   the 0 is used for space).


Then the output should be the sequence of actions that will lead to the goal:

(0 1 2 4 4 5 5 7 8)

The output is:
1. The initial state (print the 8-puzzle).

2. Depth value.

3. Cost value.

4. Time taken by the program.


	
NOTE: Any action is illegal, ignore it.


****************************************************************************

MPI part:

This code is slove the 8-puzzle problem using breadth first search algorithm with MPI.

Note that you should run the mpirun command with a number of processes equal to 5.

The program will ask the user to enter the starting position as a string (i.e. 142045578   the 0 is used for space).

Then the output should be the sequence of actions that will lead to the goal:

(0 1 2 4 4 5 5 7 8)

The output is:
1. The initial state (print the 8-puzzle).

2. The depth and cost from each rank and the time taken by the rank.

3. Rank 0 prints the optimal solution found based on the minimum depth.

4. Time taken by the program.


NOTE:
   To compile the mpi file: mpic++ filename.cpp -o namefile and to run the mpi file: mpirun -np 5 ./filename
