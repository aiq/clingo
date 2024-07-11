#include "clingo/type/double.h"

#include <iso646.h>
#include <stdint.h>

#include "_/prod.h"
#include "_/sum.h"
#include "clingo/lang/algo.h"
#include "clingo/lang/func.h"
#include "clingo/type/float.h"
#include "clingo/type/uint16.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_double_c( double a, double b );

bool double_to_float_c( double d, float f[static 1] )
{
   *f = float_c_( d );
   double const tmpD = double_c_( *f );
   return tmpD == d;
}

bool eq_double_c( double d1, double d2, double epsilon )
{
   double const upperBound = d1 + epsilon;
   double const lowerBound = d1 - epsilon;

   return lowerBound <= d2 && d2 <= upperBound;
}

/*******************************************************************************
 info
*******************************************************************************/

double build_double_c( cDoubleInfo info )
{
   uint64_t sign = uint64_c_( info.sign ) << 63;
   uint64_t exponent = uint64_c_( info.exponent ) << 52;

   return unpack_double_c( sign | exponent | info.mantissa );
}

cDoubleInfo double_info_c( double d )
{
   uint64_t val = pack_double_c( d );
   uint64_t sign = val & build_uint64_c_( 0x80000000, 0x00000000 );
   uint64_t exponent = val & build_uint64_c_( 0x7FF00000, 0x00000000 );
   uint64_t mantissa = val & build_uint64_c_( 0x000FFFFF, 0xFFFFFFFF );

   cDoubleInfo info;
   info.sign = ( sign == 0 ) ? 0 : 1;
   info.exponent = uint16_c_( ( val & exponent ) >> 52 );
   info.mantissa = val & mantissa;
   return info;
}

/*******************************************************************************
 swap
*******************************************************************************/

double swap_double_c( double d )
{
   union { double d; uint64_t u; } v;

   v.d = d;
   v.u = swap_eight_bytes_c_( v.u );

   return v.d;
}

double swap_double_to_c( double d, c_ByteOrder order )
{
   return system_order_is_c( order ) ? d
                                     : swap_double_c( d );
}

double swap_double_from_c( double d, c_ByteOrder order )
{
   return system_order_is_c( order ) ? d
                                     : swap_double_c( d );
}

/*******************************************************************************
 pack
*******************************************************************************/

uint64_t pack_double_c( double d )
{
   union { double d; uint64_t u; } v;
   v.d = d;
   return v.u;
}

double unpack_double_c( uint64_t u )
{
   union { double d; uint64_t u; } v;
   v.u = u;
   return v.d;
}

/*******************************************************************************
 algo
*******************************************************************************/

FIND_VAL_C_(
   find_double_c, // FuncName
   cDoubleSlice,  // SliceType
   double const,  // ValueType
   double,        // SearchType
   cmp_double_c,  // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MAX_C_(
   max_double_c,  // FuncName
   cDoubleSlice,  // SliceType
   double const,  // ValueType
   cmp_double_c,  // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_double_c,  // FuncName
   cDoubleSlice,  // SliceType
   double const,  // ValueType
   cmp_double_c,  // CmpFunc
   do_deref_c_    // DoDeref
)

static bool mul_func( double a, double b, double res[static 1] )
{
   *res = a * b;
   return true;
}

PROD_C_(
   prod_double_c, // FuncName
   cDoubleSlice,  // SliceType
   double,        // ValueType
   double,        // ResType
   mul_func       // MulFunc
)

static bool add_func( double a, double b, double res[static 1] )
{
   *res = a + b;
   return true;
}

SUM_C_(
   sum_double_c,  // FuncName
   cDoubleSlice,  // SliceType
   double,        // ValueType
   double,        // ResType
   add_func       // AddFunc
)

