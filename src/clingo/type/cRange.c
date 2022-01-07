#include "clingo/type/cRange.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   cRange,           // Type
   cRangeSlice,      // SliceType
   range_slice_c,    // FuncName
   cVarRangeSlice,   // VarSliceType
   var_range_slice_c // VarFuncName
)

CHUNK_IMPL_C_(
   cRangeChunk,      // ChunkType
   cRangeSlice,      // SliceType
   range_chunk_c,    // FuncName
   cVarRangeChunk,   // VarChunkType
   cVarRangeSlice,   // VarSliceType
   var_range_chunk_c // VarFuncName
)

WINDOW_IMPL_C_(
   cRangeWindow,        // WindowType
   cRangeSlice,         // SliceType
   range_window_c,      // FuncName
   cVarRangeWindow,     // VarWindowType
   cVarRangeSlice,      // VarSliceType
   var_range_window_c   // VarFuncName
)

/*******************************************************************************
********************************************************************+ Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int64_t clamp_into_range_c( cRange range, int64_t value );

extern inline bool eq_range_c( cRange a, cRange b );

extern inline bool in_range_c( cRange range, int64_t value );

extern inline bool range_is_valid_c( cRange range );

extern inline int64_t range_size_c( cRange range );

extern inline cRange shift_range_c( cRange range, int64_t distance );

