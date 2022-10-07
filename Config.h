#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------

//#define NDUMP
//#define NHASH
//#define NCANARY

typedef int Elem_t;

static char Signature[] = "SP"; // Super paper
static int  Version     = 1;

enum CmdNames
{
    HLT = 0, PUSH, ADD, SUB, MUL, DIV, OUT, DUMP = 100  
};

//-----------------------------------------------------------------------------

#endif