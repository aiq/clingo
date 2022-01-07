#ifndef CLINGO_TYPE_CBYTE_H
#define CLINGO_TYPE_CBYTE_H

#include <inttypes.h>
#include <iso646.h>
#include <stdbool.h>

#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

typedef uint8_t cByte;

typedef bool ( *c_check_byte )( cByte b );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define byte_c_( Value )                                                       \
(                                                                              \
   (cByte)(Value)                                                              \
)

inline int cmp_byte_c( cByte a, cByte b )
{
   return a < b ? -1 :
          a > b ? 1 :
                  0;
}

/*******************************************************************************
 bit
*******************************************************************************/

inline cByte byte_as_bit_c( cByte byte )
{
   return byte & 1;
}

inline cByte get_byte_bit_c( cByte byte, int64_t pos )
{
   must_be_in_range_c_( 0, pos, 7 );

   return byte_as_bit_c( byte >> ( 7 - pos ) );
}

inline cByte set_byte_bit_c( cByte byte, int64_t pos, cByte bit )
{
   must_be_in_range_c_( 0, pos, 7 );

   if ( byte_as_bit_c( bit ) == 1 )
   {
      byte |= ( (cByte)0x80 >> ( pos ) );
   }
   else
   {
      byte &= ~( (cByte)0x80 >> ( pos ) );
   }

   return byte;
}

inline cByte toggle_byte_bit_c( cByte byte, int64_t pos )
{
   must_be_in_range_c_( 0, pos, 7 );

   cByte bit = get_byte_bit_c( byte, pos );
   return set_byte_bit_c( byte, pos, byte_as_bit_c( bit + 1 ) );
}

#endif
