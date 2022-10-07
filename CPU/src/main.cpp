#include <stdio.h>

#include "cpu.h"

/*
push 1
push 2
add
div
*/

//-----------------------------------------------------------------------------

int main()
{
    FILE* file = fopen ("../a.code", "rb");

    if (file == NULL) printf ("File \"%s\" does not exist...\n", "" /*fileName*/);

    CPU cpu = {0};
    CpuCtor (&cpu);

    //CheckSignature (file);

    CpuGetCmdsArr  (&cpu, file);
    CpuCmdsHandler (&cpu);    
}

//-----------------------------------------------------------------------------