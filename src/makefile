# make the executable file
puzzle: main.o utilities.o PriorityQueue.o stack.o SolvePuzzle.o 
	gcc -o puzzle main.o utilities.o PriorityQueue.o stack.o SolvePuzzle.o -ggdb3

# make the object files needed
main.o: main.c
	gcc -c main.c -ggdb3

utilities.o: utilities.c
	gcc -c utilities.c -ggdb3

PriorityQueue.o: PriorityQueue.c
	gcc -c PriorityQueue.c -ggdb3

SolvePuzzle.o: SolvePuzzle.c
	gcc -c SolvePuzzle.c -ggdb3

stack.o: stack.c
	gcc -c stack.c -ggdb3

# run the program
run:
	./puzzle

# find the time for the puzzle to be solved
time:
	time ./puzzle

# clear excess object files
clear:
	rm -f *.o

# run valgrind
help:
	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes ./puzzle
