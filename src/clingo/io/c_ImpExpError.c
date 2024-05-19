#include "clingo/io/c_ImpExpError.h"

#include "clingo/io/cRecorder.h"
#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

static bool note_imp_exp_error( cRecorder rec[static 1], cError const* err )
{
   cReadWriteErrorData const* errd = get_error_data_c( err );
   char const* msg = NULL;
   switch ( errd->errc )
   {
      #define XMAP_C_( N, I, T ) case N: msg = T;
         cREAD_WRITE_ERROR_CODE_
      #undef XMAP_C_
   }
   if ( msg == NULL )
   {
      return write_c_( rec, "unknown read write error code: {i64}", errd->errc );
   }

   return record_chars_c_( rec, msg );
}

cErrorType const C_ImpExpError = {
   .desc = stringify_c_( C_ImpExpError ),
   .note = &note_imp_exp_error
};

QUOTE_LIT_ERROR_TYPE_C_(
   C_ImportError,
   note_import_error,
   "not able to import {s:q}",
   push_import_error_c
)

QUOTE_LIT_ERROR_TYPE_C_(
   C_ExportError,
   note_export_error,
   "not able to export {s:q}",
   push_export_error_c
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool is_imp_exp_error_c( int errc )
{
   switch ( errc )
   {
      #define XMAP_C_( N, I, T ) case N: return true;
         cREAD_WRITE_ERROR_CODE_
      #undef XMAP_C_
   }
   return false;
};

bool push_imp_exp_error_c( cErrorStack es[static 1], int errc )
{
   cReadWriteErrorData d = { .errc=errc };
   return push_error_c( es, &C_ImpExpError, &d, sizeof_c_( cReadWriteErrorData ) );
}