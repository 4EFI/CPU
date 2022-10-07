
#include <stdio.h>

#include "cpu.h"
#include "LOG.h"

//-----------------------------------------------------------------------------

int CpuCtor (CPU* cpu)
{
    if (cpu == NULL) return 0;
    
    StackCtor (&cpu->stack, 1);

    cpu->codeSize = 0;
    cpu->code     = 0;

    return 1;
}

//-----------------------------------------------------------------------------

int CpuGetCmdsArr (CPU* cpu, FILE* file)
{
    if (file == NULL || file == NULL) return 0;
    
    fscanf (file, "%*s %*d");
    fscanf (file, "%d", &cpu->codeSize);

    LOG ("%d", cpu->codeSize);

    calloc ();

    return 1;
}

//-----------------------------------------------------------------------------