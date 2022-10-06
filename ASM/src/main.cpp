#include <stdio.h>

#include "asm.h"

int main ()
{
    FILE* fileIn  = fopen ("../a.txt",  "r");
    FILE* fileOut = fopen ("../a.code", "wb");

    Asm asm_s = {0};
    AsmCtor (&asm_s);

    AsmGetCmds (&asm_s, fileIn);

    AsmMakeArrCmds (&asm_s);
    AsmMakeOutFile (&asm_s, fileOut);
}