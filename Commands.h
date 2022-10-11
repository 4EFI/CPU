
#define S_POP       StackPop  (&cpu->stack)
#define S_PUSH(VAL) StackPush (&cpu->stack, VAL)

DEF_CMD (HLT, 0, 
{
    return 0;
})

DEF_CMD (PUSH, 1, 
{
    StackPush (&cpu->stack, arg_val);
})

DEF_CMD (ADD, 2, 
{
    // if (arg_val != NULL)
    StackPush (&cpu->stack,  StackPop (&cpu->stack) + StackPop (&cpu->stack));
})

DEF_CMD (SUB, 3, 
{
    StackPush (&cpu->stack, -StackPop (&cpu->stack) + StackPop (&cpu->stack));
})

DEF_CMD (MUL, 4, 
{
    StackPush (&cpu->stack,  StackPop (&cpu->stack) * StackPop (&cpu->stack));
})

DEF_CMD (DIV, 5, 
{
    Elem_t val_2 = StackPop (&cpu->stack), val_1 = StackPop (&cpu->stack);
                
    StackPush (&cpu->stack, val_1 / val_2);
})

DEF_CMD (OUT, 6, 
{
    if (arg_ptr)
    {
        if /**/ (cmd.memory) printf ("RAM[%d] = %d\n",  arg_ptr - cpu->RAM,  *arg_ptr);
        else if (cmd.reg)    printf ("Regs[%d] = %d\n", arg_ptr - cpu->regs, *arg_ptr);
    }
    else printf ("%d\n", StackPop (&cpu->stack));
})

DEF_CMD (POP, 7, 
{
    *arg_ptr = StackPop (&cpu->stack);
})

// Jumpes
DEF_CMD (JMP, 8,
{
    ip = arg_val;
})

#define DEF_JMP(NAME, NUM, COND)             \
    DEF_CMD (NAME, NUM,                      \
    {                                        \
        Elem_t val_2 = S_POP, val_1 = S_POP; \
                                             \
        if (val_1 COND val_2) ip = arg_val;  \
    })

#include "Jumpes.h"

#undef DEF_JMP

DEF_CMD (DUMP, 31, 
{
    StackFileOut = stdout;
    
    StackDump (&cpu->stack);

    CpuCmdDump (cpu, ip);

    CpuRegDump (cpu);
    printf ("\n");
    CpuRamDump (cpu);

    PrintSyms ('-', NumDumpDividers, stdout);
    printf    ("\n");

    StackFileOut = LogFile;
})

#undef S_POP
#undef S_PUSH