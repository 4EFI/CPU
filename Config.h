#ifndef CONFIG_H
#define CONFIG_H

#include "asm.h"

//-----------------------------------------------------------------------------

Signature AsmSignature = {"HEHE", 1};

enum CmdNames
{
    HLT = 0, PUSH, ADD, SUB, MUL, DIV, OUT, DUMP = 100  
};

//-----------------------------------------------------------------------------

#endif