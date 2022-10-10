
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
    if (asm_s == NULL) return 0;
    
    TextInit (&asm_s->text); 

    asm_s->codeSize = 0;
    asm_s->code     = NULL;

    return 1;
}

//-----------------------------------------------------------------------------

int AsmGetCmds (ASM* asm_s, FILE* fileIn)
{
    if (asm_s == NULL || fileIn == NULL) return 0;
    
    long numStrs       = TextSetFileLines (&asm_s->text, fileIn); 
    asm_s->codeSize = 2 * numStrs * sizeof (Elem_t); 

    asm_s->code = (char*)calloc (asm_s->codeSize, sizeof (char));

    return 1;
}

//-----------------------------------------------------------------------------

int AsmMakeArrCmds (ASM* asm_s)
{   
    if (asm_s == NULL) return 0;
    
    int ip = 0;
    
    for (int i = 0; i < asm_s->text.numLines; i++)
    {
        char cmdName[MaxCmdLen] = "";

        int numReadSyms = 0;
        sscanf (asm_s->text.lines[i].str, "%s%n", cmdName, &numReadSyms); // Get command name

        if (numReadSyms == 0) continue;

        int ipCopy = ip;
        AsmArgHandler (asm_s, asm_s->text.lines[i].str + numReadSyms /*Str for read from*/, &ip);


        CMD* cmd = (CMD*)(&asm_s->code[ipCopy]);

        // Compare commands
        #define DEF_CMD(NAME, NUM)             \
            if (stricmp (cmdName, #NAME) == 0) \
            {                                  \
                cmd->code = NUM;               \
            }                                  \
            else

        #include "Commands.h"
        /*else*/
        {
            // Command does not exist
            continue;
        }

        #undef DEF_CMD
    }

    asm_s->codeSize = ip;

    return 1;
}

//-----------------------------------------------------------------------------

int AsmArgHandler (ASM* asm_s, const char* strForRead, int* ip)
{
    if (asm_s == NULL || strForRead == NULL) return 0;
    
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

    FLOG ("code = %d i = %d r = %d", cmd->code, cmd->immed, cmd->reg);

    return 1;
}

//-----------------------------------------------------------------------------

int GetRegIndex (const char* reg)
{
    if (reg == NULL) return 0;
    
    if (stricmp (reg, "rax") == 0) return RAX;
    if (stricmp (reg, "rbx") == 0) return RBX;
    if (stricmp (reg, "rcx") == 0) return RCX;
    if (stricmp (reg, "rdx") == 0) return RDX; 

    return 0;
}

//-----------------------------------------------------------------------------

int AsmMakeOutFile (ASM* asm_s, FILE* fileOut)
{   
    if (asm_s == NULL || fileOut == NULL) return 0;
    
    // signature, version, number of commands -> out file
    fprintf (fileOut, "%s %d %d\n", Signature, Version, asm_s->codeSize);

    fwrite (asm_s->code, sizeof (char), asm_s->codeSize, fileOut);
    
    return 1;
}

//-----------------------------------------------------------------------------