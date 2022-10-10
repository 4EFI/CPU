#include <stdio.h>

#include "cpu.h"

//-----------------------------------------------------------------------------

int main()
{
    FILE* file = fopen ("../Examples/number_squares.code", "rb");

    if (file == NULL) printf ("File \"%s\" does not exist...\n", "" /*fileName*/);

    CPU cpu = {0};
    CpuCtor (&cpu);

    //CheckCompatibility (file);

    CpuGetCmdsArr  (&cpu, file);
    CpuCmdsHandler (&cpu);    
}

//-----------------------------------------------------------------------------