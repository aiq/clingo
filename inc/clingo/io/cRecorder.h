#ifndef CLINGO_IO_CRECORDER_H
#define CLINGO_IO_CRECORDER_H

#include <stdint.h>
#include <stdio.h>

#include "clingo/apidecl.h"
#include "clingo/io/cOutput.h"
#include "clingo/io/cWriter.h"
#include "clingo/lang/mem.h"
#include "clingo/type/cBytes.h"
#include "clingo/type/cChars.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/cRune.h"
#include "clingo/type/int64.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cRECORDER_ERROR_CODE_                                                  \
   XMAP_C_( c_NotEnughRecorderSpace, 1, "not enough recorder space " )         \
   XMAP_C_( c_NotAbleIncreaseRecorderSpace, 2, "not able to increase recorder space") \
   XMAP_C_( c_ToLargeWriteFormat, 3, "to large write format" ) \
   XMAP_C_( c_InvalidWriteFormat, 4, "invalid write format" )

#define XMAP_C_( N, I, T ) N = I,
enum c_RecorderErrorCode { cRECORDER_ERROR_CODE_ };
#undef XMAP_C_
typedef enum c_RecorderErrorCode c_RecorderErrorCode;

struct cRecorder
{
   int64_t pos;
   int64_t space;
   void*   mem;
   bool    dyn;
   int     err;
};
typedef struct cRecorder cRecorder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define dyn_heap_recorder_c_( Size )                                           \
(                                                                              \
   (cRecorder)                                                                 \
   { .pos=0, .space=(Size), .mem=alloc_c(Size), .dyn=true, .err=0 }            \
)

#define fix_heap_recorder_c_( Size )                                           \
(                                                                              \
   (cRecorder)                                                                 \
   { .pos=0, .space=(Size), .mem=alloc_c(Size), .dyn=false, .err=0 }           \
)

#define make_dyn_recorder_c_( Size, Memory )                                   \
(                                                                              \
   (cRecorder)                                                                 \
   { .pos=0, .space=(Size), .mem=(Memory), .dyn=true, .err=0 }                 \
)

#define make_fix_recorder_c_( Size, Memory )                                   \
(                                                                              \
   (cRecorder)                                                                 \
   { .pos=0, .space=(Size), .mem=(Memory), .dyn=false, .err=0 }                \
)

#define null_recorder_c_()                                                     \
(                                                                              \
   (cRecorder){ .pos=0, .space=0, .mem=NULL, .dyn=false, .err=0 }              \
)

#define recorder_c_( Size )                                                    \
(                                                                              \
   (cRecorder)                                                                 \
   { .pos=0, .space=(Size), .mem=stack_mem_c_( Size ), .dyn=false, .err=0 }    \
)

/*******************************************************************************
 error
*******************************************************************************/

CLINGO_API inline bool set_recorder_error_c( cRecorder rec[static 1], int err )
{
   rec->err = err;
   return false;
}

CLINGO_API inline int clear_recorder_error_c( cRecorder rec[static 1] )
{
   int res = rec->err;
   rec->err = 0;
   return res;
}

/*******************************************************************************
 func structs
*******************************************************************************/

CLINGO_API cOutput recorder_as_output_c( cRecorder rec[static 1] );

CLINGO_API cPen recorder_as_pen_c( cRecorder rec[static 1] );

/*******************************************************************************
 mem
*******************************************************************************/

CLINGO_API
bool alloc_recorder_mem_c( cRecorder rec[static 1], int64_t size );
CLINGO_API
bool realloc_recorder_mem_c( cRecorder rec[static 1], int64_t size );
CLINGO_API
void free_recorder_mem_c( cRecorder rec[static 1] );

CLINGO_API
inline int64_t recorder_cap_c( cRecorder const rec[static 1] )
{
   must_exist_c_( rec );

   return rec->pos + rec->space;
}

CLINGO_API inline bool ensure_recorder_space_c( cRecorder rec[static 1],
                                                int64_t size )
{
   if ( rec->space >= size ) return true;

   if ( not rec->dyn )
      return set_recorder_error_c( rec, c_NotEnughRecorderSpace );

   size = imax64_c( recorder_cap_c( rec ), size );
   if ( not imul64_c( size, 2, &size ) )
      return false;

   if ( not realloc_recorder_mem_c( rec, size ) )
      return set_recorder_error_c( rec, c_NotAbleIncreaseRecorderSpace );

   return true;
}

/*******************************************************************************
 move
*******************************************************************************/
CLINGO_API
inline bool move_recorder_c( cRecorder rec[static 1], int64_t offset )
{
   must_exist_c_( rec );

   int64_t newPos = rec->pos + offset;
   int64_t newSpace = rec->space - offset;

   if ( newPos < 0 or newSpace < 0 )
   {
      return false;
   }

   rec->pos = newPos;
   rec->space = newSpace;
   rec->mem += offset;
   return true;
}

CLINGO_API
inline bool move_recorder_to_c( cRecorder rec[static 1], int64_t pos )
{
   must_exist_c_( rec );
   int64_t offset = pos - rec->pos;
   return move_recorder_c( rec, offset );
}

CLINGO_API
inline void reset_recorder_c( cRecorder rec[static 1] )
{
   must_exist_c_( rec );
   move_recorder_to_c( rec, 0 );
}

/*******************************************************************************
 recorded
*******************************************************************************/
CLINGO_API
inline cBytes recorded_bytes_c( cRecorder const rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return (cBytes)empty_c_();
   }
   const cByte* ptr = rec->mem;
   return (cBytes){ rec->pos, ptr - rec->pos };
}

CLINGO_API
inline cChars recorded_chars_c( cRecorder const rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return (cChars)empty_c_();
   }
   const char* ptr = rec->mem;
   return (cChars){ rec->pos, ptr - rec->pos };
}

CLINGO_API
bool recorded_is_c( cRecorder const[static 1], char const cstr[static 1] );

CLINGO_API
inline cVarBytes recorded_var_bytes_c( cRecorder rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return (cVarBytes)empty_c_();
   }
   cByte* ptr = rec->mem;
   return (cVarBytes){ rec->pos, ptr - rec->pos };
}

CLINGO_API
inline cVarChars recorded_var_chars_c( cRecorder rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return (cVarChars)empty_c_();
   }
   char* ptr = rec->mem;
   return (cVarChars){ rec->pos, ptr - rec->pos };
}

/*******************************************************************************
 record
*******************************************************************************/
CLINGO_API
inline bool record_mem_c( cRecorder rec[static 1],
                          int64_t len,
                          void const* mem )
{
   if ( not ensure_recorder_space_c( rec, len ) ) return false;

   size_t size;
   if ( not int64_to_size_c( len, &size ) ) return false;

   memmove( rec->mem, mem, size );
   rec->pos += len;
   rec->space -= len;
   rec->mem += len;

   return true;
}

CLINGO_API
inline bool record_bytes_c( cRecorder rec[static 1], cBytes slice )
{
   return record_mem_c( rec, slice.s, slice.v );
}

#define record_chars_c_( Rec, Cstr )                                           \
   record_chars_c( (Rec), c_c( Cstr ) )
CLINGO_API
inline bool record_chars_c( cRecorder rec[static 1], cChars chars )
{
   return record_mem_c( rec, chars.s, chars.v );
}

#define record_chars_slice_c_( Rec, Slice, Sep )                               \
   record_chars_slice_c( (Rec), (Slice), c_c( Sep ) )
CLINGO_API
bool record_chars_slice_c( cRecorder rec[static 1],
                           cCharsSlice slice,
                           cChars sep );

CLINGO_API
inline bool record_cstr_c( cRecorder rec[static 1],
                           char const str[static 1] )
{
   int64_t size = 0;
   if ( uint64_to_int64_c( strlen( str ), &size ) )
   {
      return record_mem_c( rec, size + 1, str );
   }

   return false;
}

CLINGO_API
bool record_pad_c( cRecorder rec[static 1], char c, int64_t n );

CLINGO_API
inline bool record_terminated_c( cRecorder rec[static 1],
                                 cChars chars )
{
   if ( not ensure_recorder_space_c( rec, chars.s+1 ) ) return false;

   record_mem_c( rec, chars.s, chars.v );
   char* tmp = rec->mem;
   *tmp = '\0';

   return true;
}

/*******************************************************************************
 record type
*******************************************************************************/

CLINGO_API bool record_byte_c( cRecorder rec[static 1], cByte b );
CLINGO_API bool record_char_c( cRecorder rec[static 1], char c );
CLINGO_API bool record_rune_c( cRecorder rec[static 1], cRune r );

CLINGO_API bool record_int8_c( cRecorder rec[static 1], int8_t i8 );
CLINGO_API bool record_int16_c( cRecorder rec[static 1], int16_t i16 );
CLINGO_API bool record_int32_c( cRecorder rec[static 1], int32_t i32 );
CLINGO_API bool record_int64_c( cRecorder rec[static 1], int64_t i64 );

CLINGO_API bool record_uint8_c( cRecorder rec[static 1], uint8_t u8 );
CLINGO_API bool record_uint16_c( cRecorder rec[static 1], uint16_t u16 );
CLINGO_API bool record_uint32_c( cRecorder rec[static 1], uint32_t u32 );
CLINGO_API bool record_uint64_c( cRecorder rec[static 1], uint64_t u64 );

CLINGO_API bool record_float_c( cRecorder rec[static 1], float f );
CLINGO_API bool record_double_c( cRecorder rec[static 1], double d );

/*******************************************************************************
 util
*******************************************************************************/

CLINGO_API void print_recorded_c( cRecorder rec[static 1] );

#define print_scope_c_( Rec, Size )                                            \
for (                                                                          \
   cRecorder* Rec = &recorder_c_(Size);                                        \
   Rec != NULL;                                                                \
   print_recorded_c( Rec ), Rec = NULL                                         \
)

CLINGO_API void println_recorded_c( cRecorder rec[static 1] );

#define println_scope_c_( Rec, Size )                                          \
for (                                                                          \
   cRecorder* Rec = &recorder_c_( Size );                                      \
   Rec != NULL;                                                                \
   println_recorded_c( Rec ), Rec = NULL                                       \
)

CLINGO_API char* turn_into_cstr_c( cRecorder rec[static 1] );

#endif
