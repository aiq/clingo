#ifndef CLINGO_TYPE_INT8_H
#define CLINGO_TYPE_INT8_H

#include <stdint.h>

#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   int8_t,           // Type
   cInt8Slice,       // SliceType
   int8_slice_c,     // FuncName
   cVarInt8Slice,    // VarSliceType
   var_int8_slice_c  // VarFuncName
)

CHUNK_DEF_C_(
   int8_t,           // Type
   cInt8Chunk,       // ChunkType
   cInt8Slice,       // SliceType
   int8_chunk_c,     // FuncName
   cVarInt8Chunk,    // VarChunkType
   cVarInt8Slice,    // VarSliceType
   var_int8_chunk_c  // VarFuncName
)

WINDOW_DEF_C_(
   int8_t,           // Type
   cInt8Window,      // WindowType
   cInt8Slice,       // SliceType
   int8_window_c,    // FuncName
   cVarInt8Window,   // VarWindowType
   cVarInt8Slice,    // VarSliceType
   var_int8_window_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

inline int cmp_int8_c( int8_t a, int8_t b )
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

inline CONV_C_(
   int64_to_int8_c,  // FuncName
   int64_t,          // FromType
   int8_t,           // ToType
   INT8_MIN,         // MinValue
   INT8_MAX          // MaxValue
)

inline CONV_C_(
   uint64_to_int8_c, // FuncName
   uint64_t,         // FromType
   int8_t,           // ToType
   0,                // MinValue
   INT8_MAX          // MaxValue
)

/*******************************************************************************
 algo
*******************************************************************************/

int cmp_int8_slice_c( cInt8Slice a, cInt8Slice b );

int64_t count_eq_int8_c( cInt8Slice slice, int8_t val );

int8_t const* find_int8_c( cInt8Slice slice, int8_t val );

int8_t const* max_int8_c( cInt8Slice slice );

int8_t const* min_int8_c( cInt8Slice slice );

bool prod_int8_c( cInt8Slice slice, int64_t res[static 1] );

void qsort_int8_slice_c( cVarInt8Slice slice );

void reverse_int8_slice_c( cVarInt8Slice slice );

void rotate_int8_slice_c( cVarInt8Slice slice, int64_t distance );

bool sum_int8_c( cInt8Slice slice, int64_t res[static 1] );

#endif
