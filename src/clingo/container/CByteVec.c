#include "clingo/container/CByteVec.h"

#include "clingo/io/read_type.h"
#include "clingo/io/write_type.h"

/*******************************************************************************

*******************************************************************************/

VAL_VEC_IMPL_C_(
   ,              // Static
   CByteVec,      // VecType
   cByte,         // ValType
   byte_vec_c,    // FuncSuffix
   C_ByteVecMeta, // Meta
   do_nothing_c_  // InDepthCleanup
)

/*******************************************************************************
 overall
*******************************************************************************/

extern inline bool add_many_to_byte_vec_c( CByteVec* vec, cBytes many );

BUILD_VEC_C_(
   byte_vec_c,    // FuncSuffix
   CByteVec,      // VecType
   cByte,         // ValType
   C_ByteVecMeta  // Meta
)

extern inline cBytes byte_vec_bytes_c( CByteVec const* vec );

extern inline cVarBytes byte_vec_var_bytes_c( CByteVec* vec );

/*******************************************************************************
 io
*******************************************************************************/

bool write_byte_vec_c( cRecorder rec[static 1],
                       CByteVec const* vec,
                       char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( vec );
   must_exist_c_( fmt );

   cBytes slice = { vec->i.count, vec->data };
   return write_bytes_c( rec, slice, fmt );
}

