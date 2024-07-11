#include "write_num.h"

#include <iso646.h>
#include <stdio.h>

#include "clingo/io/cScanner.h"
#include "clingo/lang/func.h"
#include "clingo/type/uint64.h"

/*******************************************************************************

*******************************************************************************/

uint64_t plusval_c( int64_t val )
{
   if ( val >= 0 )
   {
      return uint64_c_( val );
   }

   if ( val == INT64_MIN )
   {
      uint64_t result = INT64_MAX;
      return result + 1;
   }

   abs_c_( val, &val );
   return uint64_c_( val );
}

int64_t write_bin_c( uint64_t val, bool upper, cVarChars buf )
{
   if ( buf.s == 0 )
   {
      return 0;
   }

   char const one = '1';
   char const zero = upper ? '0' : 'o';

   int64_t len = 0;

   int8_t lshift = 0;
   while ( lshift <= 63 and len < buf.s )
   {
      uint64_t c = ( val << lshift ) >> 63;
      if ( len > 0 or c != 0 )
      {
         *(buf.v + len) = c == 1 ? one
                                 : zero;
         ++len;
      }

      ++lshift;;
   }

   if ( len == 0 )
   {
      *(buf.v) = zero;
      ++len;
   }

   return len;
}

int64_t write_hex_c( uint64_t val, bool upper, cVarChars buf )
{
   if ( buf.s == 0 )
   {
      return 0;
   }

   static char const* upperHex = "0123456789ABCDEF";
   static char const* lowerHex = "0123456789abcdef";

   char const* alphabet = upper ? upperHex
                                : lowerHex;

   int64_t len = 0;

   int8_t lshift = 0;
   while ( lshift <= 60 and len < buf.s )
   {
      uint64_t c = ( val << lshift ) >> 60;
      if ( len > 0 or c != 0 )
      {
         *(buf.v + len) = alphabet[ c ];
         ++len;
      }

      lshift += 4;
   }

   if ( len == 0 )
   {
      *(buf.v) = '0';
      ++len;
   }

   return len;
}

int64_t write_oct_c( uint64_t val, cVarChars buf )
{
   if ( buf.s == 0 )
   {
      return 0;
   }

   static char const* alphabet = "01234567";

   int64_t len = 0;

   uint64_t c = val >> 63;
   if ( len < buf.s and c != 0 )
   {
      *(buf.v) = alphabet[ c ];
      ++len;
   };

   int8_t lshift = 1;
   while ( lshift <= 61 and len < buf.s )
   {
      c = ( val << lshift ) >> 61;
      if ( len > 0 or c != 0 )
      {
         *(buf.v + len) = alphabet[ c ];
         ++len;
      }

      lshift += 3;
   }

   if ( len == 0 )
   {
      *(buf.v) = '0';
      ++len;
   }

   return len;
}

