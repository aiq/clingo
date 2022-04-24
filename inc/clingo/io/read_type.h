#ifndef CLINGO_IO_READ_TYPE_H
#define CLINGO_IO_READ_TYPE_H

#include "clingo/apidecl.h"
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

#define read_bool_c_( Sca, Bool )                                              \
   read_bool_c( (Sca), (Bool), "" )
CLINGO_API
bool read_bool_c( cScanner sca[static 1],
                  bool val[static 1],
                  char const fmt[static 1] );

#define read_byte_c_( Sca, Byte )                                              \
   read_byte_c( (Sca), (Byte), "" )
CLINGO_API
bool read_byte_c( cScanner sca[static 1],
                  cByte byte[static 1],
                  char const fmt[static 1] );

#define read_char_c_( Sca, Char )                                              \
   read_char_c( (Sca), (Char), "" )
CLINGO_API
bool read_char_c( cScanner sca[static 1],
                  char c[static 1],
                  char const fmt[static 1] );

#define read_range_c_( Sca, Rng )                                              \
   read_range_c( (Sca), (Rng), "" )
CLINGO_API
bool read_range_c( cScanner sca[static 1],
                   cRange rng[static 1],
                   char const fmt[static 1] );

#define read_rune_c_( Sca, Rune )                                              \
   read_rune_c( (Sca), (Rune), "" )
CLINGO_API
bool read_rune_c( cScanner sca[static 1],
                  cRune rune[static 1],
                  char const fmt[static 1] );

/*******************************************************************************
 float
*******************************************************************************/

#define read_double_c_( Sca, Double )                                          \
   read_double_c( (Sca), (Double), "" )
CLINGO_API
bool read_double_c( cScanner sca[static 1],
                    double d[static 1],
                    char const fmt[static 1] );

#define read_float_c_( Sca, Float )                                            \
   read_float_c( (Sca), (Float), "" )
CLINGO_API
bool read_float_c( cScanner sca[static 1],
                   float f[static 1],
                   char const fmt[static 1] );

/*******************************************************************************
 signed
*******************************************************************************/

#define read_int16_c_( Sca, Int16 )                                            \
   read_int16_c( (Sca), (Int16), "" )
CLINGO_API
bool read_int16_c( cScanner sca[static 1],
                   int16_t i16[static 1],
                   char const fmt[static 1] );

#define read_int32_c_( Sca, Int32 )                                            \
   read_int32_c( (Sca), (Int32), "" )
CLINGO_API
bool read_int32_c( cScanner sca[static 1],
                   int32_t i32[static 1],
                   char const fmt[static 1] );

#define read_int64_c_( Sca, Int64 )                                            \
   read_int64_c( (Sca), (Int64), "" )
CLINGO_API
bool read_int64_c( cScanner sca[static 1],
                   int64_t i64[static 1],
                   char const fmt[static 1] );

#define read_int8_c_( Sca, Int8 )                                              \
   read_int8_c( (Sca), (Int8), "" )
CLINGO_API
bool read_int8_c( cScanner sca[static 1],
                  int8_t i8[static 1],
                  char const fmt[static 1] );

/*******************************************************************************
 unsigned
*******************************************************************************/

#define read_uint16_c_( Sca, Uint16 )                                          \
   read_uint16_c( (Sca), (Uint16), "" )
CLINGO_API
bool read_uint16_c( cScanner sca[static 1],
                    uint16_t u16[static 1],
                    char const fmt[static 1] );

#define read_uint32_c_( Sca, Uint32 )                                          \
   read_uint32_c( (Sca), (Uint32), "" )
CLINGO_API
bool read_uint32_c( cScanner sca[static 1],
                    uint32_t u32[static 1],
                    char const fmt[static 1] );

#define read_uint64_c_( Sca, Uint64 )                                          \
   read_uint64_c( (Sca), (Uint64), "" )
CLINGO_API
bool read_uint64_c( cScanner sca[static 1],
                    uint64_t u64[static 1],
                    char const fmt[static 1] );

#define read_uint8_c_( Sca, Uint8 )                                            \
   read_uint8_c( (Sca), (Uint8), "" )
CLINGO_API
bool read_uint8_c( cScanner sca[static 1],
                   uint8_t u8[static 1],
                   char const fmt[static 1] );

/*******************************************************************************
 slice
*******************************************************************************/

#define read_chars_c_( Sca, Chars )                                            \
   read_chars_c( (Sca), (Chars), "" )
CLINGO_API
bool read_chars_c( cScanner sca[static 1],
                   cChars chars[static 1],
                   char const fmt[static 1] );

#endif
