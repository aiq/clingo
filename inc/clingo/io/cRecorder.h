#ifndef CLINGO_IO_CRECORDER_H
#define CLINGO_IO_CRECORDER_H

#include <stdint.h>

#include "clingo/lang/error.h"
#include "clingo/lang/mem.h"
#include "clingo/type/cBytes.h"
#include "clingo/type/cChars.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/cRune.h"
#include "clingo/type/int64.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cRecorder
{
   int64_t pos;
   int64_t space;
   void*   mem;
   int     err;
};
typedef struct cRecorder cRecorder;

struct cRecordMarker
{
   cRecorder* x;
   int64_t    startPos;
   int64_t    lastPos;
};
typedef struct cRecordMarker cRecordMarker;

/*******************************************************************************
******************************************************** Code Generation Macros
*******************************************************************************/

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define heap_recorder_c_( Size )                                               \
(                                                                              \
   (cRecorder){                                                                \
      .pos=0,                                                                  \
      .space=(Size),                                                           \
      .mem=alloc_c( Size )                                                     \
   }                                                                           \
)

#define make_recorder_c_( Size, Memory )                                       \
(                                                                              \
   (cRecorder){                                                                \
      .pos=0,                                                                  \
      .space=(Size),                                                           \
      .mem=(Memory)                                                            \
   }                                                                           \
)

#define null_recorder_c_()                                                     \
(                                                                              \
   (cRecorder){                                                                \
      .pos=0,                                                                  \
      .space=0,                                                                \
      .mem=NULL                                                                \
   }                                                                           \
)

#define recorder_c_( Size )                                                    \
(                                                                              \
   (cRecorder){                                                                \
      .pos=0,                                                                  \
      .space=(Size),                                                           \
      .mem=(cByte[]){ [(Size)-1]=0 }                                           \
   }                                                                           \
)

/*******************************************************************************
 mem
*******************************************************************************/

bool alloc_recorder_mem_c( cRecorder rec[static 1], int64_t size );
bool realloc_recorder_mem_c( cRecorder rec[static 1], int64_t size );
void free_recorder_mem_c( cRecorder rec[static 1] );

inline int64_t recorder_cap_c( cRecorder const rec[static 1] )
{
   must_exist_c_( rec );

   return rec->pos + rec->space;
}

/*******************************************************************************
 move
*******************************************************************************/

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

inline bool move_recorder_to_c( cRecorder rec[static 1], int64_t pos )
{
   must_exist_c_( rec );

   int64_t offset = pos - rec->pos;
   return move_recorder_c( rec, offset );
}

inline void reset_recorder_c( cRecorder rec[static 1] )
{
   must_exist_c_( rec );

   move_recorder_to_c( rec, 0 );
}

/*******************************************************************************
 error
*******************************************************************************/

inline bool record_error_c( cRecorder rec[static 1], int err )
{
   rec->err = err;
   return false;
}

/*******************************************************************************
 recorded
*******************************************************************************/

inline cBytes recorded_bytes_c( cRecorder const rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return empty_bytes_c();
   }
   const cByte* ptr = rec->mem;
   return bytes_c( rec->pos, ptr - rec->pos );
}

inline cChars recorded_chars_c( cRecorder const rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return empty_chars_c();
   }
   const char* ptr = rec->mem;
   return chars_c( rec->pos, ptr - rec->pos );
}

bool recorded_is_c( cRecorder const[static 1], char const cstr[static 1] );

inline cVarBytes recorded_var_bytes_c( cRecorder rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return empty_var_bytes_c();
   }
   cByte* ptr = rec->mem;
   return var_bytes_c( rec->pos, ptr - rec->pos );
}

inline cVarChars recorded_var_chars_c( cRecorder rec[static 1] )
{
   must_exist_c_( rec );
   if ( rec->pos == 0 )
   {
      return empty_var_chars_c();
   }
   char* ptr = rec->mem;
   return var_chars_c( rec->pos, ptr - rec->pos );
}

/*******************************************************************************
 record
*******************************************************************************/

inline bool record_mem_c( cRecorder rec[static 1],
                          void const* mem,
                          int64_t len )
{
   if ( len > rec->space ) return false;

   size_t size;
   if ( not int64_to_size_c( len, &size ) ) return false;

   memcpy( rec->mem, mem, size );
   rec->pos += len;
   rec->space -= len;
   rec->mem += len;

   return true;
}

inline bool record_bytes_c( cRecorder rec[static 1], cBytes slice )
{
   return record_mem_c( rec, slice.v, slice.s );
}

#define record_chars_c_( Rec, Cstr )                                           \
   record_chars_c( (Rec), c_c( Cstr ) )
inline bool record_chars_c( cRecorder rec[static 1], cChars chars )
{
   return record_mem_c( rec, chars.v, chars.s );
}

#define record_chars_slice_c_( Rec, Slice, Sep )                               \
   record_chars_slice_c( (Rec), (Slice), c_c( Sep ) )
bool record_chars_slice_c( cRecorder rec[static 1],
                           cCharsSlice slice,
                           cChars sep );

inline bool record_cstr_c( cRecorder rec[static 1],
                           char const str[static 1] )
{
   int64_t size = 0;
   if ( uint64_to_int64_c( strlen( str ), &size ) )
   {
      return record_mem_c( rec, str, size + 1 );
   }

   return false;
}

bool record_endl_c( cRecorder rec[static 1] );

bool record_ends_c( cRecorder rec[static 1] );

bool record_pad_c( cRecorder rec[static 1], char c, int64_t n );

bool recordf_c( cRecorder rec[static 1], char const format[static 1], ... );

/*******************************************************************************
 record type
*******************************************************************************/

bool record_byte_c( cRecorder rec[static 1], cByte b );
bool record_char_c( cRecorder rec[static 1], char c );
bool record_rune_c( cRecorder rec[static 1], cRune r );

bool record_int8_c( cRecorder rec[static 1], int8_t i8 );
bool record_int16_c( cRecorder rec[static 1], int16_t i16 );
bool record_int32_c( cRecorder rec[static 1], int32_t i32 );
bool record_int64_c( cRecorder rec[static 1], int64_t i64 );

bool record_uint8_c( cRecorder rec[static 1], uint8_t u8 );
bool record_uint16_c( cRecorder rec[static 1], uint16_t u16 );
bool record_uint32_c( cRecorder rec[static 1], uint32_t u32 );
bool record_uint64_c( cRecorder rec[static 1], uint64_t u64 );

bool record_float_c( cRecorder rec[static 1], float f );
bool record_double_c( cRecorder rec[static 1], double d );

/*******************************************************************************
 marker
*******************************************************************************/

#define record_marker_c_( Rec )                                                \
(                                                                              \
   (cRecordMarker){ .x=(Rec), .startPos=(Rec)->pos, .lastPos=(Rec)->pos }      \
)

inline int64_t trace_full_record_c( cRecordMarker rm[static 1] )
{
   must_exist_c_( rm );
   return rm->x->pos - rm->startPos;
}

inline int64_t trace_record_c( cRecordMarker rm[static 1] )
{
   must_exist_c_( rm );

   int64_t const res = rm->x->pos - rm->lastPos;
   rm->lastPos = rm->x->pos;
   return res;
}

inline bool undo_record_c( cRecordMarker rm[static 1] )
{
   must_exist_c_( rm );
   return move_recorder_to_c( rm->x, rm->startPos );
}

inline bool undo_record_error_c( cRecordMarker rm[static 1], int err )
{
   must_exist_c_( rm );
   undo_record_c( rm );
   return record_error_c( rm->x, err );
}

/*******************************************************************************
 util
*******************************************************************************/

void print_recorded_c( cRecorder rec[static 1] );

#define print_scope_c_( Rec, Size )                                            \
for (                                                                          \
   cRecorder* Rec = &recorder_c_(Size);                                        \
   Rec != NULL;                                                                \
   print_recorded_c( Rec ), Rec = NULL                                         \
)

void println_recorded_c( cRecorder rec[static 1] );

#define println_scope_c_( Rec, Size )                                          \
for (                                                                          \
   cRecorder* Rec = &recorder_c_( Size );                                      \
   Rec != NULL;                                                                \
   println_recorded_c( Rec ), Rec = NULL                                       \
)

char* turn_into_cstr_c( cRecorder rec[static 1] );

#endif
