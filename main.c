//Used AI tool to help me with the understanding of the code.
#include <stdio.h>
#include "bitops.h"
#include "game.h"

int main(){


    //These set of lines are meant for the test 1 phase of the bit manipulation for the project purpose.
    unsigned long long test = 0;
    printf("=== Bit Manipulation Test ===\n");
    SetBit(&test, 3);
    printf("After setting bit 3: %I64u\n", test);
    ToggleBit(&test, 3);
    printf("After toggling bit 3: %I64u\n", test);
    printf("Count of the bits set: %d\n", CountBits(test));


    //These set of lines are meant for starting the checkers game.
    printf("\n=== Starting the Checkers Game ===\n");
    PlayGame();
    return 0;


}