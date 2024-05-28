#ifndef CLINGO_IO_COUTPUT_H
#define CLINGO_IO_COUTPUT_H

#include "clingo/type/cBytes.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define output_c_( Output, Bytes )                                             \
   (Output).f( (Output).i, (Bytes) )

typedef bool ( *c_output )( void* o, cBytes data );

struct cOutput
{
   void*    i;
   c_output f;
};
typedef struct cOutput cOutput;

#endif