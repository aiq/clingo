#ifndef CLINGO_IO_CSCANNER_H
#define CLINGO_IO_CSCANNER_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/error.h"
#include "clingo/lang/mem.h"
#include "clingo/type/cBytes.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/cRuneRange.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cSCANNER_ERROR_CODE_                                                   \
   XMAP_C_( c_EndOfScanner,         1, "end of scanner" )                      \
   XMAP_C_( c_IncompleteScanValue,  2, "incomplete scan value" )               \
   XMAP_C_( c_ToLargeReadFormat,    3, "to large read format" )                \
   XMAP_C_( c_InvalidReadFormat,    4, "invalid read format" )                 \
   XMAP_C_( c_ReadAllocError,       5, "read allocation errro" )               \
   XMAP_C_( c_NotAbleToReadValue,   6, "not able to read value" )

#define XMAP_C_( N, I, T ) N = I,
enum c_ScannerErrorCode { cSCANNER_ERROR_CODE_ };
#undef XMAP_C_
typedef enum c_ScannerErrorCode c_ScannerErrorCode;

struct cScannerError
{
   int code;
};
typedef struct cScannerError cScannerError;

CLINGO_API extern cErrorType const C_ScannerError;

struct cScanner
{
   int64_t     pos;
   int64_t     space;
   void const* mem;
   int         err;
};
typedef struct cScanner cScanner;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define cstr_scanner_c_( Cstr )                                                \
(                                                                              \
   (cScanner){ .pos=0, .space=(int64_t)strlen( Cstr ), .mem=(Cstr) }           \
)

#define make_scanner_c_( Size, Memory )                                        \
(                                                                              \
   (cScanner){ .pos=0, .space=(Size), .mem=(Memory) }                          \
)

#define null_scanner_c_()                                                      \
(                                                                              \
   (cScanner){ .pos=0, .space=0, .mem=NULL }                                   \
)

#define scanner_copy_c_( Sca )                                                 \
(                                                                              \
   (cScanner){ .pos=(Sca)->pos, .space=(Sca)->space, .mem=(Sca)->mem }         \
)

#define sub_scanner_c_( Sca, MaxSize )                                         \
(                                                                              \
   make_scanner_c_( min_c_( (MaxSize), (Sca)->space ), (Sca)->mem )            \
)

/*******************************************************************************
 move
*******************************************************************************/

CLINGO_API inline bool move_scanner_c( cScanner sca[static 1], int64_t offset )
{
   must_exist_c_( sca );

   int64_t newPos = sca->pos + offset;
   int64_t newSpace = sca->space - offset;

   if ( newPos < 0 or newSpace < 0 )
   {
      return false;
   }

   sca->pos += offset;
   sca->space -= offset;
   sca->mem += offset;
   return true;
}

CLINGO_API inline bool move_scanner_to_c( cScanner sca[static 1], int64_t pos )
{
   must_exist_c_( sca );

   int64_t offset = pos - sca->pos;
   return move_scanner_c( sca, offset );
}

CLINGO_API inline void reset_scanner_c( cScanner sca[static 1] )
{
   must_exist_c_( sca );

   move_scanner_to_c( sca, 0 );
}

/*******************************************************************************
 move if
*******************************************************************************/

CLINGO_API bool move_if_byte_c( cScanner sca[static 1], cByte b );
CLINGO_API bool move_if_byte_match_c( cScanner sca[static 1], c_check_byte check );
CLINGO_API bool move_if_bytes_c( cScanner sca[static 1], cBytes slice );

#define move_if_any_char_c_( Sca, Cstr )                                       \
   move_if_any_char_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_if_any_char_c( cScanner sca[static 1], cChars set );
CLINGO_API bool move_if_char_c( cScanner sca[static 1], char c );
CLINGO_API bool move_if_char_match_c( cScanner sca[static 1], c_check_char check );

#define move_if_any_chars_c_( Sca, ... )                                       \
   move_if_any_chars_c( (Sca), cs_c_( __VA_ARGS__ ) )
CLINGO_API bool move_if_any_chars_c( cScanner sca[static 1], cCharsSlice slice );
#define move_if_chars_c_( Sca, Cstr )                                          \
   move_if_chars_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_if_chars_c( cScanner sca[static 1], cChars chars );

#define move_if_any_rune_c_( Sca, Cstr )                                       \
   move_if_any_rune_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_if_any_rune_c( cScanner sca[static 1], cChars set );
CLINGO_API bool move_if_rune_c( cScanner sca[static 1], cRune r );
CLINGO_API bool move_if_rune_match_c( cScanner sca[static 1], c_check_rune check );

CLINGO_API bool move_if_in_range_c( cScanner sca[static 1], cRuneRange range );

/*******************************************************************************
 move to
*******************************************************************************/

CLINGO_API bool move_to_byte_c( cScanner sca[static 1], cByte b );
CLINGO_API bool move_to_byte_match_c( cScanner sca[static 1], c_check_byte check );
CLINGO_API bool move_to_bytes_c( cScanner sca[static 1], cBytes slice );

#define move_to_any_char_c_( Sca, Cstr )                                       \
   move_to_any_char_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_to_any_char_c( cScanner sca[static 1], cChars set );
CLINGO_API bool move_to_char_c( cScanner sca[static 1], char c );
CLINGO_API bool move_to_char_match_c( cScanner sca[static 1], c_check_char check );

#define move_to_any_chars_c_( Sca, ... )                                       \
   move_to_any_chars_c( (Sca), cs_c_( __VA_ARGS__ ) )
CLINGO_API bool move_to_any_chars_c( cScanner sca[static 1], cCharsSlice slice );
#define move_to_chars_c_( Sca, Cstr )                                          \
   move_to_chars_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_to_chars_c( cScanner sca[static 1], cChars chars );

#define move_to_any_rune_c_( Sca, Cstr )                                       \
   move_to_any_rune_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_to_any_rune_c( cScanner sca[static 1], cChars set );
CLINGO_API bool move_to_rune_c( cScanner sca[static 1], cRune r );
CLINGO_API bool move_to_rune_match_c( cScanner sca[static 1], c_check_rune check );

CLINGO_API bool move_to_in_range_c( cScanner sca[static 1], cRuneRange range );

/*******************************************************************************
 move while
*******************************************************************************/

CLINGO_API bool move_while_byte_c( cScanner sca[static 1], cByte b );
CLINGO_API bool move_while_byte_match_c( cScanner sca[static 1], c_check_byte check );

#define move_while_any_char_c_( Sca, Cstr )                                    \
   move_while_any_char_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_while_any_char_c( cScanner sca[static 1], cChars set );
CLINGO_API bool move_while_char_c( cScanner sca[static 1], char c );
CLINGO_API bool move_while_char_match_c( cScanner sca[static 1], c_check_char check );

#define move_while_any_rune_c_( Sca, Cstr )                                    \
   move_while_any_rune_c( (Sca), c_c( Cstr ) )
CLINGO_API bool move_while_any_rune_c( cScanner sca[static 1], cChars set );
CLINGO_API bool move_while_rune_c( cScanner sca[static 1], cRune r );
CLINGO_API bool move_while_rune_match_c( cScanner sca[static 1], c_check_rune check );

CLINGO_API bool move_while_in_range_c( cScanner sca[static 1], cRuneRange range );

/*******************************************************************************
 error
*******************************************************************************/

CLINGO_API inline bool set_scanner_error_c( cScanner sca[static 1], int err )
{
   sca->err = err;
   return false;
}

CLINGO_API inline int clear_scanner_error_c( cScanner sca[static 1] )
{
   int res = sca->err;
   sca->err = 0;
   return res;
}

/*******************************************************************************
 access
*******************************************************************************/

#define scanned_bytes_c_( Sca )                                                \
   scanned_bytes_c( (Sca), (Sca)->pos )
CLINGO_API inline cBytes scanned_bytes_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->pos <= 0 or size > sca->pos )
   {
      return (cBytes)empty_c_();
   }
   cByte const* ptr = sca->mem;
   return (cBytes){ size, ptr - size };
}

#define scanned_chars_c_( Sca )                                                \
   scanned_chars_c( (Sca), (Sca)->pos )
CLINGO_API inline cChars scanned_chars_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->pos <= 0 or size > sca->pos )
   {
      return (cChars)empty_c_();
   }
   char const* ptr = sca->mem;
   return (cChars){ size, ptr - size };
}

#define unscanned_bytes_c_( Sca )                                              \
   unscanned_bytes_c( (Sca), (Sca)->space )
CLINGO_API inline cBytes unscanned_bytes_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->space <= 0 or size > sca->space )
   {
      return (cBytes)empty_c_();
   }
   cByte const* ptr = sca->mem;
   return (cBytes){ size, ptr };
}

#define unscanned_chars_c_( Sca )                                              \
   unscanned_chars_c( (Sca), (Sca)->space )
CLINGO_API inline cChars unscanned_chars_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->space <= 0 or size > sca->space )
   {
      return (cChars)empty_c_();
   }
   char const* ptr = sca->mem;
   return (cChars){ size, ptr };
}

CLINGO_API bool unscanned_is_c( cScanner const sca[static 1], char const cstr[static 1] );

/*******************************************************************************
 on
*******************************************************************************/

CLINGO_API inline bool on_byte_c( cScanner sca[static 1], cByte b )
{
   must_exist_c_( sca );
   cByte const* ptr = sca->mem;
   return ( sca->space > 0 and *ptr == b );
}

CLINGO_API inline bool on_bytes_c( cScanner sca[static 1], cBytes slice )
{
   must_exist_c_( sca );
   cBytes unscanned = unscanned_bytes_c_( sca );
   return bytes_starts_with_c( unscanned, slice );
}

#define on_any_char_c_( Sca, Cstr )                                            \
   on_any_char_c( (Sca), c_c( Cstr ) )
CLINGO_API inline bool on_any_char_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );
   char const* ptr = sca->mem;
   return ( sca->space > 0 and find_char_c( set, *ptr ) );
}

CLINGO_API inline bool on_char_c( cScanner sca[static 1], char c )
{
   must_exist_c_( sca );
   char const* ptr = sca->mem;
   return ( sca->space > 0 and *ptr == c );
}

CLINGO_API inline bool on_chars_c( cScanner sca[static 1], cChars chars )
{
   must_exist_c_( sca );
   cChars unscanned = unscanned_chars_c_( sca );
   return chars_starts_with_c( unscanned, chars );
}

CLINGO_API inline bool on_rune_c( cScanner sca[static 1], cRune r )
{
   must_exist_c_( sca );
   cChars unscanned = unscanned_chars_c_( sca );
   cRune tmp = make_rune_c( unscanned );
   return rune_is_valid_c( tmp ) and eq_rune_c( tmp, r );
}

/*******************************************************************************
 view
*******************************************************************************/

CLINGO_API inline cBytes view_bytes_c( cScanner sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( size > sca->space )
   {
      return (cBytes)empty_c_();
   }

   const cByte* ptr = sca->mem;
   sca->pos += size;
   sca->space -= size;
   sca->mem += size;
   return (cBytes){ size, ptr };
}

CLINGO_API inline cChars view_chars_c( cScanner sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( size > sca->space )
   {
      return (cChars)empty_c_();
   }

   char const* ptr = sca->mem;
   sca->pos += size;
   sca->space -= size;
   sca->mem += size;
   return (cChars){ size, ptr };
}

CLINGO_API char const* view_cstr_c( cScanner sca[static 1] );

CLINGO_API cChars view_pad_c( cScanner sca[static 1], char c );

CLINGO_API cChars view_runes_c( cScanner sca[static 1], int64_t size );

/*******************************************************************************
 scan
*******************************************************************************/

CLINGO_API bool scan_byte_c(   cScanner sca[static 1], cByte b[static 1] );
CLINGO_API bool scan_char_c(   cScanner sca[static 1], char c[static 1] );
CLINGO_API bool scan_rune_c(   cScanner sca[static 1], cRune r[static 1] );

CLINGO_API bool scan_int8_c(   cScanner sca[static 1], int8_t i8[static 1] );
CLINGO_API bool scan_int16_c(  cScanner sca[static 1], int16_t i16[static 1] );
CLINGO_API bool scan_int32_c(  cScanner sca[static 1], int32_t i32[static 1] );
CLINGO_API bool scan_int64_c(  cScanner sca[static 1], int64_t i64[static 1] );

CLINGO_API bool scan_uint8_c(  cScanner sca[static 1], uint8_t u8[static 1] );
CLINGO_API bool scan_uint16_c( cScanner sca[static 1], uint16_t u16[static 1] );
CLINGO_API bool scan_uint32_c( cScanner sca[static 1], uint32_t u32[static 1] );
CLINGO_API bool scan_uint64_c( cScanner sca[static 1], uint64_t u64[static 1] );

CLINGO_API bool scan_float_c(  cScanner sca[static 1], float f[static 1] );
CLINGO_API bool scan_double_c( cScanner sca[static 1], double d[static 1] );

#define scan_pointer_c_( Sca, Ptr )                                            \
   scan_pointer_c( (Sca), (void**)(Ptr) )
CLINGO_API bool scan_pointer_c( cScanner sca[static 1], void** ptr );

/*******************************************************************************
 error
*******************************************************************************/

CLINGO_API bool push_scanner_error_c( cErrorStack es[static 1],
                                      cScanner const sca[static 1] );

#endif
