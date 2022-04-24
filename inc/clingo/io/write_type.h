#ifndef CLINGO_IO_WRITE_TYPE_H
#define CLINGO_IO_WRITE_TYPE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/bool.h"
#include "clingo/type/cRange.h"
#include "clingo/type/double.h"
#include "clingo/type/float.h"
#include "clingo/type/int16.h"
#include "clingo/type/int32.h"
#include "clingo/type/int64.h"
#include "clingo/type/int8.h"
#include "clingo/type/uint16.h"
#include "clingo/type/uint32.h"
#include "clingo/type/uint64.h"
#include "clingo/type/uint8.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 basic
*******************************************************************************/

#define write_bool_c_( Rec, Bool )                                             \
   write_bool_c( (Rec), (Bool), "" )
CLINGO_API
bool write_bool_c( cRecorder rec[static 1],
                   bool val,
                   char const fmt[static 1] );

#define write_byte_c_( Rec, Byte )                                             \
   write_byte_c( (Rec), (Byte), "" )
CLINGO_API
bool write_byte_c( cRecorder rec[static 1],
                   cByte byte,
                   char const fmt[static 1] );

#define write_char_c_( Rec, Char )                                             \
   write_char_c( (Rec), (Char), "" )
CLINGO_API
bool write_char_c( cRecorder rec[static 1],
                   char c,
                   char const fmt[static 1] );

#define write_range_c_( Rec, Rng )                                             \
   write_range_c( (Rec), (Rng), "" )
CLINGO_API
bool write_range_c( cRecorder rec[static 1],
                    cRange rng,
                    char const fmt[static 1] );

#define write_rune_c_( Rec, Rune )                                             \
   write_rune_c( (Rec), (Rune), "" )
CLINGO_API
bool write_rune_c( cRecorder rec[static 1],
                   cRune rune,
                   char const fmt[static 1] );

/*******************************************************************************
 float
*******************************************************************************/

#define write_double_c_( Double, Rec )                                         \
   write_double_c( (Double), (Rec), "" )
CLINGO_API
bool write_double_c( cRecorder rec[static 1],
                     double d,
                     char const fmt[static 1] );

#define write_float_c_( Float, Rec )                                           \
   write_float_c( (Float), (Rec), "" )
CLINGO_API
bool write_float_c( cRecorder rec[static 1],
                    float f,
                    char const fmt[static 1] );

/*******************************************************************************
 signed
*******************************************************************************/

#define write_int16_c_( Rec, Int16 )                                           \
   write_int16_c( (Rec), (Int16), "" )
CLINGO_API
bool write_int16_c( cRecorder rec[static 1],
                    int16_t i16,
                    char const fmt[static 1] );

#define write_int32_c_( Rec, Int32  )                                          \
   write_int32_c( (Rec), (Int32), "" )
CLINGO_API
bool write_int32_c( cRecorder rec[static 1],
                    int32_t i32,
                    char const fmt[static 1] );

#define write_int64_c_( Rec, Int64 )                                           \
   write_int64_c( (Rec), (Int64), "" )
CLINGO_API
bool write_int64_c( cRecorder rec[static 1],
                    int64_t i64,
                    char const fmt[static 1] );

#define write_int8_c_( Rec, Int8 )                                             \
   write_int8_c( (Rec), (Int8), "" )
CLINGO_API
bool write_int8_c( cRecorder rec[static 1],
                   int8_t i8,
                   char const fmt[static 1] );

/*******************************************************************************
 unsigned
*******************************************************************************/

#define write_uint16_c_( Rec, Uint16 )                                         \
   write_uint16_c( (Rec), (Uint16), "" )
CLINGO_API
bool write_uint16_c( cRecorder rec[static 1],
                     uint16_t u16,
                     char const fmt[static 1] );

#define write_uint32_c_( Rec, Uint32 )                                         \
   write_uint32_c( (Rec), (Uint32), "" )
CLINGO_API
bool write_uint32_c( cRecorder rec[static 1],
                     uint32_t u32,
                     char const fmt[static 1] );

#define write_uint64_c_( Rec, Uint64 )                                         \
   write_uint64_c( (Rec), (Uint64), "" )
CLINGO_API
bool write_uint64_c( cRecorder rec[static 1],
                     uint64_t u64,
                     char const fmt[static 1] );

#define write_uint8_c_( Rec, Uint8 )                                           \
   write_uint8_c( (Rec), (Uint8), "" )
CLINGO_API
bool write_uint8_c( cRecorder rec[static 1],
                    uint8_t u8,
                    char const fmt[static 1] );

/*******************************************************************************
 slice
*******************************************************************************/

#define write_bytes_c_( Rec, Bytes )                                           \
   write_bytes_c( (Rec), (Bytes), "" )
CLINGO_API
bool write_bytes_c( cRecorder rec[static 1],
                    cBytes bytes,
                    char const fmt[static 1] );

#define write_chars_c_( Rec, Chars )                                           \
   write_chars_c( (Rec), (Slice), "" )
CLINGO_API
bool write_chars_c( cRecorder rec[static 1],
                    cChars chars,
                    char const fmt[static 1] );

#define write_cstr_c_( Rec, Str )                                              \
   write_cstr_c_( (Rec), (Str), "" )
CLINGO_API
bool write_cstr_c( cRecorder rec[static 1],
                   char const str[static 1],
                   char const fmt[static 1] );

#define write_recorded_c_( Rec, Src )                                          \
   write_recorded_c( (Rec), (Src), "" )
CLINGO_API
bool write_recorded_c( cRecorder rec[static 1],
                       cRecorder const src[static 1],
                       char const fmt[static 1] );

#define write_unscanned_c_( Rec, Sca )                                         \
   write_unscanned_c( (Rec), (Sca), "" )
CLINGO_API
bool write_unscanned_c( cRecorder rec[static 1],
                        cScanner const sca[static 1],
                        char const fmt[static 1] );

#endif
