#ifndef CLINGO_TYPE_BOOL_H
#define CLINGO_TYPE_BOOL_H

#include <stdbool.h>

#include "clingo/apidecl.h"
#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

SLICE_DEF_C_(
   bool,             // Type
   cBoolSlice,       // SliceType
   bool_slice_c,     // FuncName
   cVarBoolSlice,    // VarSliceType
   var_bool_slice_c  // VarFuncName
)

CHUNK_DEF_C_(
   bool,             // Type
   cBoolChunk,       // ChunkType
   cBoolSlice,       // SliceType
   bool_chunk_c,     // FuncName
   cVarBoolChunk,    // VarChunkType
   cVarBoolSlice,    // VarSliceType
   var_bool_chunk_c  // VarFuncName
)

WINDOW_DEF_C_(
   bool,             // Type
   cBoolWindow,      // WindowType
   cBoolSlice,       // SliceType
   bool_window_c,    // FuncName
   cVarBoolWindow,   // VarWindowType
   cVarBoolSlice,    // VarSliceType
   var_bool_window_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
**************+*****************************************************************
 overall
*******************************************************************************/

#define bool_c_( Value )                                                       \
(                                                                              \
   (bool)(Value)                                                               \
)

CLINGO_API inline int cmp_bool_c( bool a, bool b )
{
   return a - b;
}

/*******************************************************************************
 bool
*******************************************************************************/

CLINGO_API bool and_bool_slice_values_c( cBoolSlice slice );

CLINGO_API int64_t count_eq_bool_c( cBoolSlice slice, bool val );

CLINGO_API bool or_bool_slice_values_c( cBoolSlice slice );

#endif
