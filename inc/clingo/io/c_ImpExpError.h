#ifndef CLINGO_IO_CIMPEXPERROR_H
#define CLINGO_IO_CIMPEXPERROR_H

#include "clingo/apidecl.h"
#include "clingo/lang/error.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cREAD_WRITE_ERROR_CODE_                                                \
   XMAP_C_( c_NotAbleToRecordValue,    1, "not able to record value" )         \
   XMAP_C_( c_NotAbleToScanValue,      2, "not able to scan value" )           \
   XMAP_C_( c_NotAbleToReadValue,      3, "not able to read value" )           \
   XMAP_C_( c_NotAbleToWriteValue,     4, "not able to write value" )          \
   XMAP_C_( c_IncompleteValue,         5, "incomplete value" )                 \
   XMAP_C_( c_NotEnoughRecorderSpace,  6, "not enough recorder space" )        \
   XMAP_C_( c_ToLargeFormatString,     7, "to large format string" )           \
   XMAP_C_( c_InvalidFormatString,     8, "invalid format string" )            \
   XMAP_C_( c_InternalAllocError,      9, "allocation error" )                 \
   XMAP_C_( c_CustomImpExpError,      10, "custom import/export error" )

#define XMAP_C_( N, I, T ) N = I,
enum c_ImpExpErrorCode { cREAD_WRITE_ERROR_CODE_ };
#undef XMAP_C_
typedef enum c_ImpExpErrorCode c_ImpExpErrorCode;

/*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_ImpExpError;

CLINGO_API extern cErrorType const C_ImportError;

CLINGO_API extern cErrorType const C_ExportError;

struct cReadWriteErrorData
{
   int errc;
};
typedef struct cReadWriteErrorData cReadWriteErrorData;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CLINGO_API bool is_imp_exp_error_c( int errc );

CLINGO_API bool push_imp_exp_error_c( cErrorStack es[static 1], int errc );

CLINGO_API bool push_import_error_c( cErrorStack es[static 1],
                                     char const name[static 1] );

CLINGO_API bool push_export_error_c( cErrorStack es[static 1],
                                     char const name[static 1] );

#endif