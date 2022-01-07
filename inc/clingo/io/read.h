#ifndef CLINGO_IO_READ_H
#define CLINGO_IO_READ_H

#include "clingo/io/cScanner.h"
#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cREAD_ERROR_                                                           \
   XMAP_C_( c_NotAbleToReadValue, 1, "not able to read value" )                \
   XMAP_C_( c_ToLargeReadFormat,  2, "to large read format string" )           \
   XMAP_C_( c_InvalidReadFormat,  3, "invalid read format string" )

/**************************************/

#define XMAP_C_( N, I, T ) N = I,
enum c_ReadError { cREAD_ERROR_ };
#undef XMAP_C_

typedef enum c_ReadError c_ReadError;

/**************************************/

typedef int64_t ( *c_read_va_arg )( cScanner sca[static 1],
                                    void* val,
                                    cChars type,
                                    char const fmt[static 1] );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

int64_t read_format_arg_c( cScanner sca[static 1],
                           void* val,
                           cChars type,
                           char const fmt[static 1] );

#define read_c_( Sca, ... )                                                    \
   read_c( (Sca), read_format_arg_c, nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
int64_t read_c( cScanner sca[static 1],
                c_read_va_arg read_arg,
                int n,
                ... );
                
/*******************************************************************************

*******************************************************************************/

char const* scan_error_msg_c( cScanner sca[static 1] );

#endif
