#ifndef CLINGO_CONTAINER_CBYTE_VEC_H
#define CLINGO_CONTAINER_CBYTE_VEC_H

#include "clingo/container/vec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/type/cBytes.h"

/*******************************************************************************

*******************************************************************************/

VAL_VEC_DEF_C_(
   CByteVec,      // VecType
   cByte,         // ValType
   byte_vec_c,    // FuncName
   C_ByteVecMeta  // Meta
)

/*******************************************************************************
 overall
*******************************************************************************/

#define add_many_to_byte_vec_c_( Vec, ... )                                    \
   add_many_to_byte_vec_c( (Vec), (cBytes)slice_c_( cByte, __VA_ARGS__ ) )
inline bool add_many_to_byte_vec_c( CByteVec* vec, cBytes many )
{
   return add_array_to_byte_vec_c( vec, many.s, many.v );
}

/*******************************************************************************
 io
*******************************************************************************/

#define write_byte_vec_c_( Rec, Vec )                                          \
   write_byte_vec_c( (Rec), (Vec), "" )
bool write_byte_vec_c( cRecorder rec[static 1],
                       CByteVec const* vec,
                       char const fmt[static 1] );

#endif
