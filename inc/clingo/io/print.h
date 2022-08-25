#ifndef CLINGO_IO_PRINT_H
#define CLINGO_IO_PRINT_H

#include "clingo/io/jot.h"
#include "clingo/io/write.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************

*******************************************************************************/

#define printfn_c_( Prefix, RecSize, Func, ... )                               \
{                                                                              \
   cRecorder* Prefix##Recorder = &recorder_c_( RecSize );                      \
   Func( Prefix##Recorder, __VA_ARGS__ );                                      \
   print_recorded_c( Prefix##Recorder );                                       \
}

/**************************************/

#define pjot_c_( Prefix, RecSize, ... )                                        \
   printfn_c_( Prefix, RecSize, jot_c_, __VA_ARGS__ )

#define pjotln_c_( Prefix, RecSize, ... )                                      \
   printfn_c_( Prefix, RecSize, jotln_c_, __VA_ARGS__ )

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 print
*******************************************************************************/

#define print_c_( ... )                                                        \
   print_c( nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool print_c( int n, ... );

#define println_c_( ... )                                                 \
   println_c( nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool println_c( int n, ... );

#endif
