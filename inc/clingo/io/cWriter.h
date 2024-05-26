#ifndef CLINGO_IO_CWRITER_H
#define CLINGO_IO_CWRITER_H

#include "clingo/type/cBytes.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define do_write_c_( Writer, ... )                                             \
   (Writer).f( (Writer).i, nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )

typedef bool ( *c_write )( void* w, int n, ... );

struct cWriter
{
   void*   i;
   c_write f;
};
typedef struct cWriter cWriter;

#endif