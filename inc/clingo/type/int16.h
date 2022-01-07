#ifndef CLINGO_TYPE_INT16_H
#define CLINGO_TYPE_INT16_H

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
   int16_t,             // Type
   cInt16Slice,         // SliceType
   int16_slice_c,       // FuncName
   cVarInt16Slice,      // VarSliceType
   var_int16_slice_c    // VarFuncName
)

CHUNK_DEF_C_(
   int16_t,             // Type
   cInt16Chunk,         // ChunkType
   cInt16Slice,         // SliceType
   int16_chunk_c,       // FuncName
   cVarInt16Chunk,      // VarChunkType
   cVarInt16Slice,      // VarSliceType
   var_int16_chunk_c    // VarFuncName
)

WINDOW_DEF_C_(
   int16_t,             // Type
   cInt16Window,        // WindowType
   cInt16Slice,         // SliceType
   int16_window_c,      // FuncName
   cVarInt16Window,     // VarWindowType
   cVarInt16Slice,      // VarSliceType
   var_int16_window_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

inline int cmp_int16_c( int16_t a, int16_t b )
{
   return a < b ? -1
                : a > b ? 1
                        : 0;
}

#define int16_c_( Value )                                                      \
(                                                                              \
   (int16_t)(Value)                                                            \
)

/*******************************************************************************
 conv
*******************************************************************************/

inline CONV_C_(
   int64_to_int16_c, // FuncName
   int64_t,          // FromType
   int16_t,          // ToType
   INT16_MIN,        // MinValue
   INT16_MAX         // MaxValue
)

inline CONV_C_(
   uint64_to_int16_c,   // FuncName
   uint64_t,            // FromType
   int16_t,             // ToType
   0,                   // MinValue
   INT16_MAX            // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

inline int16_t swap_int16_c( int16_t val )
{
   union { int16_t i; uint16_t u; } v;

   v.i = val;
   v.u = swap_two_bytes_c_( v.u );

   return v.i;
}
inline int16_t swap_int16_from_c( int16_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int16_c( val );
}
inline int16_t swap_int16_to_c( int16_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_int16_c( val );
}

/*******************************************************************************
 algo
*******************************************************************************/

int cmp_int16_slice_c( cInt16Slice a, cInt16Slice b );

int64_t count_eq_int16_c( cInt16Slice slice, int16_t val );

int16_t const* find_int16_c( cInt16Slice slice, int16_t val );

int16_t const* max_int16_c( cInt16Slice slice );

int16_t const* min_int16_c( cInt16Slice slice );

bool prod_int16_c( cInt16Slice slice, int64_t res[static 1] );

void qsort_int16_slice_c( cVarInt16Slice slice );

void reverse_int16_slice_c( cVarInt16Slice slice );

void rotate_int16_slice_c( cVarInt16Slice slice, int64_t distance );

bool sum_int16_c( cInt16Slice slice, int64_t res[static 1] );

#endif
