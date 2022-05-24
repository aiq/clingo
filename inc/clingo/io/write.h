#ifndef CLINGO_IO_WRITE_H
#define CLINGO_IO_WRITE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/lang/error.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

#define cWRITE_ERROR_CODE_                                                     \
   XMAP_C_( c_NotEnoughRecorderSpace, 1, "not enough recorder space" )         \
   XMAP_C_( c_ToLargeWriteFormat,     2, "to large write format string" )      \
   XMAP_C_( c_InvalidWriteFormat,     3, "invalid write format string" ) 

/**************************************/

#define XMAP_C_( N, I, T ) N = I,
enum c_WriteErrorCode { cWRITE_ERROR_CODE_ };
#undef XMAP_C_
typedef enum c_WriteErrorCode c_WriteErrorCode;

/*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_WriteError;

struct cWriteErrorData
{
   int errc;
};
typedef struct cWriteErrorData cWriteErrorData;
                
/*******************************************************************************

*******************************************************************************/

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
bool push_write_error_c( cErrorStack es[static 1], cRecorder rec[static 1] );

CLINGO_API
bool note_write_error_c( cRecorder rec[static 1], cError const* err );

#endif
