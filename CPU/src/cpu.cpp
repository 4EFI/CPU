
#include <stdio.h>
#include <stdlib.h>

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
    fscanf (file, "%d ", &cpu->codeSize);

    LOG ("Code Size = %d", cpu->codeSize);

    cpu->code = (char*)calloc (cpu->codeSize, sizeof (char));

    fread (cpu->code, sizeof (char), cpu->codeSize, file);

    return 1;
}

//-----------------------------------------------------------------------------

int CpuCmdsHandler (CPU* cpu)
{
    if (cpu == NULL) return 0;

    for (int ip = 0; ip < cpu->codeSize; ip++)
    {
        CMD cmd = {0};
        *(char*)(&cmd) = cpu->code[ip];

        switch (cmd.code)
        {
            case PUSH:
            {
                ip++;
                Elem_t val = *(Elem_t*)(cpu->code + ip);

                StackPush (&cpu->stack, val);

                ip += (sizeof (Elem_t) - 1);
                break;
            }

            case ADD:
                StackPush (&cpu->stack, StackPop (&cpu->stack) + StackPop (&cpu->stack));
                break;

            case OUT:
                printf ("%d\n", StackPop (&cpu->stack));
                break;
        }

        StackDump (&cpu->stack);
    }
    
    return 1;
}

//-----------------------------------------------------------------------------