#include "clingo/type/float.h"

#include <iso646.h>
#include <stdint.h>

#include "_/prod.h"
#include "_/sum.h"
#include "clingo/lang/algo.h"
#include "clingo/lang/func.h"
#include "clingo/type/uint8.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_float_c( float a, float b );

bool eq_float_c( float f1, float f2, float epsilon )
{
   float const upperBound = f1 + epsilon;
   float const lowerBound = f1 - epsilon;

   return ( lowerBound <= f2 && f2 <= upperBound ) ? true
                                                   : false;
}

/*******************************************************************************
 info
*******************************************************************************/

float build_float_c( cFloatInfo info )
{
   uint32_t sign = uint32_c_( info.sign ) << 31;
   uint32_t exponent = uint32_c_( info.exponent ) << 23;

   return unpack_float_c( sign | exponent | info.mantissa );
}

cFloatInfo float_info_c( float f )
{
   uint32_t val = pack_float_c( f );
   uint32_t sign = val & 0x80000000;
   uint32_t exponent = val & 0x7F800000;
   uint32_t mantissa = val & 0x007FFFFF;

   cFloatInfo info;
   info.sign = ( sign == 0 ) ? 0 : 1;
   info.exponent = uint8_c_( ( val & exponent ) >> 23 );
   info.mantissa = val & mantissa;
   return info;
}

/*******************************************************************************
 swap
*******************************************************************************/

float swap_float_c( float f )
{
   union { float f; uint32_t u; } v;

   v.f = f;
   v.u = swap_four_bytes_c_( v.u );

   return v.f;
}

float swap_float_to_c( float f, c_ByteOrder order )
{
   return system_order_is_c( order ) ? f
                                     : swap_float_c( f );
}

float swap_float_from_c( float f, c_ByteOrder order )
{
   return system_order_is_c( order ) ? f
                                     : swap_float_c( f );
}

/*******************************************************************************
 pack
*******************************************************************************/

uint32_t pack_float_c( float f )
{
   union { float f; uint32_t u; } v;
   v.f = f;
   return v.u;
}

float unpack_float_c( uint32_t u )
{
   union { float f; uint32_t u; } v;
   v.u = u;
   return v.f;
}

/*******************************************************************************
 algo
*******************************************************************************/

FIND_VAL_C_(
   find_float_c,  // FuncName
   cFloats,   // SliceType
   float const,   // ValueType
   float,         // SearchType
   cmp_float_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MAX_C_(
   max_float_c,   // FuncName
   cFloats,   // SliceType
   float const,   // ValueType
   cmp_float_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_float_c,   // FuncName
   cFloats,   // SliceType
   float const,   // ValueType
   cmp_float_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

static bool mul_func( float a, float b, float res[static 1] )
{
   *res = a * b;
   return true;
}

PROD_C_(
   prod_float_c,  // FuncName
   cFloats,   // SliceType
   float,         // ValueType
   float,         // ResType
   mul_func       // MulFunc
)

static bool add_func( float a, float b, float res[static 1] )
{
   *res = a + b;
   return true;
}

SUM_C_(
   sum_float_c,   // FuncName
   cFloats,   // SliceType
   float,         // ValueType
   float,         // ResType
   add_func       // AddFunc
)

/*******************************************************************************

*******************************************************************************/

float trunc_float_c( float f, float* diff )
{
   float res = truncf( f );
   if ( diff != NULL )
   {
      *diff = f - res;
   }
   return res;
}