SRC_DIR = ./src
MOD_DIR = ./modules

OBJ = $(SRC_DIR)/main.o \
	  $(SRC_DIR)/utilities.o \
	  $(SRC_DIR)/SolvePuzzle.o \
	  $(MOD_DIR)/stack.o \
	  $(MOD_DIR)/pq.o

EXEC = npuzzle
CC = gcc

# make the executable file
npuzzle: $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) -ggdb3

# make the object files needed
main.o: $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c -ggdb3

utilities.o: $(SRC_DIR)/utilities.c
	$(CC) -c $(SRC_DIR)/utilities.c -ggdb3

SolvePuzzle.o: $(SRC_DIR)/SolvePuzzle.c
	$(CC) -c $(SRC_DIR)/SolvePuzzle.c -ggdb3

stack.o: $(MOD_DIR)/stack.c
	$(CC) -c $(MOD_DIR)/stack.c -ggdb3

pq.o: $(MOD_DIR)/pq.c
	$(CC) -c $(MOD_DIR)/pq.c -ggdb3

# play the game
play: $(EXEC)
	./npuzzle

# run example
EXAMPLE = 4
example: $(EXEC)
	./npuzzle < examples/example$(EXAMPLE).txt

help: $(EXEC)
	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes ./npuzzle

# delete excess object files
clear:
	rm -f $(OBJ)
