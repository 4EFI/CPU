#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------

static int RegLen = 3;

enum Reg_i
{
    RAX = 1,
    RBX,
    RCX, 
    RDX
};

struct CMD
{
    char code   : 4;
    char immed  : 1;
    char reg    : 1;
    char unused : 2;
};

#define NDUMP
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