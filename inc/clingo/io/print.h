#ifndef CLINGO_IO_PRINT_H
#define CLINGO_IO_PRINT_H

#include "clingo/io/jot.h"
#include "clingo/io/write.h"

/*******************************************************************************

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

/**************************************/

#define print_c_( Prefix, RecSize, ... )                                       \
   printfn_c_( Prefix, RecSize, write_c_, __VA_ARGS__ )

#define println_c_( Prefix, RecSize, ... )                                     \
   printfn_c_( Prefix, RecSize, writeln_c_, __VA_ARGS__ )

#endif
