#include <stdio.h>

#include "asm.h"
#include "LOG.h"
#include "OptionsCmdLine.h"

//-----------------------------------------------------------------------------

int main (int argc, const char* argv[])
{
    FILE* fileIn  = fopen ("../Examples/number_squares.txt", "r");
    FILE* fileOut = fopen ("../Examples/number_squares.code", "wb");

    START_OPT_HANDLER (argc, argv)
    {
        OPT_HANDLER ("-o", LOG ("asdfasf"));    
    }
    FINISH_OPT_HANDLER()

    ASM asm_s = { 0 };
    AsmCtor (&asm_s);

    AsmGetCmds (&asm_s, fileIn);

    AsmMakeArrCmds (&asm_s);
    AsmMakeOutFile (&asm_s, fileOut);

    fclose (fileIn);
    fclose (fileOut);
}

//-----------------------------------------------------------------------------

int SetFileOut(FILE* fileOut, const char* fileName)
{
    if (fileOut == NULL) return 0;
}

//-----------------------------------------------------------------------------