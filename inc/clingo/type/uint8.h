#ifndef CLINGO_TYPE_UINT8_H
#define CLINGO_TYPE_UINT8_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   uint8_t,             // Type
   cUint8Slice,         // SliceType
   uint8_slice_c,       // FuncName
   cVarUint8Slice,      // VarSliceType
   var_uint8_slice_c    // VarFuncName
)

CHUNK_DEF_C_(
   uint8_t,             // Type
   cUint8Chunk,         // ChunkType
   cUint8Slice,         // SliceType
   uint8_chunk_c,       // FuncName
   cVarUint8Chunk,      // VarChunkType
   cVarUint8Slice,      // VarSliceType
   var_uint8_chunk_c    // VarFuncName
)

WINDOW_DEF_C_(
   uint8_t,             // Type
   cUint8Window,        // WindowType
   cUint8Slice,         // SliceType
   uint8_window_c,      // FuncName
   cVarUint8Window,     // VarWindowType
   cVarUint8Slice,      // VarSliceType
   var_uint8_window_c   // VarFuncName
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
