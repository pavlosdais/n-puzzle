# make the executable file
npuzzle: main.o utilities.o PriorityQueue.o stack.o SolvePuzzle.o 
	gcc -o npuzzle main.o utilities.o PriorityQueue.o stack.o SolvePuzzle.o

# make the object files needed
main.o: main.c
	gcc -c main.c

utilities.o: utilities.c
	gcc -c utilities.c

PriorityQueue.o: PriorityQueue.c
	gcc -c PriorityQueue.c

SolvePuzzle.o: SolvePuzzle.c
	gcc -c SolvePuzzle.c

stack.o: stack.c
	gcc -c stack.c

# run the program
run:
	./npuzzle

# clear excess object files
clear:
	rm -f *.o
