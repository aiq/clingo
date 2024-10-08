#ifndef CLINGO_TYPE_INT32_H
#define CLINGO_TYPE_INT32_H

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
   int32_t,    // Type
   cInt32s,    // SliceType
   cVarInt32s  // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_int32_c( int32_t a, int32_t b )
{
   return a < b ? -1 :
          a > b ? 1 :
                  0;
}

#define int32_c_( Value )                                                      \
(                                                                              \
   (int32_t)(Value)                                                            \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_int32_c, // FuncName
   int64_t,          // FromType
   int32_t,          // ToType
   INT32_MIN,        // MinValue
   INT32_MAX         // MaxValue
)

CLINGO_API inline CONV_C_(
   uint64_to_int32_c,   // FuncName
   uint64_t,            // FromType
   int32_t,             // ToType
   0,                   // MinValue
   INT32_MAX            // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

CLINGO_API inline int32_t swap_int32_c( int32_t val )
{
   union { int32_t i; uint32_t u; } v;

   v.i = val;
   v.u = swap_four_bytes_c_( v.u );

   return v.i;
}
CLINGO_API inline int32_t swap_int32_from_c( int32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int32_c( val  );
}
CLINGO_API inline int32_t swap_int32_to_c( int32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int32_c( val  );
}

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int32_t const* bsearch_int32_c( cInt32s slice, int32_t val );

CLINGO_API int cmp_int32s_c( cInt32s a, cInt32s b );

CLINGO_API int64_t count_eq_int32_c( cInt32s slice, int32_t val );

CLINGO_API int32_t const* find_int32_c( cInt32s slice, int32_t val );

CLINGO_API int32_t const* max_int32_c( cInt32s slice );

CLINGO_API int32_t const* min_int32_c( cInt32s slice );

CLINGO_API bool prod_int32_c( cInt32s slice, int64_t res[static 1] );

CLINGO_API void qsort_int32s_c( cVarInt32s slice );

CLINGO_API bool remove_int32_c( cVarInt32s slice[static 1], int64_t pos );

CLINGO_API void reverse_int32s_c( cVarInt32s slice );

CLINGO_API void rotate_int32s_c( cVarInt32s slice, int64_t distance );

CLINGO_API bool sum_int32_c( cInt32s slice, int64_t res[static 1] );

CLINGO_API bool take_int32_c( cVarInt32s slice[static 1],
                              int64_t pos,
                              int32_t val[static 1] );

#endif
