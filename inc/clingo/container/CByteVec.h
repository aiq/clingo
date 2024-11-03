#ifndef CLINGO_CONTAINER_CBYTEVEC_H
#define CLINGO_CONTAINER_CBYTEVEC_H

#include "clingo/apidecl.h"
#include "clingo/container/vec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/type/cBytes.h"

/*******************************************************************************

*******************************************************************************/

VAL_VEC_DEF_C_(
   CLINGO_API, // LibApi
   CByteVec,   // VecType
   cByte,      // ValType
   byte_vec_c, // FuncName
   C_ByteVec   // Meta
)

/*******************************************************************************
 overall
*******************************************************************************/

#define add_many_to_byte_vec_c_( Vec, ... )                                    \
   add_many_to_byte_vec_c( (Vec), (cBytes)slice_c_( cByte, __VA_ARGS__ ) )
CLINGO_API inline bool add_many_to_byte_vec_c( CByteVec* vec, cBytes many )
{
   return add_array_to_byte_vec_c( vec, many.s, many.v );
}

CLINGO_API
CByteVec* build_byte_vec_c( int64_t cap, int64_t count, cByte* data );

CLINGO_API inline cBytes byte_vec_bytes_c( CByteVec const* vec )
{
   must_exist_c_( vec );

   return (cBytes){
      info_of_byte_vec_c( vec )->count,
      data_of_byte_vec_c( vec )
   };
}

CLINGO_API inline cVarBytes byte_vec_var_bytes_c( CByteVec* vec )
{
   must_exist_c_( vec );

   return (cVarBytes){
      info_of_byte_vec_c( vec )->count,
      var_data_of_byte_vec_c( vec )
   };
}

/*******************************************************************************
 io
*******************************************************************************/

#define write_byte_vec_c_( Rec, Vec )                                          \
   write_byte_vec_c( (Rec), (Vec), "" )
CLINGO_API bool write_byte_vec_c( cRecorder rec[static 1],
                       CByteVec const* vec,
                       char const fmt[static 1] );

#endif
