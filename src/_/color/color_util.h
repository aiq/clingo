#ifndef CLINGO_INTERN_COLOR_UTIL_H
#define CLINGO_INTERN_COLOR_UTIL_H

#include "clingo/type/float.h"
#include "clingo/type/uint8.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static inline uint8_t uint8_from_percent_c( float f )
{
   if ( f > 1.0f ) return UINT8_MAX;

   if ( f < 0.0f ) return 0;

   float v = roundf( float_c_( UINT8_MAX ) * f );
   return uint8_c_( v );
}

static inline float uint8_in_percent_c( uint8_t u8 )
{
   return ( 1.0f / 255.0f ) * float_c_( u8 );
}

#endif
