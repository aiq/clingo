#ifndef CLINGO_TYPE_CHAR_H
#define CLINGO_TYPE_CHAR_H

#include <stdbool.h>
#include <string.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

typedef bool ( *c_check_char )( char c );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define char_c_( Value )                                                       \
(                                                                              \
   (char)(Value)                                                               \
)

CLINGO_API inline int cmp_char_c( char a, char b )
{
   return a - b;
}

/*******************************************************************************
 interpret
*******************************************************************************/

CLINGO_API inline int8_t dec_char_value_c( char c )
{
   if ( in_range_c_( '0', c, '9' ) )
   {
      return c - '0';
   }

   return -1;
}

CLINGO_API inline int8_t hex_char_value_c( char c )
{
   if ( in_range_c_( '0', c, '9' ) )
   {
      return c - '0';
   }
   else if ( in_range_c_( 'A', c, 'F' ) )
   {
      return ( c - 'A' ) + 10 ;
   }
   else if ( in_range_c_( 'a', c, 'f' ) )
   {
      return ( c - 'a' ) + 10;
   }

   return -1;
}

CLINGO_API inline int8_t oct_char_value_c( char c )
{
   if ( in_range_c_( '0', c, '7' ) )
   {
      return c - '0';
   }

   return -1;
}

/*******************************************************************************
 check
*******************************************************************************/

CLINGO_API inline bool char_is_cntrl_c( char c )
{
   return c == 0x7f or in_range_c_( 0x00, c, 0x1f );
}

CLINGO_API inline bool char_is_digit_c( char c )
{
   return in_range_c_( '0', c, '9' );
}

CLINGO_API inline bool char_is_graph_c( char c )
{
   return in_range_c_( '!', c, '~' );
}

CLINGO_API inline bool char_is_hex_c( char c )
{
   return in_range_c_( '0', c, '9' ) or
          in_range_c_( 'a', c, 'f' ) or
          in_range_c_( 'A', c, 'F' );
}

CLINGO_API inline bool char_is_lower_c( char c )
{
   return in_range_c_( 'a', c, 'z' );
}

CLINGO_API inline bool char_is_print_c( char c )
{
   return not char_is_cntrl_c( c );
}

CLINGO_API inline bool char_is_punct_c( char c )
{
   return in_range_c_( '!', c, '/' ) or
          in_range_c_( ':', c, '@' ) or
          in_range_c_( '[', c, '`' ) or
          in_range_c_( '{', c, '~' );
}

CLINGO_API inline bool char_is_space_c( char c )
{
   return c == ' ' or in_range_c_( 0x09, c, 0x0d );
}

CLINGO_API inline bool char_is_upper_c( char c )
{
   return in_range_c_( 'A', c, 'Z' );
}

CLINGO_API inline bool char_is_alpha_c( char c )
{
   return char_is_lower_c( c ) or char_is_upper_c( c );
}

CLINGO_API inline bool char_is_alnum_c( char c )
{
   return char_is_digit_c( c ) or char_is_alpha_c( c );
}

#endif
