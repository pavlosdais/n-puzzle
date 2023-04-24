# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS =

# Directories
SRC_DIR = src
MODULES_DIR = modules
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
MODULES_FILES = $(wildcard $(MODULES_DIR)/*.c)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES)) \
            $(patsubst $(MODULES_DIR)/%.c, $(OBJ_DIR)/%.o, $(MODULES_FILES))

# Executable program
EXECUTABLE_NAME = npuzzle
EXECUTABLE = $(BIN_DIR)/$(EXECUTABLE_NAME)

# OS
OS := LIN
ifeq ($(OS), WIN)
	CC = x86_64-w64-mingw32-gcc
	EXECUTABLE = $(BIN_DIR)/$(EXECUTABLE_NAME).exe
endif

all: $(EXECUTABLE)

# Targets
.PHONY: all clean valgrind

# Create the executable program
$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MODULES_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Play the game
play:
	./$(EXECUTABLE)

# Example demo
EXAMPLE = 5
example: $(EXECUTABLE)
	./$(EXECUTABLE) < examples/example$(EXAMPLE).txt

# Clear files used by the program
clear:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Use valgrind - Output is saved at bin/valgrind.log
help: $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./bin/valgrind.log ./$(EXECUTABLE)

# Final build // use optimization flags
final: CFLAGS = -Ofast
final: LDFLAGS = 
final: all
