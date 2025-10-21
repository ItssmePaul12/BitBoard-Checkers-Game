# Used AI tool to help me get a better understanding of the code.

# These set of lines are meant for compiling and flaging purposes.
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# These set of lines are meant for the sourcing files and targeting purposes.
SRC = main.c bitops.c game.c
OBJ = $(SRC:.c=.o)
TARGET = checkers

# This line is meant for the default location for building the target.
all: $(TARGET)

# These set of lines are for linking the object files, which will go to execution for final.
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# These set of lines are meant for compiling the .c files into object files (.o).
%.O: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# This is meant for running the board game.
run: all
	./$(TARGET)

# This is meant for cleaning any files that have been generated.
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
