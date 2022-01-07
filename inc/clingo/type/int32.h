#ifndef CLINGO_TYPE_INT32_H
#define CLINGO_TYPE_INT32_H

#include <stdint.h>

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
   int32_t,             // Type
   cInt32Slice,         // SliceType
   int32_slice_c,       // FuncName
   cVarInt32Slice,      // VarSliceType
   var_int32_slice_c    // VarFuncName
)

CHUNK_DEF_C_(
   int32_t,             // Type
   cInt32Chunk,         // ChunkType
   cInt32Slice,         // SliceType
   int32_chunk_c,       // FuncName
   cVarInt32Chunk,      // VarChunkType
   cVarInt32Slice,      // VarSliceType
   var_int32_chunk_c    // VarFuncName
)

WINDOW_DEF_C_(
   int32_t,             // Type
   cInt32Window,        // WindowType
   cInt32Slice,         // SliceType
   int32_window_c,      // FuncName
   cVarInt32Window,     // VarWindowType
   cVarInt32Slice,      // VarSliceType
   var_int32_window_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

inline int cmp_int32_c( int32_t a, int32_t b )
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

inline CONV_C_(
   int64_to_int32_c, // FuncName
   int64_t,          // FromType
   int32_t,          // ToType
   INT32_MIN,        // MinValue
   INT32_MAX         // MaxValue
)

inline CONV_C_(
   uint64_to_int32_c,   // FuncName
   uint64_t,            // FromType
   int32_t,             // ToType
   0,                   // MinValue
   INT32_MAX            // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

inline int32_t swap_int32_c( int32_t val )
{
   union { int32_t i; uint32_t u; } v;

   v.i = val;
   v.u = swap_four_bytes_c_( v.u );

   return v.i;
}
inline int32_t swap_int32_from_c( int32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int32_c( val  );
}
inline int32_t swap_int32_to_c( int32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int32_c( val  );
}

/*******************************************************************************
 algo
*******************************************************************************/

int32_t const* bsearch_int32_c( cInt32Slice slice, int32_t val );

int cmp_int32_slice_c( cInt32Slice a, cInt32Slice b );

int64_t count_eq_int32_c( cInt32Slice slice, int32_t val );

int32_t const* find_int32_c( cInt32Slice slice, int32_t val );

int32_t const* max_int32_c( cInt32Slice slice );

int32_t const* min_int32_c( cInt32Slice slice );

bool prod_int32_c( cInt32Slice slice, int64_t res[static 1] );

void qsort_int32_slice_c( cVarInt32Slice slice );

void reverse_int32_slice_c( cVarInt32Slice slice );

void rotate_int32_slice_c( cVarInt32Slice slice, int64_t distance );

bool sum_int32_c( cInt32Slice slice, int64_t res[static 1] );

#endif
