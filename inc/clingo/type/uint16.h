#ifndef CLINGO_TYPE_UINT16_H
#define CLINGO_TYPE_UINT16_H

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
   uint16_t,   // Type
   cUint16s,   // SliceType
   cVarUint16s // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_uint16_c( uint16_t a, uint16_t b )
{
   return a - b;
}

#define uint16_c_( Value )                                                     \
(                                                                              \
   (uint16_t)(Value)                                                           \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_uint16_c,   // FuncName
   int64_t,             // FromType
   uint16_t,            // ToType
   0,                   // MinValue
   UINT16_MAX           // MaxValue
)

CLINGO_API inline CONV_C_(
   uint64_to_uint16_c,  // FuncName
   uint64_t,            // FromType
   uint16_t,            // ToType
   0,                   // MinValue
   UINT16_MAX           // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

CLINGO_API inline uint16_t swap_uint16_c( uint16_t val )
{
   return swap_two_bytes_c_( val );
}
CLINGO_API inline uint16_t swap_uint16_from_c( uint16_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_two_bytes_c_( val );
}
CLINGO_API inline uint16_t swap_uint16_to_c( uint16_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_two_bytes_c_( val );
}

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int cmp_uint16s_c( cUint16s a, cUint16s b );

CLINGO_API int64_t count_eq_uint16_c( cUint16s slice, uint16_t val );

CLINGO_API uint16_t const* find_uint16_c( cUint16s slice, uint16_t val );

CLINGO_API uint16_t const* max_uint16_c( cUint16s slice );

CLINGO_API uint16_t const* min_uint16_c( cUint16s slice );

CLINGO_API bool prod_uint16_c( cUint16s slice, uint64_t res[static 1] );

CLINGO_API void qsort_uint16s_c( cVarUint16s slice );

CLINGO_API void reverse_uint16s_c( cVarUint16s slice );

CLINGO_API void rotate_uint16s_c( cVarUint16s slice, int64_t distance );

CLINGO_API bool sum_uint16_c( cUint16s slice, uint64_t res[static 1] );

#endif
