
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

Elem_t* CpuGetArg (CPU* cpu, int* ip, Elem_t* val)
{
    if (cpu == NULL) return 0;

    CMD cmd = {0};
    *(char*)(&cmd) = cpu->code[(*ip)++];

    Elem_t* arg_ptr = NULL;   

    if (cmd.immed)
    {
        (*val) += *(Elem_t*)(cpu->code + *ip);
        (*ip)  += sizeof (Elem_t);
    }
    
    if (cmd.reg)
    {        
        (*val) +=  cpu->regs[cpu->code[*ip]];

        arg_ptr = &cpu->regs[cpu->code[*ip]];

        (*ip)++;
    }

    if (cmd.memory)
    {
        // 
    }

    return arg_ptr;  
}

//-----------------------------------------------------------------------------

int CpuCmdsHandler (CPU* cpu)
{
    if (cpu == NULL) return 0;

    for (int ip = 0; ip < cpu->codeSize; )
    {
        CMD cmd = {0};
        *(char*)(&cmd) = cpu->code[ip];

        Elem_t  arg_val = 0;
        Elem_t* arg_ptr = CpuGetArg (cpu, &ip, &arg_val);

        switch (cmd.code)
        {
            case PUSH:
                StackPush (&cpu->stack, arg_val);
                break;

            case POP:
                *arg_ptr = StackPop (&cpu->stack);
                LOG ("%d", cpu->regs[1]);
                break;

            case ADD:
                // if (arg_val != NULL)
                StackPush (&cpu->stack,  StackPop (&cpu->stack) + StackPop (&cpu->stack));
                break;

            case SUB:
                StackPush (&cpu->stack, -StackPop (&cpu->stack) + StackPop (&cpu->stack));
                break;

            case MUL:
                StackPush (&cpu->stack,  StackPop (&cpu->stack) * StackPop (&cpu->stack));
                break;

            case DIV:
            {
                Elem_t val_2 = StackPop (&cpu->stack), val_1 = StackPop (&cpu->stack);
                
                StackPush (&cpu->stack, val_1 / val_2);
                break;
            }

            case OUT:
                printf ("%d\n", StackPop (&cpu->stack));
                break;

            case HLT:
                return 0;
                break;
        }
    }
    
    return 1;
}

//-----------------------------------------------------------------------------