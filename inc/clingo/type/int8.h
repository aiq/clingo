#ifndef CLINGO_TYPE_INT8_H
#define CLINGO_TYPE_INT8_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   int8_t,           // Type
   cInt8Slice,       // SliceType
   cVarInt8Slice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_int8_c( int8_t a, int8_t b )
{
   return a - b;
}

#define int8_c_( Value )                                                       \
(                                                                              \
   (int8_t)(Value)                                                             \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_int8_c,  // FuncName
   int64_t,          // FromType
   int8_t,           // ToType
   INT8_MIN,         // MinValue
   INT8_MAX          // MaxValue
)

CLINGO_API inline CONV_C_(
   uint64_to_int8_c, // FuncName
   uint64_t,         // FromType
   int8_t,           // ToType
   0,                // MinValue
   INT8_MAX          // MaxValue
)

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int cmp_int8_slice_c( cInt8Slice a, cInt8Slice b );

CLINGO_API int64_t count_eq_int8_c( cInt8Slice slice, int8_t val );

CLINGO_API int8_t const* find_int8_c( cInt8Slice slice, int8_t val );

CLINGO_API int8_t const* max_int8_c( cInt8Slice slice );

CLINGO_API int8_t const* min_int8_c( cInt8Slice slice );

CLINGO_API bool prod_int8_c( cInt8Slice slice, int64_t res[static 1] );

CLINGO_API void qsort_int8_slice_c( cVarInt8Slice slice );

CLINGO_API void reverse_int8_slice_c( cVarInt8Slice slice );

CLINGO_API void rotate_int8_slice_c( cVarInt8Slice slice, int64_t distance );

CLINGO_API bool sum_int8_c( cInt8Slice slice, int64_t res[static 1] );

#endif
