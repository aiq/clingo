#include "clingo/lang/error.h"

#include <string.h>
#include "clingo/lang/func.h"
#include "clingo/lang/mem.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

cErrorType const C_ErrnoError = {
   .desc = stringify_c_( C_ErrnoError ),
   .note = &note_errno_error_c
};

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

int64_t error_depth_c( cError const* err )
{
   int64_t res = 0;
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

/*******************************************************************************
 note
*******************************************************************************/

bool note_error_c( cRecorder rec[static 1],
                   cError const* err )
{
   if ( err == NULL ) return true;
   
   bool res = err->type->note( rec, err );
   while ( res and err != NULL )
   {
      res &= record_chars_c_( rec, ": " );
      res &= err->type->note( rec, err );
   }
   return res;
}

/*******************************************************************************
 stack
*******************************************************************************/

int64_t count_errors_c( cErrorStack es[static 1] )
{
   return error_depth_c( es->err );
}

void drop_error_c( cErrorStack es[static 1] )
{
   if ( es->err == NULL ) return;

   void* mem = (void*)es->err;
   int64_t pos = es->mem - mem;
   es->space = es->space + pos;
   es->mem = mem;
   es->err = es->err->sub;
}

bool push_error_c( cErrorStack es[static 1],
                   cErrorType const type[static 1],
                   cErrorData const* data,
                   int64_t dataSize )
{
   dataSize = ( data != NULL ) ? dataSize
                               : 0;
   int64_t fullSize;
   if ( not iadd64_c( sizeof_c_( cError ), dataSize, &fullSize ) )
      return false;

   if ( es->space < fullSize )
      return false;

   cError* e = es->mem;
   e->type = type;
   e->sub = es->err;
   es->mem += sizeof_c_( cError );

   if ( data != NULL )
   {
      size_t size;
      int64_to_size_c( dataSize, &size );
      memcpy( es->mem, data, size );
      es->mem += dataSize;
   }

   es->space -= fullSize;
   es->err = e;

   return false;
}

void reset_error_stack_c( cErrorStack es[static 1] )
{
   if ( es->err == NULL ) return;

   cError const* err = es->err;
   while ( err->sub != NULL )
   {
      err = err->sub;
   }
   void* mem = (void*)err;
   int64_t pos = es->mem - mem;
   es->space = es->space + pos;
   es->mem = mem;
   es->err = NULL;
}

/*******************************************************************************

*******************************************************************************/

bool push_errno_error_c( cErrorStack es[static 1], int number )
{
   cErrnoErrorData d = { .number=number };
   return push_error_c( es, &C_ErrnoError, &d, sizeof_c_( cErrnoErrorData ) );
}

bool note_errno_error_c( cRecorder rec[static 1], cError const* err )
{
   cErrnoErrorData const* errd = get_error_data_c( err );
   char* errStr = strerror( errd->number );
   if ( errStr == NULL ) return false;

   return record_chars_c_( rec, errStr );
}