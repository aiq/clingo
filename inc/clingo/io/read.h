#ifndef CLINGO_IO_READ_H
#define CLINGO_IO_READ_H

#include "clingo/apidecl.h"
#include "clingo/io/cScanner.h"
#include "clingo/io/write.h"
#include "clingo/lang/error.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cREAD_ERROR_CODE_                                                      \
   XMAP_C_( c_NotAbleToReadValue, 1, "not able to read value" )                \
   XMAP_C_( c_ToLargeReadFormat,  2, "to large read format string" )           \
   XMAP_C_( c_InvalidReadFormat,  3, "invalid read format string" )

/**************************************/

#define XMAP_C_( N, I, T ) N = I,
enum c_ReadErrorCode { cREAD_ERROR_CODE_ };
#undef XMAP_C_
typedef enum c_ReadErrorCode c_ReadErrorCode;
                
/*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_ReadScannerError;

struct cReadErrorData
{
   int errc;
};
typedef struct cReadErrorData cReadErrorData;
                
/*******************************************************************************

*******************************************************************************/

typedef bool ( *c_read_va_arg )( cScanner sca[static 1],
                                 void* val,
                                 cChars type,
                                 char const fmt[static 1] );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CLINGO_API
bool read_format_arg_c( cScanner sca[static 1],
                        void* val,
                        cChars type,
                        char const fmt[static 1] );

#define read_c_( Sca, ... )                                                    \
   read_c( (Sca), read_format_arg_c, nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API
bool read_c( cScanner sca[static 1],
             c_read_va_arg read_arg,
             int n,
             ... );
                
/*******************************************************************************
 error
*******************************************************************************/

CLINGO_API
bool push_read_scanner_error_c( cErrorStack es[static 1], cScanner sca[static 1] );

#endif
