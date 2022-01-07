#ifndef CLINGO_IO_CSCANNER_H
#define CLINGO_IO_CSCANNER_H

#include <stdint.h>

#include "clingo/lang/mem.h"
#include "clingo/type/cBytes.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/cRuneRange.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cScanner
{
   int64_t     pos;
   int64_t     space;
   void const* mem;
   int         err;
};
typedef struct cScanner cScanner;

struct cScanMarker
{
   cScanner* x;
   int64_t   startPos;
   int64_t   lastPos;
};
typedef struct cScanMarker cScanMarker;

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

#define sub_scanner_c_( Sca, MaxSize )                                         \
(                                                                              \
   make_scanner_c_( min_c_( (MaxSize), (Sca)->space ), (Sca)->mem )            \
)

/*******************************************************************************
 move
*******************************************************************************/

inline bool move_scanner_c( cScanner sca[static 1], int64_t offset )
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

inline bool move_scanner_to_c( cScanner sca[static 1], int64_t pos )
{
   must_exist_c_( sca );

   int64_t offset = pos - sca->pos;
   return move_scanner_c( sca, offset );
}

inline void reset_scanner_c( cScanner sca[static 1] )
{
   must_exist_c_( sca );

   move_scanner_to_c( sca, 0 );
}

/*******************************************************************************
 move if
*******************************************************************************/

bool move_if_byte_c( cScanner sca[static 1], cByte b );
bool move_if_byte_match_c( cScanner sca[static 1], c_check_byte check );
bool move_if_bytes_c( cScanner sca[static 1], cBytes slice );

#define move_if_any_char_c_( Sca, Cstr )                                       \
   move_if_any_char_c( (Sca), c_c( Cstr ) )
bool move_if_any_char_c( cScanner sca[static 1], cChars set );
bool move_if_char_c( cScanner sca[static 1], char c );
bool move_if_char_match_c( cScanner sca[static 1], c_check_char check );

#define move_if_any_chars_c_( Sca, ... )                                       \
   move_if_any_chars_c( (Sca), cs_c_( __VA_ARGS__ ) )
bool move_if_any_chars_c( cScanner sca[static 1], cCharsSlice slice );
#define move_if_chars_c_( Sca, Cstr )                                          \
   move_if_chars_c( (Sca), c_c( Cstr ) )
bool move_if_chars_c( cScanner sca[static 1], cChars chars );

#define move_if_any_rune_c_( Sca, Cstr )                                       \
   move_if_any_rune_c( (Sca), c_c( Cstr ) )
bool move_if_any_rune_c( cScanner sca[static 1], cChars set );
bool move_if_rune_c( cScanner sca[static 1], cRune r );
bool move_if_rune_match_c( cScanner sca[static 1], c_check_rune check );

bool move_if_in_range_c( cScanner sca[static 1], cRuneRange range );

/*******************************************************************************
 move to
*******************************************************************************/

bool move_to_byte_c( cScanner sca[static 1], cByte b );
bool move_to_byte_match_c( cScanner sca[static 1], c_check_byte check );
bool move_to_bytes_c( cScanner sca[static 1], cBytes slice );

#define move_to_any_char_c_( Sca, Cstr )                                       \
   move_to_any_char_c( (Sca), c_c( Cstr ) )
bool move_to_any_char_c( cScanner sca[static 1], cChars set );
bool move_to_char_c( cScanner sca[static 1], char c );
bool move_to_char_match_c( cScanner sca[static 1], c_check_char check );

#define move_to_any_chars_c_( Sca, ... )                                       \
   move_to_any_chars_c( (Sca), cs_c_( __VA_ARGS__ ) )
bool move_to_any_chars_c( cScanner sca[static 1], cCharsSlice slice );
#define move_to_chars_c_( Sca, Cstr )                                          \
   move_to_chars_c( (Sca), c_c( Cstr ) )
bool move_to_chars_c( cScanner sca[static 1], cChars chars );

#define move_to_any_rune_c_( Sca, Cstr )                                       \
   move_to_any_rune_c( (Sca), c_c( Cstr ) )
bool move_to_any_rune_c( cScanner sca[static 1], cChars set );
bool move_to_rune_c( cScanner sca[static 1], cRune r );
bool move_to_rune_match_c( cScanner sca[static 1], c_check_rune check );

bool move_to_in_range_c( cScanner sca[static 1], cRuneRange range );

/*******************************************************************************
 move while
*******************************************************************************/

bool move_while_byte_c( cScanner sca[static 1], cByte b );
bool move_while_byte_match_c( cScanner sca[static 1], c_check_byte check );

#define move_while_any_char_c_( Sca, Cstr )                                    \
   move_while_any_char_c( (Sca), c_c( Cstr ) )
bool move_while_any_char_c( cScanner sca[static 1], cChars set );
bool move_while_char_c( cScanner sca[static 1], char c );
bool move_while_char_match_c( cScanner sca[static 1], c_check_char check );

#define move_while_any_rune_c_( Sca, Cstr )                                    \
   move_while_any_rune_c( (Sca), c_c( Cstr ) )
bool move_while_any_rune_c( cScanner sca[static 1], cChars set );
bool move_while_rune_c( cScanner sca[static 1], cRune r );
bool move_while_rune_match_c( cScanner sca[static 1], c_check_rune check );

bool move_while_in_range_c( cScanner sca[static 1], cRuneRange range );

/*******************************************************************************
 error
*******************************************************************************/

inline bool scan_error_c( cScanner sca[static 1], int err )
{
   sca->err = err;
   return false;
}

/*******************************************************************************
 access
*******************************************************************************/

#define scanned_bytes_c_( Sca )                                                \
   scanned_bytes_c( (Sca), (Sca)->pos )
inline cBytes scanned_bytes_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->pos <= 0 or size > sca->pos )
   {
      return empty_bytes_c();
   }
   cByte const* ptr = sca->mem;
   return bytes_c( size, ptr - size );
}

#define scanned_chars_c_( Sca )                                                \
   scanned_chars_c( (Sca), (Sca)->pos )
inline cChars scanned_chars_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->pos <= 0 or size > sca->pos )
   {
      return empty_chars_c();
   }
   char const* ptr = sca->mem;
   return chars_c( size, ptr - size );
}

#define unscanned_bytes_c_( Sca )                                              \
   unscanned_bytes_c( (Sca), (Sca)->space )
inline cBytes unscanned_bytes_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->space <= 0 or size > sca->space )
   {
      return empty_bytes_c();
   }
   cByte const* ptr = sca->mem;
   return bytes_c( size, ptr );
}

#define unscanned_chars_c_( Sca )                                              \
   unscanned_chars_c( (Sca), (Sca)->space )
inline cChars unscanned_chars_c( cScanner const sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( sca->space <= 0 or size > sca->space )
   {
      return empty_chars_c();
   }
   char const* ptr = sca->mem;
   return chars_c( size, ptr );
}

bool unscanned_is_c( cScanner const sca[static 1], char const cstr[static 1] );

/*******************************************************************************
 on
*******************************************************************************/

inline bool on_byte_c( cScanner sca[static 1], cByte b )
{
   must_exist_c_( sca );
   cByte const* ptr = sca->mem;
   return ( sca->space > 0 and *ptr == b );
}

inline bool on_bytes_c( cScanner sca[static 1], cBytes slice )
{
   must_exist_c_( sca );
   cBytes unscanned = unscanned_bytes_c_( sca );
   return bytes_starts_with_c( unscanned, slice );
}

#define on_any_char_c_( Sca, Cstr )                                            \
   on_any_char_c( (Sca), c_c( Cstr ) )
inline bool on_any_char_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );
   char const* ptr = sca->mem;
   return ( sca->space > 0 and find_char_c( set, *ptr ) );
}

inline bool on_char_c( cScanner sca[static 1], char c )
{
   must_exist_c_( sca );
   char const* ptr = sca->mem;
   return ( sca->space > 0 and *ptr == c );
}

inline bool on_chars_c( cScanner sca[static 1], cChars chars )
{
   must_exist_c_( sca );
   cChars unscanned = unscanned_chars_c_( sca );
   return chars_starts_with_c( unscanned, chars );
}

inline bool on_rune_c( cScanner sca[static 1], cRune r )
{
   must_exist_c_( sca );
   cChars unscanned = unscanned_chars_c_( sca );
   cRune tmp = make_rune_c( unscanned );
   return rune_is_valid_c( tmp ) and eq_rune_c( tmp, r );
}

/*******************************************************************************
 view
*******************************************************************************/

inline cBytes view_bytes_c( cScanner sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( size > sca->space )
   {
      return empty_bytes_c();
   }

   const cByte* ptr = sca->mem;
   sca->pos += size;
   sca->space -= size;
   sca->mem += size;
   return bytes_c( size, ptr );
}

inline cChars view_chars_c( cScanner sca[static 1], int64_t size )
{
   must_exist_c_( sca );
   must_be_positive_c_( size );

   if ( size > sca->space )
   {
      return empty_chars_c();
   }

   char const* ptr = sca->mem;
   sca->pos += size;
   sca->space -= size;
   sca->mem += size;
   return chars_c( size, ptr );
}

char const* view_cstr_c( cScanner sca[static 1] );

cChars view_pad_c( cScanner sca[static 1], char c );

cChars view_runes_c( cScanner sca[static 1], int64_t size );

/*******************************************************************************
 scan
*******************************************************************************/

bool scan_byte_c(   cScanner sca[static 1], cByte b[static 1] );
bool scan_char_c(   cScanner sca[static 1], char c[static 1] );
bool scan_rune_c(   cScanner sca[static 1], cRune r[static 1] );

bool scan_int8_c(   cScanner sca[static 1], int8_t i8[static 1] );
bool scan_int16_c(  cScanner sca[static 1], int16_t i16[static 1] );
bool scan_int32_c(  cScanner sca[static 1], int32_t i32[static 1] );
bool scan_int64_c(  cScanner sca[static 1], int64_t i64[static 1] );

bool scan_uint8_c(  cScanner sca[static 1], uint8_t u8[static 1] );
bool scan_uint16_c( cScanner sca[static 1], uint16_t u16[static 1] );
bool scan_uint32_c( cScanner sca[static 1], uint32_t u32[static 1] );
bool scan_uint64_c( cScanner sca[static 1], uint64_t u64[static 1] );

bool scan_float_c(  cScanner sca[static 1], float f[static 1] );
bool scan_double_c( cScanner sca[static 1], double d[static 1] );

/*******************************************************************************
 marker
*******************************************************************************/

#define scan_marker_c_( Sca )                                                  \
(                                                                              \
   (cScanMarker){ .x=(Sca), .startPos=(Sca)->pos, .lastPos=(Sca)->pos }        \
)

#define trace_scan_c_( Sm )                                                    \
   trace_scan_c( (Sm), false )
inline int64_t trace_scan_c( cScanMarker sm[static 1], bool full )
{
   must_exist_c_( sm );

   int64_t const res = full ? sm->x->pos - sm->startPos
                            : sm->x->pos - sm->lastPos;
   sm->lastPos = sm->x->pos;
   return res;
}

#define traced_bytes_c_( Sm )                                                  \
   traced_bytes_c( (Sm), false )
inline cBytes traced_bytes_c( cScanMarker sm[static 1], bool full )
{
   must_exist_c_( sm );
   return scanned_bytes_c( sm->x, trace_scan_c( sm, full ) );
}

#define traced_chars_c_( Sm )                                                  \
   traced_chars_c( (Sm), false )
inline cChars traced_chars_c( cScanMarker sm[static 1], bool full )
{
   must_exist_c_( sm );
   return scanned_chars_c( sm->x, trace_scan_c( sm, full ) );
}

inline bool undo_scan_c( cScanMarker sm[static 1] )
{
   must_exist_c_( sm );
   return move_scanner_to_c( sm->x, sm->startPos );
}

inline bool undo_scan_error_c( cScanMarker sm[static 1], int err )
{
   must_exist_c_( sm );
   undo_scan_c( sm );
   return scan_error_c( sm->x, err );
}

#endif
