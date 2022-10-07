
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
    int curCmd           = 0;
    int totalArrCmdsSize = 0;
    
    for (int i = 0; asm_s->text.numLines; i++)
    {
        char cmd[MaxCmdLen] = "";

        int numReadSyms = 0;
        sscanf (asm_s->text.lines[i].str, "%s%n", cmd, &numReadSyms);

        // Break for (;;)
        if (numReadSyms == 0) break;

        if      (stricmp (cmd, "push") == 0)
        {
            asm_s->code[curCmd++] = PUSH;

            Elem_t val = 0;            
            sscanf (asm_s->text.lines[i].str + numReadSyms, "%d", &val); // %d if Elem_t is int

            *(int*)(asm_s->code + curCmd) = val;

            totalArrCmdsSize += (sizeof (char) + sizeof (Elem_t)); // Command + values
            curCmd           +=  sizeof (Elem_t);

            continue;
        }
        else if (stricmp (cmd, "add")  == 0)
        {
            asm_s->code[curCmd] = ADD;
        }
        else if (stricmp (cmd, "sub")  == 0)
        {
            asm_s->code[curCmd] = SUB;
        }
        else if (stricmp (cmd, "mul")  == 0)
        {
            asm_s->code[curCmd] = MUL;
        }
        else if (stricmp (cmd, "div")  == 0)
        {   
            asm_s->code[curCmd] = DIV;
        }
        else if (stricmp (cmd, "out")  == 0)
        {   
            asm_s->code[curCmd] = OUT;
        }
        else if (stricmp (cmd, "hlt")  == 0)
        {   
            asm_s->code[curCmd] = HLT;
        }
        else
        {
            // Command does not exist
            continue;
        }

        curCmd++;
        totalArrCmdsSize++;
    }

    asm_s->codeSize = totalArrCmdsSize;

    return 1;
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