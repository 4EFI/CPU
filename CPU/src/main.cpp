#include <stdio.h>

#include "cpu.h"

//-----------------------------------------------------------------------------

int main(int argc, const char* argv[])
{
    FILE* file = NULL;

    if (argc > 1) file = fopen (argv[1], "rb");

    if (!file) 
    {
        printf ("Cpu file opening error...\n");
        return -1;
    }

    if (file == NULL) printf ("File \"%s\" does not exist...\n", "" /*fileName*/);

    CPU cpu = {0};
    CpuCtor (&cpu);

    //CheckCompatibility (file);

    CpuGetCmdsArr  (&cpu, file);
    CpuCmdsHandler (&cpu);    
}

//-----------------------------------------------------------------------------