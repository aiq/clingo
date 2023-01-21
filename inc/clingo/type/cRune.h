#ifndef CLINGO_TYPE_CRUNE_H
#define CLINGO_TYPE_CRUNE_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"
#include "clingo/type/cByte.h"
#include "clingo/type/cChars.h"
#include "clingo/type/uint8.h"
#include "clingo/type/uint16.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cRune
{
   union
   {
      uint32_t ctrl;
      cByte b[4];
      char c[4];
   };
};
typedef struct cRune cRune;

typedef bool ( *c_check_rune )( cRune r );

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cRune,            // Type
   cRuneSlice,       // SliceType
   cVarRuneSlice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 utf8
*******************************************************************************/

CLINGO_API inline bool is_utf8_head_c( char c )
{
   return not in_range_c_( 0x80, uint8_c_( c ), 0xBF );
}

CLINGO_API inline bool is_utf8_tail_c( char c )
{
   return in_range_c_( 0x80, uint8_c_( c ), 0xBF );
}

CLINGO_API inline int8_t utf8_length_c( char c )
{
   cByte const value = byte_c_( c );
   if ( value <= 0x7F)
   {
      return 1;
   }
   else if ( in_range_c_( 0xC0, value, 0xDF ) )
   {
      return 2;
   }
   else if ( in_range_c_( 0xE0, value, 0xEF ) )
   {
      return 3;
   }
   else if ( in_range_c_( 0xF0, value, 0xF4 ) )
   {
      return 4;
   }

   return 0;
}

/*******************************************************************************
 utf16
*******************************************************************************/

CLINGO_API inline bool is_high_utf16_surrogate_c( uint16_t val )
{
   return in_range_c_( 0xd800, val, 0xdbff );
}

CLINGO_API inline bool is_low_utf16_surrogate_c( uint16_t val )
{
   return in_range_c_( 0xdc00, val, 0xdfff );
}

CLINGO_API inline uint32_t utf16_to_utf32_c( uint16_t high, uint16_t low )
{
   if ( is_high_utf16_surrogate_c( high ) )
   {
      return ( high - 0xd800 ) * 0x400 + ( low - 0xdc00 ) + 0x10000;
   }

   return high;
}

CLINGO_API inline uint16_t utf32_to_utf16_c( uint32_t val,
                                             uint16_t low[static 1] )
{
   if ( val > 0xffff )
   {
      uint16_t high = ( uint16_c_( val - 0x10000 ) / 0x400 ) + 0xd800;
      *low = ( uint16_c_( val - 0x10000 ) % 0x400 ) + 0xdc00;
      return high;
   }

   return uint16_c_( val );
}

/*******************************************************************************
 init
*******************************************************************************/

#define build_rune_c_( A, B, C, D )                                            \
(                                                                              \
   (cRune){ .b={ (A), (B), (C), (D) } }                                        \
)

CLINGO_API cRune make_rune_c( cChars chars );

CLINGO_API inline cRune null_rune_c()
{
   return build_rune_c_( 0xff, 0, 0, 0 );
}

CLINGO_API cRune rune_c( char const cstr[static 1] );

CLINGO_API cRune surrogate_rune_c( uint16_t high, uint16_t low );

CLINGO_API cRune utf16_rune_c( uint16_t val );

CLINGO_API cRune utf32_rune_c( uint32_t val );

/*******************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_rune_c( cRune a, cRune b )
{
   return a.ctrl == b.ctrl ? 0
                           : a.ctrl < b.ctrl ? -1
                                             : 1;
}

CLINGO_API inline bool eq_rune_c( cRune a, cRune b )
{
   return a.ctrl == b.ctrl;
}

CLINGO_API uint32_t rune_code_c( cRune r );

CLINGO_API inline bool rune_is_c( cRune r, char const cstr[static 1] )
{
   return eq_rune_c( r, rune_c( cstr ) );
}

CLINGO_API inline bool rune_is_valid_c( cRune r )
{
   #define zero_( B ) ( (B) == 0 )
   #define tail_( B ) is_utf8_tail_c( B )
   switch( utf8_length_c( r.c[0] ) )
   {
	   case 1:  return zero_( r.c[1] ) and zero_( r.c[2] ) and zero_( r.c[3] ); 
	   case 2:  return tail_( r.c[1] ) and zero_( r.c[2] ) and zero_( r.c[3] );
	   case 3:  return tail_( r.c[1] ) and tail_( r.c[2] ) and zero_( r.c[3] );
      case 4:  return tail_( r.c[1] ) and tail_( r.c[2] ) and tail_( r.c[3] );
      default: return false;
   }
}

CLINGO_API inline int8_t rune_size_c( cRune r )
{
   return utf8_length_c( r.c[0] );
}

/*******************************************************************************
 chars
*******************************************************************************/

CLINGO_API char const* ceil_to_rune_c( cChars chars, int64_t index );
CLINGO_API char const* first_rune_c( cChars chars );
CLINGO_API char const* floor_to_rune_c( cChars chars, int64_t index );
CLINGO_API char const* last_rune_c( cChars chars );
CLINGO_API char const* nth_rune_c( cChars chars, int64_t n );

/*******************************************************************************
 itr
*******************************************************************************/

#define iterate_runes_c_( Itr, RunePtr, Chars )                                \
   for ( char const* Itr = next_rune_c( Chars, NULL, RunePtr );                \
         Itr != NULL;                                                          \
         Itr = next_rune_c( Chars, Itr, RunePtr ) )
CLINGO_API
inline char const* next_rune_c( cChars chars,
                                char const* itr,
                                cRune r[static 1] )
{
   if ( is_empty_c_( chars ) ) return NULL;

   itr = points_into_c_( chars, itr ) ? itr + utf8_length_c( *itr )
                                      : begin_c_( chars );
   int64_t const len = utf8_length_c( *itr );
   if ( len == 0 or
        itr+len > end_c_( chars ) ) return NULL;

   *r = rune_c( itr );
   return itr;
}

/*******************************************************************************
 chars
*******************************************************************************/

CLINGO_API int64_t count_runes_c( cChars chars );

CLINGO_API cVarRuneSlice fill_rune_slice_c( cVarRuneSlice dst, cChars src );

#define find_any_rune_c_( Chars, Cstr )                                        \
   find_any_rune_c( (Chars), c_c( Cstr ) )
CLINGO_API char const* find_any_rune_c( cChars chars, cChars set );

#define find_rune_c_( Chars, Cstr )                                            \
   find_rune_c( (Chars), rune_c( Cstr ) )
CLINGO_API char const* find_rune_c( cChars chars, cRune r );

CLINGO_API cChars left_runes_c( cChars chars, int64_t maxLen );

CLINGO_API cChars mid_runes_c( cChars chars, int64_t index );

CLINGO_API cChars right_runes_c( cChars chars, int64_t maxLen );

CLINGO_API cChars sub_runes_c( cChars chars, int64_t begIdx, int64_t endIdx );

#endif
