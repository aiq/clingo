#ifndef CLINGO_TYPE_CHAR_H
#define CLINGO_TYPE_CHAR_H

#include <stdbool.h>
#include <string.h>

#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

typedef int ( *c_check_char )( int c );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define char_c_( Value )                                                       \
(                                                                              \
   (char)(Value)                                                               \
)

inline int cmp_char_c( char a, char b )
{
   return a - b;
}

/*******************************************************************************
 interpret
*******************************************************************************/

inline int8_t dec_char_value_c( char c )
{
   if ( in_range_c_( '0', c, '9' ) )
   {
      return c - '0';
   }

   return -1;
}

inline int8_t hex_char_value_c( char c )
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

inline int8_t oct_char_value_c( char c )
{
   if ( in_range_c_( '0', c, '7' ) )
   {
      return c - '0';
   }

   return -1;
}

#endif
