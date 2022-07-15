#ifndef CLINGO_IO_C_READ_WRITE_ERROR_H
#define CLINGO_IO_C_READ_WRITE_ERROR_H

#include "clingo/apidecl.h"
#include "clingo/lang/error.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cREAD_WRITE_ERROR_CODE_                                                \
   XMAP_C_( c_NotAbleToReadValue,      1, "not able to read value" )           \
   XMAP_C_( c_NotAbleToScanValue,      2, "not able to scan value" )           \
   XMAP_C_( c_IncompleteValue,         3, "incomplete value" )                 \
   XMAP_C_( c_NotEnoughRecorderSpace,  4, "not enough recorder space" )        \
   XMAP_C_( c_ToLargeFormatString,     5, "to large format string" )           \
   XMAP_C_( c_InvalidFormatString,     6, "invalid format string" )

#define XMAP_C_( N, I, T ) N = I,
enum c_ReadWriteErrorCode { cREAD_WRITE_ERROR_CODE_ };
#undef XMAP_C_
typedef enum c_ReadWriteErrorCode c_ReadWriteErrorCode;

/*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_ReadWriteError;

struct cReadWriteErrorData
{
   int errc;
};
typedef struct cReadWriteErrorData cReadWriteErrorData;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CLINGO_API bool is_read_write_error_c( int errc );

CLINGO_API bool push_read_write_error_c( cErrorStack es[static 1], int errc );

#endif