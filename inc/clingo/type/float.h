#ifndef CLINGO_TYPE_FLOAT_H
#define CLINGO_TYPE_FLOAT_H

#include <float.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"
#include "clingo/type/c_ByteOrder.h"
#include "clingo/type/uint32.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cFloatInfo
{
   uint8_t sign;
   uint8_t exponent;
   uint32_t mantissa;
};
typedef struct cFloatInfo cFloatInfo;

SLICES_C_(
   float,               // Type
   cFloatSlice,         // SliceType
   cVarFloatSlice       // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_float_c( float a, float b )
{
   return ( a < b ) ? -1
                    : ( a == b ) ? 0
                                 : 1;
}

#define eq_float_c_( F1, F2 )                                                  \
   eq_float_c( F1, F2, FLT_EPSILON )
CLINGO_API bool eq_float_c( float f1, float f2, float epsilon );

#define float_c_( Value )                                                      \
(                                                                              \
   (float)(Value)                                                              \
)

/*******************************************************************************
 info
*******************************************************************************/

CLINGO_API float build_float_c( cFloatInfo info );

CLINGO_API cFloatInfo float_info_c( float f );

/*******************************************************************************

*******************************************************************************/

CLINGO_API float swap_float_c( float f );
CLINGO_API float swap_float_from_c( float f, c_ByteOrder order );
CLINGO_API float swap_float_to_c( float f, c_ByteOrder order );

/*******************************************************************************

*******************************************************************************/

CLINGO_API uint32_t pack_float_c( float f );
CLINGO_API float unpack_float_c( uint32_t u );

/*******************************************************************************

*******************************************************************************/

CLINGO_API float const* find_float_c( cFloatSlice slice, float f );

CLINGO_API float const* max_float_c( cFloatSlice slice );

CLINGO_API float const* min_float_c( cFloatSlice slice );

CLINGO_API bool prod_float_c( cFloatSlice slice, float res[static 1] );

CLINGO_API bool sum_float_c( cFloatSlice slice, float res[static 1] );

#endif
