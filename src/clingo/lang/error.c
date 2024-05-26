#include "clingo/lang/error.h"

#include <string.h>
#include "clingo/io/write.h"
#include "clingo/lang/func.h"
#include "clingo/lang/mem.h"
#include "clingo/io/print.h"

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

 bool note_error_c( cWriter w, cError const* err )
 {
   if ( err == NULL ) return do_write_c_( w, "no error" );

   bool res = err->type->note( w, err );
   err = err->sub;
   while ( res and err != NULL )
   {
      res &= do_write_c_( w, ": " );
      res &= err->type->note( w, err );
      err = err->sub;
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
 error types
*******************************************************************************/

static bool note_errno_error( cWriter w, cError const* err )
{
   must_be_c_( err->type == &C_ErrnoError );
   cErrnoErrorData const* errd = get_error_data_c( err );
   char* errStr = strerror( errd->number );
   if ( errStr == NULL ) return false;

   return do_write_c_( w, "{s}", errStr );
}
cErrorType const C_ErrnoError = {
   .desc = stringify_c_( C_ErrnoError ),
   .note = &note_errno_error
};

bool push_errno_error_c( cErrorStack es[static 1], int number )
{
   cErrnoErrorData d = { .number=number };
   return push_error_c( es, &C_ErrnoError, &d, sizeof_c_( cErrnoErrorData ) );
}

/******************************************************************************/

static bool note_lit_error( cWriter w, cError const* err )
{
   must_be_c_( err->type == &C_LitError );
   cLitErrorData const* errd = get_error_data_c( err );
   return do_write_c_( w, "{s}", errd->str );
}
cErrorType const C_LitError = {
   .desc = stringify_c_( C_LitError ),
   .note = &note_lit_error
};

bool push_lit_error_c( cErrorStack es[static 1], char const str[static 1] )
{
   cLitErrorData d = { .str=str };
   return push_error_c( es, &C_LitError, &d, sizeof_c_( cLitErrorData ) );
}

/******************************************************************************/

static bool note_text_error( cWriter w, cError const* err )
{
   must_be_c_( err->type == &C_TextError );
   cTextErrorData const* errd = get_error_data_c( err );
   return do_write_c_( w, "{s}", errd->str );
}
cErrorType const C_TextError = {
   .desc = stringify_c_( C_TextError ),
   .note = &note_text_error
};

bool push_text_error_c( cErrorStack es[static 1], int n, ... )
{
   cRecorder* rec = &make_fix_recorder_c_( es->space, es->mem );
   va_list list;
   va_start( list, n );
   bool res = write_list_c( rec, n, list );
   va_end( list );
   if ( res == false ) return false;

   if ( not record_char_c( rec, '\0' ) ) return false;

   es->space = rec->space;
   es->mem = rec->mem;
   reset_recorder_c( rec );
   cTextErrorData d = { .str=rec->mem };
   return push_error_c( es, &C_TextError, &d, sizeof_c_( cTextErrorData ) );
}