#ifndef CLINGO_TYPE_UINT32_H
#define CLINGO_TYPE_UINT32_H

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
   uint32_t,            // Type
   cUint32Slice,        // SliceType
   uint32_slice_c,      // FuncName
   cVarUint32Slice,     // VarSliceType
   var_uint32_slice_c   // VarFuncName
)

CHUNK_DEF_C_(
   uint32_t,            // Type
   cUint32Chunk,        // ChunkType
   cUint32Slice,        // SliceType
   uint32_chunk_c,      // FuncName
   cVarUint32Chunk,     // VarChunkType
   cVarUint32Slice,     // VarSliceType
   var_uint32_chunk_c   // VarFuncName
)

WINDOW_DEF_C_(
   uint32_t,            // Type
   cUint32Window,       // WindowType
   cUint32Slice,        // SliceType
   uint32_window_c,     // FuncName
   cVarUint32Window,    // VarWindowType
   cVarUint32Slice,     // VarSliceType
   var_uint32_window_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

inline int cmp_uint32_c( uint32_t a, uint32_t b )
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

inline CONV_C_(
   int64_to_uint32_c,   // FuncName
   int64_t,             // FromType
   uint32_t,            // ToType
   0,                   // MinValue
   UINT32_MAX           // MaxValue
)

inline CONV_C_(
   uint64_to_uint32_c,  // FuncName
   uint64_t,            // FromType
   uint32_t,            // ToType
   0,                   // MinValue
   UINT32_MAX           // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

inline uint32_t swap_uint32_c( uint32_t val )
{
   return swap_four_bytes_c_( val );
}
inline uint32_t swap_uint32_from_c( uint32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_four_bytes_c_( val );
}
inline uint32_t swap_uint32_to_c( uint32_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_four_bytes_c_( val );
}

/*******************************************************************************
 math
*******************************************************************************/

inline uint32_t next_pow2_uint32_c( uint32_t val )
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

int cmp_uint32_slice_c( cUint32Slice a, cUint32Slice b );

int64_t count_eq_uint32_c( cUint32Slice slice, uint32_t val );

uint32_t const* find_uint32_c( cUint32Slice slice, uint32_t val );

uint32_t const* max_uint32_c( cUint32Slice slice );

uint32_t const* min_uint32_c( cUint32Slice slice );

bool prod_uint32_c( cUint32Slice slice, uint64_t res[static 1] );

void qsort_uint32_slice_c( cVarUint32Slice slice );

void reverse_uint32_slice_c( cVarUint32Slice slice );

void rotate_uint32_slice_c( cVarUint32Slice slice, int64_t distance );

bool sum_uint32_c( cUint32Slice slice, uint64_t res[static 1] );

#endif
