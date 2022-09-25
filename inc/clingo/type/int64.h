#ifndef CLINGO_TYPE_INT64_H
#define CLINGO_TYPE_INT64_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"
#include "clingo/type/c_ByteOrder.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   int64_t,             // Type
   cInt64Slice,         // SliceType
   cVarInt64Slice       // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_int64_c( int64_t a, int64_t b )
{
   return a < b ? -1
                : a > b ? 1
                        : 0;
}

#define int64_c_( Value )                                                      \
(                                                                              \
   (int64_t)(Value)                                                            \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   uint64_to_int64_c,   // FuncName
   uint64_t,            // FromType
   int64_t,             // ToType
   0,                   // MinValue
   INT64_MAX            // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

CLINGO_API inline int64_t swap_int64_c( int64_t val )
{
   union { int64_t i; uint64_t u; } v;

   v.i = val;
   v.u = swap_eight_bytes_c_( v.u );

   return v.i;
}
CLINGO_API inline int64_t swap_int64_from_c( int64_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int64_c( val );
}
CLINGO_API inline int64_t swap_int64_to_c( int64_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int64_c( val );
}

/*******************************************************************************
 math
*******************************************************************************/

CLINGO_API inline uint64_t hash_int64_c( int64_t val )
{
   union { int64_t i; uint64_t u; } v;
   v.i = val;
   return v.u;
}

CLINGO_API inline int64_t next_pow2_int64_c( int64_t val )
{
   --val;
   val |= val >> 1;
   val |= val >> 2;
   val |= val >> 4;
   val |= val >> 8;
   val |= val >> 16;
   val |= val >> 32;
   ++val;

   return val;
}

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int64_t const* bsearch_int64_c( cInt64Slice slice, int64_t val );

CLINGO_API int cmp_int64_slice_c( cInt64Slice a, cInt64Slice b );

CLINGO_API int64_t count_eq_int64_c( cInt64Slice slice, int64_t val );

CLINGO_API int64_t const* find_int64_c( cInt64Slice slice, int64_t val );

CLINGO_API int64_t const* max_int64_c( cInt64Slice slice );

CLINGO_API int64_t const* min_int64_c( cInt64Slice slice );

CLINGO_API bool prod_int64_c( cInt64Slice slice, int64_t res[static 1] );

CLINGO_API void qsort_int64_slice_c( cVarInt64Slice slice );

CLINGO_API void reverse_int64_slice_c( cVarInt64Slice slice );

CLINGO_API void rotate_int64_slice_c( cVarInt64Slice slice, int64_t distance );

CLINGO_API bool sum_int64_c( cInt64Slice slice, int64_t res[static 1] );

#endif
