#ifndef ASM_H
#define ASM_H

#include "Config.h"

#include <stdio.h>

#include "StrAlgorithms.h"

//-----------------------------------------------------------------------------

struct Label
{
    int    val;
    String name;
};

struct ASM
{
    Text text;

    Label labels[NumLabels];

    int   codeSize;
    char* code;
};

int AsmCtor (ASM* asm_s);
int AsmDtor (ASM* asm_s);

int AsmGetCmds      (ASM* asm_s, FILE* fileIn);
int AsmLabelHandler (ASM* asm_s, const char* str,        int  len, int ip);
int AsmArgHandler   (ASM* asm_s, const char* strForRead, int* ip);
int AsmMakeArrCmds  (ASM* asm_s);
int AsmMakeOutFile  (ASM* asm_s, FILE* fileOut);

int GetLabelIndex (Label* labels, int numLabels, const char* str, int len);

int GetRegIndex (const char* reg);

//-----------------------------------------------------------------------------

#endif