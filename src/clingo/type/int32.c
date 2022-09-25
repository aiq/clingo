#include "clingo/type/int32.h"

#include "_/algo/prod.h"
#include "_/algo/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_int32_c( int32_t a, int32_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_int32_c( int64_t src, int32_t dest[static 1] );
extern inline bool uint64_to_int32_c( uint64_t src, int32_t dest[static 1] );

/*******************************************************************************
 swap
*******************************************************************************/

extern inline int32_t swap_int32_c( int32_t val );
extern inline int32_t swap_int32_from_c( int32_t val, c_ByteOrder order );
extern inline int32_t swap_int32_to_c( int32_t val, c_ByteOrder order );

/*******************************************************************************
 algo
*******************************************************************************/

BSEARCH_C_(
   bsearch_int32_c,  // FuncName
   cInt32Slice,      // SliceType
   int32_t const,    // ValueType
   int32_t,          // SearchType
   cmp_int32_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

CMP_SLICE_C_(
   cmp_int32_slice_c,   // FuncName
   cInt32Slice,         // SliceType
   int32_t const,       // ValueType
   cmp_int32_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_int32_c, // FuncName
   cInt32Slice,      // SliceType
   int32_t const,    // ValueType
   int32_t,          // SearchType
   cmp_int32_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_VAL_C_(
   find_int32_c,  // FuncName
   cInt32Slice,   // SliceType
   int32_t const, // ValueType
   int32_t,       // SearchType
   cmp_int32_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MAX_C_(
   max_int32_c,   // FuncName
   cInt32Slice,   // SliceType
   int32_t const, // ValueType
   cmp_int32_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_int32_c,   // FuncName
   cInt32Slice,   // SliceType
   int32_t const, // ValueType
   cmp_int32_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

PROD_C_(
   prod_int32_c,  // FuncName
   cInt32Slice,   // SliceType
   int32_t,       // ValueType
   int64_t,       // ResType
   imul64_c       // MulFunc
)

QSORT_C_(
   qsort_int32_slice_c, // FuncName
   cVarInt32Slice,      // SliceType
   int32_t,             // ValueType
   cmp_int32_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

REVERSE_C_(
   reverse_int32_slice_c,  // FuncName
   cVarInt32Slice,         // SliceType
   int32_t                 // ValueType
)

ROTATE_C_(
   rotate_int32_slice_c,   // FuncName
   cVarInt32Slice,         // SliceType
   int32_t                 // ValueType
)

SUM_C_(
   sum_int32_c,   // FuncName
   cInt32Slice,   // SliceType
   int32_t,       // ValueType
   int64_t,       // ResType
   iadd64_c       // AddFunc
)
