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
   C_ByteVecMeta  // Meta
)

/*******************************************************************************
 overall
*******************************************************************************/

extern inline bool add_many_to_byte_vec_c( CByteVec* vec, cBytes many );

SLICE_OF_VEC_C_(
   byte_vec_c, // FuncSuffix
   CByteVec,   // VecType
   cBytes      // SliceType
)

VAR_SLICE_OF_VEC_C_(
   byte_vec_c, // FuncSuffix
   CByteVec,   // VecType
   cVarBytes   // SliceType
)

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

   cBytes slice = bytes_c( vec->i.count, vec->data );
   return write_bytes_c( rec, slice, fmt );
}

