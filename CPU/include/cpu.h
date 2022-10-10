#ifndef CPU_H
#define CPU_H

#include "Config.h"

#include "Stack.h"

//-----------------------------------------------------------------------------

struct Label
{
    int  val;
    char name[MaxStrLen];
};


struct CPU
{
    Elem_t RAM[RamSize];
    
    Elem_t regs  [NumRegs];
    Label  labels[NumLabels];
    
    Stack_t stack; 
    
    int   codeSize;
    char* code;
};

int     CpuCtor        (CPU* cpu);
int     CpuGetCmdsArr  (CPU* cpu, FILE* file);
int     CpuCmdsHandler (CPU* cpu);
Elem_t* CpuGetArg      (CPU* cpu, int* ip, Elem_t* val);

//-----------------------------------------------------------------------------

#endif