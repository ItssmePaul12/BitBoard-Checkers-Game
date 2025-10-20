CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC = main.c bitops.c game.c
OBJ = $(SRC:.c=.o)
TARGET = checkers

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.O: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
