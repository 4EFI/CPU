
#define S_POP       StackPop  (&cpu->stack)
#define S_PUSH(VAL) StackPush (&cpu->stack, VAL)

DEF_CMD (HLT, 0, 
{
    return 0;
})

DEF_CMD (PUSH, 1, 
{
    S_PUSH (arg_val);
})

DEF_CMD (ADD, 2, 
{
    // if (arg_val != NULL)
    S_PUSH (S_POP + S_POP);
})

DEF_CMD (SUB, 3, 
{
    Elem_t val_2 = S_POP, val_1 = S_POP;
    
    S_PUSH (val_1 - val_2);
})

DEF_CMD (MUL, 4, 
{
    S_PUSH (S_POP * S_POP);
})

DEF_CMD (DIV, 5, 
{
    Elem_t val_2 = S_POP, val_1 = S_POP;
                
    S_PUSH (val_1 / val_2);
})

DEF_CMD (OUT, 6, 
{
    if (arg_ptr)
    {
        if /**/ (cmd.memory) printf ("RAM[%d] = %g\n",  arg_ptr - cpu->RAM,  (double)(*arg_ptr));
        else if (cmd.reg)    printf ("Regs[%d] = %g\n", arg_ptr - cpu->regs, (double)(*arg_ptr));
    }
    else printf ("%g\n", double(S_POP));
})

DEF_CMD (POP, 7, 
{
    *arg_ptr = S_POP;
})

// Jumpes
DEF_CMD (JMP, 8,
{
    ip = arg_val;
})

#define DEF_JMP(NAME, NUM, COND)                  \
    DEF_CMD (NAME, NUM,                           \
    {                                             \
        Elem_t val_2 = S_POP, val_1 = S_POP;      \
                                                  \
        if (val_1 COND val_2) ip = int(arg_val);  \
    })

#include "Jumpes.h"

#undef DEF_JMP

DEF_CMD (SQRT, 15, 
{
    S_PUSH (sqrt (S_POP));
})

DEF_CMD (DUMP, 31, 
{ 
    if (LogFile) StackDump (&cpu->stack);

    CpuCmdDump (cpu, ip, LogFile);
    CpuRegDump (cpu, LogFile);
    fprintf    (LogFile, "\n");
    CpuRamDump (cpu, LogFile);

    PrintSyms ('-', NumDumpDividers, LogFile);
    fprintf   (LogFile, "\n");
})

#undef S_POP
#undef S_PUSH