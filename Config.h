#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------

static const int RegLen  = 3;
static const int NumRegs = 5;

enum Reg_i
{
    R0X = 0,
    RAX = 1,
    RBX = 2,
    RCX = 3, 
    RDX = 4
};

struct CMD
{
    unsigned char code   : 4;
    unsigned char immed  : 1;
    unsigned char reg    : 1;
    unsigned char memory : 1;
    unsigned char unused : 1;
};

//#define NDUMP
//#define NHASH
//#define NCANARY

typedef int Elem_t;

static char Signature[] = "SP"; // Super paper
static int  Version     = 1;

enum CmdNames
{
    HLT = 0, PUSH, ADD, SUB, MUL, DIV, OUT, POP, DUMP = 15
};

//-----------------------------------------------------------------------------

#endif