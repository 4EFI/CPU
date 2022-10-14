#include <stdio.h>

#include "asm.h"
#include "LOG.h"
#include "OptionsCmdLine.h"

int SetFileOut( FILE** fileOut );

//-----------------------------------------------------------------------------

int main( int argc, const char* argv[] )
{
    FILE* fileIn  = NULL;
    FILE* fileOut = NULL;

    // Set input file 
    if( argc > 1 ) fileIn = fopen( argv[1], "r" );

    // Function that open a file in progress... :)))
    if( !fileIn ) 
    {
        printf( "Asm file opening error...\n" );
        return -1;
    }

    START_OPT_HANDLER( argc, argv )
    {
        OPT_HANDLER( "-o", SetFileOut( &fileOut ); )    
    }

    if( !fileOut ) 
    {
        fileOut = fopen( "a.code", "wb" );
    }


    ASM asm_s = { 0 };
    AsmCtor( &asm_s );

    AsmGetCmds( &asm_s, fileIn );

    for (int i = 0; i < 2; i++) 
    {
        if( AsmMakeArrCmds( &asm_s ) == -1) return -1;
    }

    AsmMakeBinFile( &asm_s, fileOut );

    fclose( fileIn );
    fclose( fileOut );
}

//-----------------------------------------------------------------------------

int SetFileOut( FILE** fileOut )
{
    if( __CUR_OPT__ < __NUM_OPTIONS__ - 1 ) 
    {
        *fileOut = fopen( Argv[__CUR_OPT__ + 1], "wb" );
    }

    return 1;
}

//-----------------------------------------------------------------------------