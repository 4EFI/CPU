#ifndef ASM_H
#define ASM_H

#include <stdio.h>

#include "StrAlgorithms.h"

//-----------------------------------------------------------------------------

static const int MaxCmdLen = 5;

//-----------------------------------------------------------------------------

struct Signature
{
    char* specialWord;
    int   version;
};

struct Asm
{
    Signature signature;

    Text text;

    int  numCmds;
    int* arrCmds;
};

int AsmCtor (Asm* asm_s);
int AsmDtor (Asm* asm_s);

int AsmGetCmds     (Asm* asm_s, FILE* fileIn);
int AsmMakeArrCmds (Asm* asm_s);
int AsmMakeOutFile (Asm* asm_s, FILE* fileOut);

//-----------------------------------------------------------------------------

#endif