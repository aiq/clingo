#include "clingo/lang/error.h"

#include <string.h>
#include "clingo/lang/func.h"
#include "clingo/lang/mem.h"

cErrorType const C_ErrnoError = {
   .desc = stringify_c_( C_ErrnoError ),
   .note = &note_errno_error_c
};

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

uint32_t error_depth_c( cError const err[static 1] )
{
   uint32_t res = 0;

   while ( err )
   {
      res += 1;
      err = err->sub;
   }

   return res;
}

cErrorData const* get_error_data_c( cError const* err )
{
   must_exist_c_( err );

   return err + sizeof( cError );
}

int fprint_error_c( FILE* output, cError const err[static 1] )
{
   int res = 0;
/*
   while ( err )
   {
      cError const* curr = err;
      err = curr->details;
      char const* fmtStr = err ? "%s: "
                               : "%s";

      int tmpRes = fprintf( output, fmtStr, curr->msg );
      if ( tmpRes < 0 )
      {
         return tmpRes;
      }
      res += tmpRes;
   }
*/
   return res;
}

extern inline int print_error_c( cError const err[static 1] );

void reset_error_c( cError err[static 1] )
{
   /*
   while ( err )
   {
      cError* curr = err;
      err = curr->details;

      curr->code = cNoError_;
      curr->msg = "";
      curr->details = NULL;
   }
   */
}

/*******************************************************************************

*******************************************************************************/

bool push_error_c( cErrorStack stack[static 1],
                   cErrorType const type[static 1],
                   cErrorData const* data,
                   int64_t dataSize )
{
   dataSize = ( data != NULL ) ? dataSize
                               : 0;
   int64_t fullSize;
   if ( not iadd64_c( sizeof_c_( cError ), dataSize, &fullSize ) )
      return false;

   if ( stack->space < fullSize )
      return false;

   cError* e = stack->mem;
   e->type = type;
   e->sub = stack->err;
   stack->mem += sizeof_c_( cError );

   if ( data != NULL )
   {
      size_t size;
      int64_to_size_c( dataSize, &size );
      memcpy( stack->mem, data, size );
      stack->mem += dataSize;
   }

   stack->space -= fullSize;
   stack->err = e;

   return true;
}

bool note_error_c( cErrorNotepad notepad[static 1],
                   cError const err[static 1] )
{
   return false;
}

/*******************************************************************************

*******************************************************************************/

bool push_errno_error_c( cErrorStack stack[static 1], int number )
{
   cErrnoErrorData d = { .number=number };
   return push_error_c( stack, &C_ErrnoError, &d, sizeof( cErrnoErrorData ) );
}

bool note_errno_error_c( cErrorNotepad notepad[static 1], cError const* err )
{
   cErrnoErrorData const* errData = get_error_data_c( err );
   char* errStr = strerror( errData->number );
   if ( errStr == NULL ) return false;

   size_t lenSize = strlen( errStr );
   int64_t len = 0;
   if ( not size_to_int64_c( lenSize, &len ) ) return false;

   if ( len > notepad->space ) return false;

   memmove( notepad->mem, errStr, lenSize );
   return true;
}