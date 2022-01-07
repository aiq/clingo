#include "clingo/type/uint32.h"

#include "_/algo/prod.h"
#include "_/algo/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   uint32_t,            // Type
   cUint32Slice,        // SliceType
   uint32_slice_c,      // FuncName
   cVarUint32Slice,     // VarSliceType
   var_uint32_slice_c   // VarFuncName
)

CHUNK_IMPL_C_(
   cUint32Chunk,        // ChunkType
   cUint32Slice,        // SliceType
   uint32_chunk_c,      // FuncName
   cVarUint32Chunk,     // VarChunkType
   cVarUint32Slice,     // VarSliceType
   var_uint32_chunk_c   // VarFuncName
)

WINDOW_IMPL_C_(
   cUint32Window,       // WindowType
   cUint32Slice,        // SliceType
   uint32_window_c,     // FuncName
   cVarUint32Window,    // VarWindowType
   cVarUint32Slice,     // VarSliceType
   var_uint32_window_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_uint32_c( uint32_t a, uint32_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_uint32_c( int64_t src, uint32_t dest[static 1] );
extern inline bool uint64_to_uint32_c( uint64_t src, uint32_t dest[static 1] );

/*******************************************************************************
 swap
*******************************************************************************/

extern inline uint32_t swap_uint32_c( uint32_t val );
extern inline uint32_t swap_uint32_from_c( uint32_t val, c_ByteOrder order );
extern inline uint32_t swap_uint32_to_c( uint32_t val, c_ByteOrder order );

/*******************************************************************************
 math
*******************************************************************************/

extern inline uint32_t next_pow2_uint32_c( uint32_t val );

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_uint32_slice_c,  // FuncName
   cUint32Slice,        // SliceType
   uint32_t const,      // ValueType
   cmp_uint32_c,        // CmpFunc
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_uint32_c,   // FuncName
   cUint32Slice,        // SliceType
   uint32_t const,      // ValueType
   uint32_t,            // SearchType
   cmp_uint32_c,        // CmpFunc
   do_deref_c_          // DoDeref
)

FIND_VAL_C_(
   find_uint32_c,    // FuncName
   cUint32Slice,     // SliceType
   uint32_t const,   // ValueType
   uint32_t,         // SearchType
   cmp_uint32_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MAX_C_(
   max_uint32_c,     // FuncName
   cUint32Slice,     // SliceType
   uint32_t const,   // ValueType
   cmp_uint32_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MIN_C_(
   min_uint32_c,     // FuncName
   cUint32Slice,     // SliceType
   uint32_t const,   // ValueType
   cmp_uint32_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

PROD_C_(
   prod_uint32_c, // FuncName
   cUint32Slice,  // SliceType
   uint32_t,      // ValueType
   uint64_t,      // ResType
   umul64_c       // MulFunc
)

QSORT_C_(
   qsort_uint32_slice_c,   // FuncName
   cVarUint32Slice,        // SliceType
   uint32_t,               // ValueType
   cmp_uint32_c,           // CmpFunc
   do_deref_c_             // DoDeref
)

REVERSE_C_(
   reverse_uint32_slice_c, // FuncName
   cVarUint32Slice,        // SliceType
   uint32_t                // ValueType
)

ROTATE_C_(
   rotate_uint32_slice_c,  // FuncName
   cVarUint32Slice,        // SliceType
   uint32_t                // ValueType
)

SUM_C_(
   sum_uint32_c,  // FuncName
   cUint32Slice,  // SliceType
   uint32_t,      // ValueType
   uint64_t,      // ResType
   uadd64_c       // AddFunc
)
