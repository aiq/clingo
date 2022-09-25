#include "clingo/type/int64.h"

#include "_/algo/prod.h"
#include "_/algo/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_int64_c( int64_t a, int64_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool uint64_to_int64_c( uint64_t src, int64_t dest[static 1] );

/*******************************************************************************
 swap
*******************************************************************************/

extern inline int64_t swap_int64_c( int64_t val );
extern inline int64_t swap_int64_from_c( int64_t val, c_ByteOrder order );
extern inline int64_t swap_int64_to_c( int64_t val, c_ByteOrder order );

/*******************************************************************************
 math
*******************************************************************************/

extern inline uint64_t hash_int64_c( int64_t val );
extern inline int64_t next_pow2_int64_c( int64_t val );

/*******************************************************************************
 algo
*******************************************************************************/

BSEARCH_C_(
   bsearch_int64_c,  // FuncName
   cInt64Slice,      // SliceType
   int64_t const,    // ValueType
   int64_t,          // SearchType
   cmp_int64_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

CMP_SLICE_C_(
   cmp_int64_slice_c,   // FuncName
   cInt64Slice,         // SliceType
   int64_t const,       // ValueType
   cmp_int64_c,         // ValueType
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_int64_c, // FuncName
   cInt64Slice,      // SliceType
   int64_t const,    // ValueType
   int64_t,          // SearchType
   cmp_int64_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MAX_C_(
   max_int64_c,   // FuncName
   cInt64Slice,   // SliceType
   int64_t const, // ValueType
   cmp_int64_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_int64_c,   // FuncName
   cInt64Slice,   // SliceType
   int64_t const, // ValueType
   cmp_int64_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_VAL_C_(
   find_int64_c,  // FuncName
   cInt64Slice,   // SliceType
   int64_t const, // ValueType
   int64_t,       // SearchType
   cmp_int64_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

PROD_C_(
   prod_int64_c,  // FuncName
   cInt64Slice,   // SliceType
   int64_t,       // ValueType
   int64_t,       // ResType
   imul64_c       // MulFunc
)

QSORT_C_(
   qsort_int64_slice_c, // FuncName
   cVarInt64Slice,      // SliceType
   int64_t,             // ValueType
   cmp_int64_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

REVERSE_C_(
   reverse_int64_slice_c,  // FuncName
   cVarInt64Slice,         // SliceType
   int64_t                 // ValueType
)

ROTATE_C_(
   rotate_int64_slice_c,   // FuncName
   cVarInt64Slice,         // SliceType
   int64_t                 // ValueType
)

SUM_C_(
   sum_int64_c,   // FuncName
   cInt64Slice,   // SliceType
   int64_t,       // ValueType
   int64_t,       // ResType
   iadd64_c       // AddFunc
)
