//Used an AI tool to help me the undeerstanding of the code.
#include "bitops.h"


void SetBit(unsigned long long *value, int position){
    *value |= (1ULL << position);
}


void ClearBit(unsigned long long *value, int position){
    *value &= ~(1ULL << position);
}

void ToggleBit(unsigned long long *value, int position){
    *value ^= (1ULL << position);
}

int GetBit(unsigned long long value, int position){
    return (value >> position) & 1ULL;
}

int CountBits(unsigned long long value){
    int count = 0;
    while (value){
        count += value & 1ULL;
        value >>= 1;
    }
    return count;
}

