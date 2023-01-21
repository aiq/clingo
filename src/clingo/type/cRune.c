#include "clingo/type/cRune.h"
#include <stdio.h>

/*******************************************************************************
********************************************************************+ Functions
********************************************************************************
 utf8
*******************************************************************************/

extern inline bool is_utf8_head_c( char c );

extern inline bool is_utf8_tail_c( char c );

extern inline int8_t utf8_length_c( char c );

/*******************************************************************************
 utf16
*******************************************************************************/

extern inline bool is_high_utf16_surrogate_c( uint16_t val );

extern inline bool is_low_utf16_surrogate_c( uint16_t val );

extern inline uint32_t utf16_to_utf32_c( uint16_t val, uint16_t low );

extern inline uint16_t utf32_to_utf16_c( uint32_t val, uint16_t low[static 1] );

/*******************************************************************************
 init
*******************************************************************************/

cRune make_rune_c( cChars chars )
{
   if ( is_empty_c_( chars ) )
   {
      return null_rune_c();
   }

   cByte const* bytes = (cByte const*) chars.v;
   if ( bytes[ 0 ] <= 0x7F )
   {
      return build_rune_c_( bytes[ 0 ], '\0', '\0', '\0' );
   }
   else if ( chars.s > 1 and
             in_range_c_( 0xC0, bytes[ 0 ], 0xDF ) and // 11000000 <= bytes[ 0 ] <= 11011111
             in_range_c_( 0x80, bytes[ 1 ], 0xBF ) )
   {
      return build_rune_c_( bytes[ 0 ], bytes[ 1 ], '\0', '\0' );
   }
   else if ( chars.s > 2 and
             in_range_c_( 0xE0, bytes[ 0 ], 0xEF ) and // 11100000 <= bytes[ 0 ] <= 11101111
             in_range_c_( 0x80, bytes[ 1 ], 0xBF ) and
             in_range_c_( 0x80, bytes[ 2 ], 0xBF ) )
   {
      return build_rune_c_( bytes[ 0 ], bytes[ 1 ], bytes[ 2 ], '\0' );
   }
   else if ( chars.s > 3 and
             in_range_c_( 0xF0, bytes[ 0 ], 0xF4 ) and // 11110000 <= bytes[ 0 ] <= Cause of RFC 3629
             in_range_c_( 0x80, bytes[ 1 ], 0xBF ) and
             in_range_c_( 0x80, bytes[ 2 ], 0xBF ) and
             in_range_c_( 0x80, bytes[ 3 ], 0xBF ) )
   {
      return build_rune_c_( bytes[ 0 ], bytes[ 1 ], bytes[ 2 ], bytes[ 3 ] );
   }

   return null_rune_c();
}

extern inline cRune null_rune_c();

cRune rune_c( char const cstr[static 1] )
{
   if ( *cstr == '\0' )
   {
      return null_rune_c();
   }

   cByte const* bytes = (cByte const*) cstr;
   if ( bytes[ 0 ] <= 0x7F )
   {
      return build_rune_c_( bytes[ 0 ], '\0', '\0', '\0' );
   }
   else if ( in_range_c_( 0xC0, bytes[ 0 ], 0xDF ) and // 11000000 <= bytes[ 0 ] <= 11011111
             in_range_c_( 0x80, bytes[ 1 ], 0xBF ) )
   {
      return build_rune_c_( bytes[ 0 ], bytes[ 1 ], '\0', '\0' );
   }
   else if ( in_range_c_( 0xE0, bytes[ 0 ], 0xEF ) and // 11100000 <= bytes[ 0 ] <= 11101111
             in_range_c_( 0x80, bytes[ 1 ], 0xBF ) and
             in_range_c_( 0x80, bytes[ 2 ], 0xBF ) )
   {
      return build_rune_c_( bytes[ 0 ], bytes[ 1 ], bytes[ 2 ], '\0' );
   }
   else if ( in_range_c_( 0xF0, bytes[ 0 ], 0xF4 ) and // 11110000 <= bytes[ 0 ] <= Cause of RFC 3629
             in_range_c_( 0x80, bytes[ 1 ], 0xBF ) and
             in_range_c_( 0x80, bytes[ 2 ], 0xBF ) and
             in_range_c_( 0x80, bytes[ 3 ], 0xBF ) )
   {
      return build_rune_c_( bytes[ 0 ], bytes[ 1 ], bytes[ 2 ], bytes[ 3 ] );
   }

   return null_rune_c();
}

cRune surrogate_rune_c( uint16_t high, uint16_t low )
{
   return utf32_rune_c( utf16_to_utf32_c( high, low ) );
}

cRune utf16_rune_c( uint16_t val )
{
   return utf32_rune_c( val );
}

cRune utf32_rune_c( uint32_t val )
{
   if ( val > 0x001000ff )
   {
      return null_rune_c();
   }
   else if ( val > 0x0000ffff )
   {
      uint8_t a = uint8_c_( ( val >> 18 ) | 0x000000f0 );
      uint8_t b = ( ( val >> 12 ) & 0x0000003f ) | 0x00000080;
      uint8_t c = ( ( val >> 6 ) & 0x0000003f ) | 0x00000080;
      uint8_t d = ( val & 0x0000003f ) | 0x00000080;
      return build_rune_c_( a, b, c, d );
   }
   else if ( val >= 0x00000800 )
   {
      uint8_t a = uint8_c_( ( val >> 12 ) | 0x000000e0 );
      uint8_t b = ( ( val >> 6 ) & 0x0000003f) | 0x00000080;
      uint8_t c = ( val & 0x0000003f ) | 0x00000080;
      return build_rune_c_( a, b, c, '\0' );
   }
   else if ( val >= 0x00000080 )
   {
      uint8_t a = uint8_c_( ( val >> 6 ) | 0x000000c0 );
      uint8_t b = ( val & 0x0000003f ) | 0x00000080;
      return build_rune_c_( a, b, '\0', '\0' );
   }
   else
   {
      uint8_t a = uint8_c_( val );
      return build_rune_c_( a, '\0', '\0', '\0' );
   }
}

/*******************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_rune_c( cRune a, cRune b );

extern inline bool eq_rune_c( cRune a, cRune b );

uint32_t rune_code_c( cRune r )
{
   int8_t const len = rune_size_c( r );
   uint8_t const mask = 0x7f >> len;

   uint32_t b0 = r.b[0] & mask;
   uint32_t b1 = r.b[1] & 0x3f;
   uint32_t b2 = r.b[2] & 0x3f;
   uint32_t b3 = r.b[3] & 0x3f;
   switch ( len )
   {
      case 1:  return r.b[0];
      case 2:  return (b0 << 6) | b1;
      case 3:  return (b0 << 12) | (b1 << 6) | b2;
      case 4:  return (b0 << 18) | (b1 << 12) | (b2 << 6) | b3;
      default: return 0xffffffff;
   }
}

extern inline bool rune_is_c( cRune r, char const cstr[static 1] );

extern inline bool rune_is_valid_c( cRune r );

extern inline int8_t rune_size_c( cRune r );

/*******************************************************************************
 algo
*******************************************************************************/

static inline char const* move_rune_ptr( char const* cstr )
{
   return cstr + utf8_length_c( *cstr );
}

char const* ceil_to_rune_c( cChars chars, int64_t index )
{
   char const* ptr = ptr_for_c_( chars, index );

   while ( ptr )
   {
      if ( is_utf8_head_c( *ptr ) )
      {
         return ptr;
      }

      ++index;
      ptr = ptr_for_c_( chars, index );
   }

   return NULL;
}

char const* first_rune_c( cChars chars )
{
   return nth_rune_c( chars, 0 );
}

char const* floor_to_rune_c( cChars chars, int64_t index )
{
   char const* ptr = ptr_for_c_( chars, index );

   while ( ptr >= chars.v )
   {
      if ( is_utf8_head_c( *ptr ) )
      {
         return ptr;
      }

      --ptr;
   }

   return NULL;
}

char const* last_rune_c( cChars chars )
{
   return nth_rune_c( chars, -1 );
}

extern inline char const* next_rune_c( cChars chars, char const* itr, cRune r[static 1] );

char const* nth_rune_c( cChars chars, int64_t n )
{
   if ( n >= 0 )
   {
      char const* itr = begin_c_( chars );
      char const* end = end_c_( chars );
      int64_t i = 0;
      while ( ( itr < end ) and ( i < n ) )
      {
         itr = move_rune_ptr( itr );
         ++i;
      }

      if ( itr < end ) return itr;
   }
   else // n < 0
   {
      char const* beg = begin_c_( chars );
      char const* itr = end_c_( chars );
      int64_t i = 0;
      while ( itr > beg )
      {
         --itr;
         if ( is_utf8_head_c( *itr ) )
         {
            --i;
            if ( i == n ) return itr;
         }
      }
   }

   return NULL;
}

/*******************************************************************************
 algo
*******************************************************************************/

int64_t count_runes_c( cChars chars )
{
   int64_t result = 0;
   {
      cRune r;
      char const* itr = next_rune_c( chars, NULL, &r );
      char const* lastValid = itr;
      while ( itr != NULL )
      {
         lastValid = itr;
         ++result;
         itr = next_rune_c( chars, itr, &r );
      }

      if ( lastValid != last_rune_c( chars ) )
      {
         return -1;
      }
   }

   return result;
}

cVarRuneSlice fill_rune_slice_c( cVarRuneSlice dst, cChars src )
{
   if ( is_empty_c_( dst ) ) return dst;

   cRune r;
   int64_t i = 0;
   iterate_runes_c_( itr, &r, src )
   {   
      dst.v[i] = r;
      if ( i == dst.s ) break;

      ++i;
   }
   dst.s = i;

   return dst;
}

char const* find_any_rune_c( cChars chars, cChars set )
{
   cRune out;
   iterate_runes_c_( outItr, &out, chars )
   {
      cRune in;
      iterate_runes_c_( inItr, &in, set )
      {
         if ( eq_rune_c( out, in ) )
         {
            return outItr;
         }
      }
   }
   return NULL;
}

char const* find_rune_c( cChars chars, cRune r )
{
   cRune tmp;
   iterate_runes_c_( itr, &tmp, chars )
   {
      if ( eq_rune_c( r, tmp ) )
      {
         return itr;
      }
   }
   return NULL;
}

cChars left_runes_c( cChars chars, int64_t maxLen )
{
   must_be_positive_c_( maxLen );

   if ( is_empty_c_( chars ) or maxLen == 0 ) return (cChars)empty_c_();

   if ( chars.s <= maxLen ) return chars;

   char const* end = nth_rune_c( chars, maxLen );
   if ( end == NULL ) return chars;

   return (cChars)atween_c_( begin_c_( chars ), end );
}

cChars mid_runes_c( cChars chars, int64_t index )
{
   must_be_positive_c_( index );

   if ( is_empty_c_( chars ) or chars.s <= index ) return (cChars)empty_c_();

   if ( index == 0 ) return chars;

   char const* beg = nth_rune_c( chars, index );
   if ( beg == NULL ) return (cChars)empty_c_();

   return (cChars)atween_c_( beg, end_c_( chars ) );
}

cChars right_runes_c( cChars chars, int64_t maxLen )
{
   must_be_positive_c_( maxLen );

   if ( is_empty_c_( chars ) or maxLen == 0 ) return (cChars)empty_c_();

   if ( chars.s <= maxLen ) return chars;

   char const* beg = nth_rune_c( chars, -maxLen );
   if ( beg == NULL ) return chars;

   return (cChars)atween_c_( beg, end_c_( chars ) );
}

cChars sub_runes_c( cChars chars, int64_t begIdx, int64_t endIdx )
{
   must_be_positive_c_( begIdx );
   must_be_positive_c_( endIdx );

   char const* beg = nth_rune_c( chars, begIdx );
   char const* end = nth_rune_c( chars, endIdx - 1 );
   if ( beg == NULL or end == NULL ) return (cChars)empty_c_();

   end = move_rune_ptr( end );
   if ( end > end_c_( chars ) ) return (cChars)empty_c_();

   return (cChars)atween_c_( beg, end );
}
