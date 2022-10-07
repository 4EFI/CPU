#ifndef ASM_H
#define ASM_H

#include <stdio.h>

#include "StrAlgorithms.h"

//-----------------------------------------------------------------------------

static const int MaxCmdLen = 5;

//-----------------------------------------------------------------------------

struct ASM
{
    Text text;

    int   codeSize;
    char* code;
};

int AsmCtor (ASM* asm_s);
int AsmDtor (ASM* asm_s);

int AsmGetCmds     (ASM* asm_s, FILE* fileIn);
int AsmMakeArrCmds (ASM* asm_s);
int AsmMakeOutFile (ASM* asm_s, FILE* fileOut);

//-----------------------------------------------------------------------------

#endif