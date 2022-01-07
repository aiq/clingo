#ifndef CLINGO_CONTAINER_CINT64_VEC_H
#define CLINGO_CONTAINER_CINT64_VEC_H

#include "clingo/container/vec.h"
#include "clingo/type/int64.h"

/*******************************************************************************

*******************************************************************************/

VAL_VEC_DEF_C_(
   CInt64Vec,     // VecType
   int64_t,       // ValType
   int64_vec_c,   // FuncName
   C_Int64VecMeta // Meta
)

/*******************************************************************************
 overall
*******************************************************************************/

#define add_many_to_int64_vec_c_( Vec, ... )                                   \
   add_many_to_int64_vec_c(                                                    \
      (Vec), (cInt64Slice)slice_c_( int64_t, __VA_ARGS__ )                     \
   )
inline bool add_many_to_int64_vec_c( CInt64Vec* vec, cInt64Slice many )
{
   return add_array_to_int64_vec_c( vec, many.s, many.v );
}

cInt64Slice slice_of_int64_vec_c( CInt64Vec const* vec );

cVarInt64Slice var_slice_of_int64_vec_c( CInt64Vec* vec );

#endif
