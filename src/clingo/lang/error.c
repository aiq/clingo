#include "clingo/lang/error.h"

#include <string.h>
#include "clingo/io/write.h"
#include "clingo/lang/error_type.h"
#include "clingo/lang/func.h"
#include "clingo/lang/mem.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

SINGLE_ERROR_TYPE_C_(
   C_InvalidInputError,
   note_invalid_input_error,
   "invalid input"
)

SINGLE_ERROR_TYPE_C_(
   C_NotEnoughBufferError,
   note_not_enough_buffer_error,
   "not enough buffer space"
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 error
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

   return err + 1;
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
