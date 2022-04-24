#ifndef CLINGO_IO_WRITE_H
#define CLINGO_IO_WRITE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

#define cWRITE_ERROR_                                                          \
   XMAP_C_( c_NotEnoughRecorderSpace, 1, "not enough recorder space" )         \
   XMAP_C_( c_ToLargeWriteFormat,     2, "to large write format string" )      \
   XMAP_C_( c_InvalidWriteFormat,     3, "invalid write format string" ) 

/**************************************/

#define XMAP_C_( N, I, T ) N = I,
enum c_WriteError { cWRITE_ERROR_ };
#undef XMAP_C_

typedef enum c_WriteError c_WriteError;

/**************************************/

typedef bool ( *c_write_va_arg )( cRecorder rec[static 1],
                                  va_list* list,
                                  cChars type,
                                  char const fmt[static 1] );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CLINGO_API
bool write_format_arg_c( cRecorder rec[static 1],
                         va_list* list,
                         cChars type,
                         char const fmt[static 1] );

/*******************************************************************************

*******************************************************************************/

#define write_c_( Rec, ... )                                                   \
   write_c( (Rec), write_format_arg_c, nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API
bool write_c( cRecorder rec[static 1],
              c_write_va_arg write_arg,
              int n,
              ... );

#define writeln_c_( Rec, ... )                                                 \
   writeln_c( (Rec), write_format_arg_c, nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API
bool writeln_c( cRecorder rec[static 1],
                c_write_va_arg write_arg,
                int n,
                ... );

/*******************************************************************************
 error
*******************************************************************************/

CLINGO_API
char const* write_error_msg_c( cRecorder rec[static 1] );

#endif
