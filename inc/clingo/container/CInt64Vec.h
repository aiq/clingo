#ifndef CLINGO_CONTAINER_CINT64VEC_H
#define CLINGO_CONTAINER_CINT64VEC_H

#include "clingo/apidecl.h"
#include "clingo/container/vec.h"
#include "clingo/type/int64.h"

/*******************************************************************************

*******************************************************************************/

VAL_VEC_DEF_C_(
   CLINGO_API,    // LibApi
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
CLINGO_API inline bool add_many_to_int64_vec_c( CInt64Vec* vec, cInt64Slice many )
{
   return add_array_to_int64_vec_c( vec, many.s, many.v );
}

CLINGO_API cInt64Slice slice_of_int64_vec_c( CInt64Vec const* vec );

CLINGO_API cVarInt64Slice var_slice_of_int64_vec_c( CInt64Vec* vec );

#endif
