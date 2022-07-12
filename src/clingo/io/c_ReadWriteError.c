#include "clingo/io/c_ReadWriteError.h"

#include "clingo/io/cRecorder.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

static bool note_read_write_error( cRecorder rec[static 1], cError const* err )
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
      return recordf_c( rec, "unknown read write error code: %i", errd->errc );
   }

   return record_chars_c_( rec, msg );
}

cErrorType const C_ReadWriteError = {
   .desc = stringify_c_( C_ReadWriteError ),
   .note = &note_read_write_error
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool is_read_write_error_c( int errc )
{
   switch ( errc )
   {
      #define XMAP_C_( N, I, T ) case N: return true;
         cREAD_WRITE_ERROR_CODE_
      #undef XMAP_C_
   }
   return false;
};

bool push_read_write_error_c( cErrorStack es[static 1], int errc )
{
   cReadWriteErrorData d = { .errc=errc };
   return push_error_c( es, &C_ReadWriteError, &d, sizeof_c_( cReadWriteErrorData ) );
}