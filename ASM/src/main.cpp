#include <stdio.h>

#include "asm.h"

int main ()
{
    FILE* fileIn  = fopen ("../Examples/number_squares.txt", "r");
    FILE* fileOut = fopen ("../Examples/number_squares.code", "wb");

    ASM asm_s = {0};
    AsmCtor (&asm_s);

    AsmGetCmds (&asm_s, fileIn);

    AsmMakeArrCmds (&asm_s);
    AsmMakeOutFile (&asm_s, fileOut);
}