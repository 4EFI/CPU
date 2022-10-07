#ifndef CPU_H
#define CPU_H

#include "Config.h"

#include "Stack.h"

//-----------------------------------------------------------------------------

struct CPU
{
    Stack_t stack; 
    
    int   codeSize;
    char* code;
};

int CpuCtor       (CPU* cpu);
int CpuGetCmdsArr (CPU* cpu, FILE* file);

//-----------------------------------------------------------------------------

#endif