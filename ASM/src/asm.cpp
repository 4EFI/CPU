
#include "Config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"
#include "FileAlgorithms.h"
#include "StrAlgorithms.h"
#include "LOG.h"

//-----------------------------------------------------------------------------

int AsmCtor (Asm* asm_s)
{
    TextInit (&asm_s->text); 

    asm_s->numCmds = 0;
    asm_s->arrCmds = NULL;

    return 1;
}

//-----------------------------------------------------------------------------

int AsmGetCmds (Asm* asm_s, FILE* fileIn)
{
    long numStrs = TextSetFileLines (&asm_s->text, fileIn); 
    asm_s->numCmds = 2 * numStrs; 

    asm_s->arrCmds = (int*)calloc (asm_s->numCmds, sizeof (int));

    return 1;
}

//-----------------------------------------------------------------------------

int AsmMakeArrCmds (Asm* asm_s)
{   
    int curCmd  = 0;
    int numCmds = 0;
    
    for (int i = 0; asm_s->text.numLines; i++)
    {
        char cmd[MaxCmdLen] = "";

        int numReadSyms = 0;

        sscanf (asm_s->text.lines[i].str, "%s%n", cmd, &numReadSyms);

        // Break for (;;)
        if (numReadSyms == 0) break;

        if      (stricmp (cmd, "push") == 0)
        {
            asm_s->arrCmds[curCmd++] = PUSH;

            int val = 0;            
            sscanf ((asm_s->text).lines[i].str + numReadSyms, "%d", &val);

            asm_s->arrCmds[curCmd] = val;

            numCmds++;
        }
        else if (stricmp (cmd, "add")  == 0)
        {
            asm_s->arrCmds[curCmd] = ADD;
        }
        else if (stricmp (cmd, "sub")  == 0)
        {
            asm_s->arrCmds[curCmd] = SUB;
        }
        else if (stricmp (cmd, "mul")  == 0)
        {
            asm_s->arrCmds[curCmd] = MUL;
        }
        else if (stricmp (cmd, "div")  == 0)
        {   
            asm_s->arrCmds[curCmd] = DIV;
        }
        else if (stricmp (cmd, "out")  == 0)
        {   
            asm_s->arrCmds[curCmd] = OUT;
        }
        else if (stricmp (cmd, "hlt")  == 0)
        {   
            asm_s->arrCmds[curCmd] = HLT;
        }
        else
        {
            // Command does not exist
            continue;
        }

        curCmd++;
        numCmds++;
    }

    asm_s->numCmds = numCmds;

    return 1;
}

//-----------------------------------------------------------------------------

int AsmMakeOutFile (Asm* asm_s, FILE* fileOut)
{   
    fprintf (fileOut, "%s %d %d\n", AsmSignature.specialWord, AsmSignature.version, asm_s->numCmds);

    fwrite (asm_s->arrCmds, sizeof (int), asm_s->numCmds, fileOut);
    
    return 1;
}

//-----------------------------------------------------------------------------