//Used an AI tool to help me the undeerstanding of the code.
#ifndef BITOPS_H
#define BITOPS_H


//These set of lines are important functions for manipulation of the bits.
void SetBit(unsigned long long *value, int position);

void ClearBit(unsigned long long *value, int position);

void ToggleBit(unsigned long long *value, int position);

int GetBit(unsigned long long value, int position);

int CountBits(unsigned long long value);




#endif
