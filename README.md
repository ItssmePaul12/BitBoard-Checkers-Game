# BitBoard-Checkers-Game

## Author 
Paul O.

## Description
The goal of the project is using many data representation and data manipulation bits to be used as a board game of checkers.

## Build Instructions

Make sure to run the following commands in the terminal to be able to run the game:

If using Make:
```
make
make run
```

If Make isn't working properly, try these commands in your terminal:
```
gcc -Wall -Wextra -std=c11 -g main.c game.c bitops.c -o checkers
./checkers
```

## Notes
I did run into some issues with the board-masking logic. I am tried to do a lot of things to fix it, but was unable to fix it (Something with the VALID_SQUARES in the game.c file). But, everything else should be working well such as the loading, saving, etc. 

