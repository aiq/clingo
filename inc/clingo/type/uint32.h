#ifndef CLINGO_TYPE_UINT32_H
#define CLINGO_TYPE_UINT32_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"
#include "clingo/type/c_ByteOrder.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   uint32_t,   // Type
   cUint32s,   // SliceType
   cVarUint32s // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_uint32_c( uint32_t a, uint32_t b )
{
   return ( a < b ) ? -1
                    : ( a == b ) ? 0
                                 : 1;
}

#define uint32_c_( Value )                                                     \
(                                                                              \
   (uint32_t)(Value)                                                           \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_uint32_c,   // FuncName
   int64_t,             // FromType
   uint32_t,            // ToType
   0,                   // MinValue
   UINT32_MAX           // MaxValue
)

CLINGO_API inline CONV_C_(
   uint64_to_uint32_c,  // FuncName
   uint64_t,            // FromType
   uint32_t,            // ToType
   0,                   // MinValue
   UINT32_MAX           // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

CLINGO_API inline uint32_t swap_uint32_c( uint32_t val )
{
   return swap_four_bytes_c_( val );
}
CLINGO_API inline uint32_t swap_uint32_from_c( uint32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_four_bytes_c_( val );
}
CLINGO_API inline uint32_t swap_uint32_to_c( uint32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_four_bytes_c_( val );
}

/*******************************************************************************
 math
*******************************************************************************/

CLINGO_API inline uint32_t next_pow2_uint32_c( uint32_t val )
{
   --val;
   val |= val >> 1;
   val |= val >> 2;
   val |= val >> 4;
   val |= val >> 8;
   val |= val >> 16;
   ++val;

   return val;
}

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int cmp_uint32s_c( cUint32s a, cUint32s b );

CLINGO_API int64_t count_eq_uint32_c( cUint32s slice, uint32_t val );

CLINGO_API uint32_t const* find_uint32_c( cUint32s slice, uint32_t val );

CLINGO_API uint32_t const* max_uint32_c( cUint32s slice );

CLINGO_API uint32_t const* min_uint32_c( cUint32s slice );

CLINGO_API bool prod_uint32_c( cUint32s slice, uint64_t res[static 1] );

CLINGO_API void qsort_uint32s_c( cVarUint32s slice );

CLINGO_API void reverse_uint32s_c( cVarUint32s slice );

CLINGO_API void rotate_uint32s_c( cVarUint32s slice, int64_t distance );

CLINGO_API bool sum_uint32_c( cUint32s slice, uint64_t res[static 1] );

#endif
