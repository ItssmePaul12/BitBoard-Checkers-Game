//Used an AI tool to help me the undeerstanding of the code.
#include "bitops.h"

//This function is setting the bit at a specified position, which goes to 1.
void SetBit(unsigned long long *value, int position){
    *value |= (1ULL << position);
}

//This function is clearing, which will set to zero, at the specified position.
void ClearBit(unsigned long long *value, int position){
    *value &= ~(1ULL << position);
}

//This function is meant for toggling the bits of the board game.
void ToggleBit(unsigned long long *value, int position){
    *value ^= (1ULL << position);
}

//This is meant for returning the value of a bit, either 0 or 1, at a specified position.
int GetBit(unsigned long long value, int position){
    return (value >> position) & 1ULL;
}

//This function is meant for counting the total calculation of the bits.
int CountBits(unsigned long long value){
    int count = 0;
    while (value){
        count += value & 1ULL;
        value >>= 1;
    }
    return count;
}

