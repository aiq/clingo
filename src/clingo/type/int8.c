#include "clingo/type/int8.h"

#include "_/algo/prod.h"
#include "_/algo/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   int8_t,           // Type
   cInt8Slice,       // SliceType
   int8_slice_c,     // FuncName
   cVarInt8Slice,    // VarSliceType
   var_int8_slice_c  // VarFuncName
)

CHUNK_IMPL_C_(
   cInt8Chunk,       // ChunkType
   cInt8Slice,       // SliceType
   int8_chunk_c,     // FuncName
   cVarInt8Chunk,    // VarChunkType
   cVarInt8Slice,    // VarSliceType
   var_int8_chunk_c  // VarFuncName
)

WINDOW_IMPL_C_(
   cInt8Window,      // WindowType
   cInt8Slice,       // SliceType
   int8_window_c,    // FuncName
   cVarInt8Window,   // VarWindowType
   cVarInt8Slice,    // VarSliceType
   var_int8_window_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_int8_c( int8_t a, int8_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_int8_c( int64_t src, int8_t dest[static 1] );
extern inline bool uint64_to_int8_c( uint64_t src, int8_t dest[static 1] );

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_int8_slice_c, // FuncName
   cInt8Slice,       // SliceType
   int8_t const,     // ValueType
   cmp_int8_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

COUNT_EQ_C_(
   count_eq_int8_c,  // FuncName
   cInt8Slice,       // SliceType
   int8_t const,     // ValueType
   int8_t,           // SearchType
   cmp_int8_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_VAL_C_(
   find_int8_c,   // FuncName
   cInt8Slice,    // SliceType
   int8_t const,  // ValueType
   int8_t,        // SearchType
   cmp_int8_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MAX_C_(
   max_int8_c,    // FuncName
   cInt8Slice,    // SliceType
   int8_t const,  // ValueType
   cmp_int8_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_int8_c,    // FuncName
   cInt8Slice,    // SliceType
   int8_t const,  // ValueType
   cmp_int8_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

PROD_C_(
   prod_int8_c,   // FuncName
   cInt8Slice,    // SliceType
   int8_t,        // ValueType
   int64_t,       // ResType
   imul64_c       // MulFunc
)

QSORT_C_(
   qsort_int8_slice_c,  // FuncName
   cVarInt8Slice,       // SliceType
   int8_t,              // ValueType
   cmp_int8_c,          // FuncName
   do_deref_c_          // DoDeref
)

REVERSE_C_(
   reverse_int8_slice_c,   // FuncName
   cVarInt8Slice,          // SliceType
   int8_t                  // ValueType
)

ROTATE_C_(
   rotate_int8_slice_c, // FuncName
   cVarInt8Slice,       // SliceType
   int8_t               // ValueType
)

SUM_C_(
   sum_int8_c,    // FuncName
   cInt8Slice,    // SliceType
   int8_t,        // ValueType
   int64_t,       // ResType
   iadd64_c       // AddFunc
)
