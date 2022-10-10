#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------

static const int NumRegs   = 5;
static const int NumLabels = 20;
static const int RamSize   = 100;

static const int MaxStrLen = 255;

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
    unsigned char code   : 5;
    unsigned char immed  : 1;
    unsigned char reg    : 1;
    unsigned char memory : 1;
};

#define NDUMP
//#define NHASH
//#define NCANARY

typedef int Elem_t;

static char Signature[] = "SP"; // Super paper
static int  Version     = 1;

#define DEF_CMD(NAME, NUM, ...) \
    CMD_##NAME = NUM, 

enum CmdNames
{
    #include "Commands.h"
};

#undef DEF_CMD

//-----------------------------------------------------------------------------

#endif