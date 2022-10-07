#ifndef ASM_H
#define ASM_H

#include "Config.h"

#include <stdio.h>

#include "StrAlgorithms.h"

//-----------------------------------------------------------------------------

static const int MaxCmdLen = 5;
static const int MaxRegLen = 4;

//-----------------------------------------------------------------------------

struct ASM
{
    Text text;

    int   codeSize;
    char* code;
};

int AsmCtor (ASM* asm_s);
int AsmDtor (ASM* asm_s);

int    AsmGetCmds     (ASM* asm_s, FILE* fileIn);
Elem_t AsmArgHandler  (ASM* asm_s, int ip, int curLine, int numSkipSyms);
int    AsmMakeArrCmds (ASM* asm_s);
int    AsmMakeOutFile (ASM* asm_s, FILE* fileOut);

int GetRegIndex (const char* reg);

//-----------------------------------------------------------------------------

#endif