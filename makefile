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
	$(CC) -o $(EXEC) $(OBJ)

# make the object files needed
main.o: $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c

utilities.o: $(SRC_DIR)/utilities.c
	$(CC) -c $(SRC_DIR)/utilities.c

SolvePuzzle.o: $(SRC_DIR)/SolvePuzzle.c
	$(CC) -c $(SRC_DIR)/SolvePuzzle.c

stack.o: $(MOD_DIR)/stack.c
	$(CC) -c $(MOD_DIR)/stack.c

pq.o: $(MOD_DIR)/pq.c
	$(CC) -c $(MOD_DIR)/pq.c

# delete excess object files
clear:
	rm -f $(OBJ)

# run the program
run:
	./npuzzle