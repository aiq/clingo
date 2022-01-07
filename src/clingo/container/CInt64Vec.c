#include "clingo/container/CInt64Vec.h"

/*******************************************************************************

*******************************************************************************/

VAL_VEC_IMPL_C_(
   ,              // Static
   CInt64Vec,     // VecType
   int64_t,       // ValType
   int64_vec_c,   // FuncName
   C_Int64VecMeta // Meta
)

/*******************************************************************************
 overall
*******************************************************************************/

extern inline bool add_many_to_int64_vec_c( CInt64Vec* vec, cInt64Slice many );

SLICE_OF_VEC_C_(
   int64_vec_c,   // FuncSuffix
   CInt64Vec,     // VecType
   cInt64Slice    // SliceType
)

VAR_SLICE_OF_VEC_C_(
   int64_vec_c,   // FuncSuffix
   CInt64Vec,     // VecType
   cVarInt64Slice // SliceType
)
