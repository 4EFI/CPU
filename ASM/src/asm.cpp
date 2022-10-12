
#include "Config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"
#include "FileAlgorithms.h"
#include "StrAlgorithms.h"
#include "LOG.h"

#define _STR(str) #str
#define  STR(str) _STR(str)

//-----------------------------------------------------------------------------

int AsmCtor (ASM* asm_s)
{
    if (asm_s == NULL) return 0;
    
    TextInit (&asm_s->text); 

    // Fill all with zero
    memset (asm_s->labels, 0, NumLabels * sizeof (Label));

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
        char cmdName[MaxStrLen] = "";
    
        char* strForRead = asm_s->text.lines[i].str;

        int numReadSyms = 0;
        sscanf (strForRead, "%" STR(MaxStrLen) "s%n", cmdName, &numReadSyms); // Get command name

        if (numReadSyms == 0) continue;

        // Check label
        char* sym = strchr (cmdName, ':');

        if (sym)
        {
            AsmLabelHandler (asm_s, strForRead, sym - strForRead, ip);
            continue;
        }

        CMD* cmd = (CMD*)(&asm_s->code[ip]);
        
        AsmArgHandler (asm_s, strForRead + numReadSyms /*Str for read from*/, &ip);

        // Compare commands
        #define DEF_CMD(NAME, NUM, ...)        \
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

int AsmLabelHandler (ASM* asm_s, const char* str, int len, int ip)
{
    if (asm_s == NULL || str == NULL) return 0;

    int strPos = GetLabelIndex (asm_s->labels, NumLabels, str, len);

    if (strPos == -1)
    {
        int emptyLabel = -1;

        // Find empty label
        for (int i = 0; i < NumLabels; i++)
        {
            if (asm_s->labels[i].name.str == NULL) 
            {
                emptyLabel = i; 
                break; 
            }
        }

        String* str_ptr = &asm_s->labels[emptyLabel].name;

        str_ptr->str = (char*)str;
        str_ptr->len = len;

        asm_s->labels[emptyLabel].val = ip;
    }
    else 
    {
        printf ("Label \"%.*s\" already exists...\n", len, str);
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------

int AsmArgHandler (ASM* asm_s, const char* strForRead, int* ip)
{
    if (asm_s == NULL || strForRead == NULL) return 0;
    
    CMD* cmd = (CMD*)(&asm_s->code[(*ip)++]);

    // ??

    char* sym = strchr (strForRead, ':');

    if (sym)
    {
        int len = 0;
        strForRead = sym + 1;

        sscanf (strForRead, "%" STR(MaxStrLen) "*s%n", &len);

        int pos = GetLabelIndex (asm_s->labels, NumLabels, strForRead, len);

        if (pos == -1)
        {
            printf ("Label \"%.*s\" does not exist...\n", len, strForRead);
            return -1;
        }

        *(Elem_t*)(asm_s->code + *ip) = asm_s->labels[pos].val;
        
        (*ip) += sizeof (Elem_t); 

        cmd->immed = 1;

        return 1;
    }

    
    Elem_t val = 0;
    char reg_i[MaxStrLen] = "";

    bool isMemTreatment = false;
    
    // check [
    sym = strchr (strForRead, '[');
    
    int numSkipSyms = 0;
    if (sym) { isMemTreatment = true; numSkipSyms = sym - strForRead + 1; }

    if /**/ (sscanf (strForRead + numSkipSyms, "%lf + %" STR(MaxStrLen) "s",    &val,    reg_i) == 2 || 
             sscanf (strForRead + numSkipSyms, " %" STR(MaxStrLen) "[^+] + %lf", reg_i, &val  ) == 2) 
    /* if (value + reg_value) || (reg_value + value) */
    {
        cmd->immed = 1;
        cmd->reg   = 1;

        *(Elem_t*)(asm_s->code + *ip) = val;
        
        (*ip) += sizeof (Elem_t); 

        asm_s->code[(*ip)++] = GetRegIndex (reg_i);
    }

    else if (sscanf (strForRead + numSkipSyms, "%lf", &val) == 1) // if value
    {   
        cmd->immed = 1;

        *(Elem_t*)(asm_s->code + *ip) = val;
        
        (*ip) += sizeof (Elem_t); 
    }
    
    else if (sscanf (strForRead + numSkipSyms, "%" STR(MaxStrLen) "s", reg_i) == 1) // if register
    {    
        cmd->reg = 1;

        asm_s->code[(*ip)++] = GetRegIndex (reg_i);
    }

    // Check ]
    if (isMemTreatment && strchr (strForRead + numSkipSyms, ']')) cmd->memory = 1; 

    FLOG ("i = %d r = %d m = %d", cmd->immed, cmd->reg, cmd->memory);

    return 1;
}

int GetLabelIndex (Label* labels, int numLabels, const char* str, int len)
{
    for (int i = 0; i < numLabels; i++)
    {
        if (labels[i].name.str != NULL && strncmp (str, labels[i].name.str, len) == 0)
        {
            return i;
        }
    }

    return -1;  
}

//-----------------------------------------------------------------------------

int GetRegIndex (const char* reg)
{
    if (reg == NULL) return 0;

    int numRightIgnSyms = NumRightIgnoredSyms (reg, " ]");

    int len = strlen (reg) - numRightIgnSyms;
    
    if /**/ (strnicmp (reg, "rax", len) == 0) return RAX;
    else if (strnicmp (reg, "rbx", len) == 0) return RBX;
    else if (strnicmp (reg, "rcx", len) == 0) return RCX;
    else if (strnicmp (reg, "rdx", len) == 0) return RDX; 

    printf ("Register \"%.*s\" does not exist...\n", len, reg);

    return 0;
}

//-----------------------------------------------------------------------------

// Bin, Exec

int AsmMakeOutFile (ASM* asm_s, FILE* fileOut)
{   
    if (asm_s == NULL || fileOut == NULL) return 0;
    
    // signature, version, number of commands -> out file
    fprintf (fileOut, "%s %d %d\n", Signature, Version, asm_s->codeSize);

    fwrite (asm_s->code, sizeof (char), asm_s->codeSize, fileOut);
    
    return 1;
}

//-----------------------------------------------------------------------------