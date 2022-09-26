#ifndef CLINGO_TYPE_UINT8_H
#define CLINGO_TYPE_UINT8_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   uint8_t,             // Type
   cUint8Slice,         // SliceType
   cVarUint8Slice       // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_uint8_c( uint8_t a, uint8_t b )
{
   return a - b;
}

#define uint8_c_( Value )                                                      \
(                                                                              \
   (uint8_t)(Value)                                                            \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_uint8_c, // FuncName
   int64_t,          // FromType
   uint8_t,          // ToType
   0,                // MinValue
   UINT8_MAX         // MaxValue
)

CLINGO_API inline CONV_C_(
   uint64_to_uint8_c,   // FuncName
   uint64_t,            // FromType
   uint8_t,             // ToType
   0,                   // MinValue
   UINT8_MAX            // MaxValue
)

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int cmp_uint8_slice_c( cUint8Slice a, cUint8Slice b );

CLINGO_API int64_t count_eq_uint8_c( cUint8Slice slice, uint8_t val );

CLINGO_API uint8_t const* find_uint8_c( cUint8Slice slice, uint8_t val );

CLINGO_API uint8_t const* max_uint8_c( cUint8Slice slice );

CLINGO_API uint8_t const* min_uint8_c( cUint8Slice slice );

CLINGO_API bool prod_uint8_c( cUint8Slice slice, uint64_t res[static 1] );

CLINGO_API void qsort_uint8_slice_c( cVarUint8Slice slice );

CLINGO_API void reverse_uint8_slice_c( cVarUint8Slice slice );

CLINGO_API void rotate_uint8_slice_c( cVarUint8Slice slice, int64_t distance );

CLINGO_API bool sum_uint8_c( cUint8Slice slice, uint64_t res[static 1] );

#endif
