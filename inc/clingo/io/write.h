#ifndef CLINGO_IO_WRITE_H
#define CLINGO_IO_WRITE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/io/cTape.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 write
*******************************************************************************/

CLINGO_API bool write_list_c( cRecorder rec[static 1], int n, va_list list );

#define write_c_( Rec, ... )                                                   \
   write_c( (Rec), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool write_c( cRecorder rec[static 1], int n, ... );

/*******************************************************************************
 writeln
*******************************************************************************/

CLINGO_API bool writeln_list_c( cRecorder rec[static 1], int n, va_list list );

#define writeln_c_( Rec, ... )                                                 \
   writeln_c( (Rec), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool writeln_c( cRecorder rec[static 1], int n, ... );

#endif
