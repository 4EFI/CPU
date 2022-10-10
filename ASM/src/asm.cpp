
#include "Config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"
#include "FileAlgorithms.h"
#include "StrAlgorithms.h"
#include "LOG.h"

//-----------------------------------------------------------------------------

int AsmCtor (ASM* asm_s)
{
    TextInit (&asm_s->text); 

    asm_s->codeSize = 0;
    asm_s->code     = NULL;

    return 1;
}

//-----------------------------------------------------------------------------

int AsmGetCmds (ASM* asm_s, FILE* fileIn)
{
    long numStrs       = TextSetFileLines (&asm_s->text, fileIn); 
    asm_s->codeSize = 2 * numStrs * sizeof (Elem_t); 

    asm_s->code = (char*)calloc (asm_s->codeSize, sizeof (char));

    return 1;
}

//-----------------------------------------------------------------------------

int AsmMakeArrCmds (ASM* asm_s)
{   
    int ip               = 0;
    int totalArrCmdsSize = 0;
    
    for (int i = 0; i < asm_s->text.numLines; i++)
    {
        char cmd[MaxCmdLen] = "";

        int numReadSyms = 0;
        sscanf (asm_s->text.lines[i].str, "%s%n", cmd, &numReadSyms); // Get command name

        if (numReadSyms == 0) continue;

        if /**/ (stricmp (cmd, "push") == 0)
        {
            asm_s->code[ip] = PUSH;
        }
        else if (stricmp (cmd, "pop")  == 0)
        {
            asm_s->code[ip] = POP;
        }
        else if (stricmp (cmd, "add")  == 0)
        {
            asm_s->code[ip] = ADD;
        }
        else if (stricmp (cmd, "sub")  == 0)
        {
            asm_s->code[ip] = SUB;
        }
        else if (stricmp (cmd, "mul")  == 0)
        {
            asm_s->code[ip] = MUL;
        }
        else if (stricmp (cmd, "div")  == 0)
        {   
            asm_s->code[ip] = DIV;
        }
        else if (stricmp (cmd, "out")  == 0)
        {   
            asm_s->code[ip] = OUT;
        }
        else if (stricmp (cmd, "hlt")  == 0)
        {   
            asm_s->code[ip] = HLT;
        }
        else
        {
            // Command does not exist
            continue;
        }

        AsmArgHandler (asm_s, asm_s->text.lines[i].str + numReadSyms /*Str for read from*/, &ip);
    }

    LOG ("%d", ip);

    asm_s->codeSize = ip;

    return 1;
}

//-----------------------------------------------------------------------------

int AsmArgHandler (ASM* asm_s, const char* strForRead, int* ip)
{
    if (asm_s == 0 || strForRead == 0) return 0;
    
    CMD* cmd = (CMD*)(&asm_s->code[(*ip)++]);
    
    Elem_t val = 0;
    char reg_i[MaxRegLen] = "";
    
    if /**/ (sscanf (strForRead, "%d", &val) == 1) // if value
    {   
        cmd->immed = 1;

        *(Elem_t*)(asm_s->code + *ip) = val;
        
        (*ip) += sizeof (Elem_t); 
    }
    
    else if (sscanf (strForRead, "%s", reg_i) == 1) // if register
    {    
        if (strlen (reg_i) == RegLen) 
        {
            cmd->reg = 1;

            asm_s->code[(*ip)++] = GetRegIndex (reg_i);
        }
    }

    LOG ("code = %d i = %d r = %d", cmd->code, cmd->immed, cmd->reg);

    return 1;
}

//-----------------------------------------------------------------------------

int GetRegIndex (const char* reg)
{
    if (stricmp (reg, "rax") == 0) return RAX;
    if (stricmp (reg, "rbx") == 0) return RBX;
    if (stricmp (reg, "rcx") == 0) return RCX;
    if (stricmp (reg, "rdx") == 0) return RDX; 

    return 0;
}

//-----------------------------------------------------------------------------

int AsmMakeOutFile (ASM* asm_s, FILE* fileOut)
{   
    // signature, version, number of commands -> out file
    fprintf (fileOut, "%s %d %d\n", Signature, Version, asm_s->codeSize);

    fwrite (asm_s->code, sizeof (char), asm_s->codeSize, fileOut);
    
    return 1;
}

//-----------------------------------------------------------------------------