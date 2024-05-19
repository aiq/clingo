#include "clingo/io/cRecorder.h"

#include <stdarg.h>
#include <stdio.h>

#include "clingo/io/c_ImpExpError.h"
#include "clingo/type/uint64.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 mem
*******************************************************************************/

bool alloc_recorder_mem_c( cRecorder rec[static 1], int64_t size )
{
   must_exist_c_( rec );
   must_be_positive_c_( size );

   void* mem = alloc_c( size );
   if ( mem == NULL )
   {
      return false;
   }

   rec->pos = 0;
   rec->space = size;
   rec->mem = mem;

   return true;
}

bool realloc_recorder_mem_c( cRecorder rec[static 1], int64_t size )
{
   must_exist_c_( rec );

   void* mem = realloc_c( rec->mem - rec->pos, size );
   if ( mem == NULL )
   {
      return false;
   }

   rec->pos = min_c_( rec->pos, size );
   rec->space = size - rec->pos;
   rec->mem = mem + rec->pos;

   return true;
}

void free_recorder_mem_c( cRecorder rec[static 1] )
{
   reset_recorder_c( rec );
   free( rec->mem );
}

extern inline int64_t recorder_cap_c( cRecorder const rec[static 1] );

/*******************************************************************************

*******************************************************************************/

extern inline bool move_recorder_c( cRecorder rec[static 1], int64_t offset );
extern inline bool move_recorder_to_c( cRecorder rec[static 1], int64_t pos );
extern inline void reset_recorder_c( cRecorder rec[static 1] );

/*******************************************************************************
 error
*******************************************************************************/

extern inline bool set_recorder_error_c( cRecorder rec[static 1], int err );

extern inline int clear_recorder_error_c( cRecorder rec[static 1] );

/*******************************************************************************
 access
*******************************************************************************/

extern inline cBytes recorded_bytes_c( cRecorder const rec[static 1] );
extern inline cChars recorded_chars_c( cRecorder const rec[static 1] );
bool recorded_is_c( cRecorder const rec[static 1], char const cstr[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( cstr );

   return chars_is_c( recorded_chars_c( rec ), cstr );
}

extern inline cVarBytes recorded_var_bytes_c( cRecorder rec[static 1] );
extern inline cVarChars recorded_var_chars_c( cRecorder rec[static 1] );

/*******************************************************************************

*******************************************************************************/

extern inline bool record_mem_c( cRecorder rec[static 1],
                                 int64_t len,
                                 void const* mem );
extern inline bool record_bytes_c( cRecorder rec[static 1], cBytes bytes );
extern inline bool record_chars_c( cRecorder rec[static 1], cChars chars );

bool record_chars_slice_c( cRecorder rec[static 1],
                           cCharsSlice slice,
                           cChars sep )
{
   if ( is_empty_c_( slice ) ) return true;

   int64_t const strLen = count_chars_slice_c( slice );
   int64_t const sepLen = ( slice.s -1 ) * sep.s;
   int64_t const memLen = strLen + sepLen;
   if ( memLen > rec->space )
   {
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

   cChars const* itr = begin_c_( slice );
   record_chars_c( rec, *itr );
   ++itr;
   for ( ; itr < end_c_( slice ); ++itr )
   {
      record_chars_c( rec, sep );
      record_chars_c( rec, *itr );
   }

   return true;
}

extern inline bool record_cstr_c( cRecorder rec[static 1],
                                  char const str[static 1] );

bool record_pad_c( cRecorder rec[static 1], char c, int64_t n )
{
   if ( not in_range_c_( 0, n, rec->space ) ) return false;

   char* mem = rec->mem;
   times_c_( n, i )
   {
      mem[i] = c;
   }
   rec->pos += n;
   rec->space -= n;
   rec->mem += n;

   return true;
}

extern inline bool record_terminated_c( cRecorder rec[static 1],
                                        cChars chars );

/*******************************************************************************
 exrecord
*******************************************************************************/

extern inline bool exrecord_mem_c( cRecorder rec[static 1],
                                   int64_t len,
                                   void const* mem );
extern inline bool exrecord_bytes_c( cRecorder rec[static 1], cBytes bytes );
extern inline bool exrecord_chars_c( cRecorder rec[static 1], cChars chars );
extern inline bool exrecord_terminated_c( cRecorder rec[static 1],
                                          cChars chars );

/*******************************************************************************

*******************************************************************************/

#define RECORD_FUNC_IMPL_( Type, FuncName )                                    \
bool FuncName( cRecorder rec[static 1], Type val )                             \
{                                                                              \
   must_exist_c_( rec );                                                       \
                                                                               \
   int64_t const size = sizeof_c_( Type );                                     \
   if ( size > rec->space )                                                    \
   {                                                                           \
     return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );             \
   }                                                                           \
                                                                               \
   Type* ptr = rec->mem;                                                       \
   ptr[ 0 ] = val;                                                             \
   rec->pos += size;                                                           \
   rec->space -= size;                                                         \
   rec->mem += size;                                                           \
   return true;                                                                \
}


RECORD_FUNC_IMPL_( cByte,    record_byte_c )
RECORD_FUNC_IMPL_( char,     record_char_c )

bool record_rune_c( cRecorder rec[static 1], cRune r )
{
   must_exist_c_( rec );

   if ( not rune_is_valid_c( r ) )
   {
      return set_recorder_error_c( rec, c_NotAbleToRecordValue );
   }

   return record_mem_c( rec, rune_size_c( r ), r.c );
}

RECORD_FUNC_IMPL_( int8_t,   record_int8_c )
RECORD_FUNC_IMPL_( int16_t,  record_int16_c )
RECORD_FUNC_IMPL_( int32_t,  record_int32_c )
RECORD_FUNC_IMPL_( int64_t,  record_int64_c )

RECORD_FUNC_IMPL_( uint8_t,  record_uint8_c )
RECORD_FUNC_IMPL_( uint16_t, record_uint16_c )
RECORD_FUNC_IMPL_( uint32_t, record_uint32_c )
RECORD_FUNC_IMPL_( uint64_t, record_uint64_c )

RECORD_FUNC_IMPL_( float,    record_float_c )
RECORD_FUNC_IMPL_( double,   record_double_c )

/*******************************************************************************
util
*******************************************************************************/

void print_recorded_c( cRecorder rec[static 1] )
{
   cChars recorded = recorded_chars_c( rec );
   for_each_c_( char const*, c, recorded )
   {
      putchar( *c );
   }
}

void println_recorded_c( cRecorder rec[static 1] )
{
   print_recorded_c( rec );
   putchar( '\n' );
}

char* turn_into_cstr_c( cRecorder rec[static 1] )
{
   if ( recorder_cap_c( rec ) == 0 ) return NULL;

   if ( rec->space > 0 )
   {
      record_char_c( rec, '\0' );
   }
   else
   {
      char const* cstr = rec->mem;
      --cstr;
      if ( *cstr != '\0' ) return NULL;
   }

   reset_recorder_c( rec );
   return rec->mem;
}
