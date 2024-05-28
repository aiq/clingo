#ifndef CLINGO_IO_CPEN_H
#define CLINGO_IO_CPEN_H

#include "clingo/type/cBytes.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define pen_c_( Pen, ... )                                                     \
   (Pen).f( (Pen).i, nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )

typedef bool ( *c_pen )( void* w, int n, ... );

struct cPen
{
   void* i;
   c_pen f;
};
typedef struct cPen cPen;

#endif