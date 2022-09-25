#include "clingo/type/uint8.h"

#include "_/algo/prod.h"
#include "_/algo/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_uint8_c( uint8_t a, uint8_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_uint8_c( int64_t src, uint8_t dest[static 1] );
extern inline bool uint64_to_uint8_c( uint64_t src, uint8_t dest[static 1] );

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_uint8_slice_c,   // FuncName
   cUint8Slice,         // SliceType
   uint8_t const,       // ValueType
   cmp_uint8_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_uint8_c, // FuncName
   cUint8Slice,      // SliceType
   uint8_t const,    // ValueType
   uint8_t,          // SearchType
   cmp_uint8_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_VAL_C_(
   find_uint8_c,  // FuncName
   cUint8Slice,   // SliceType
   uint8_t const, // ValueType
   uint8_t,       // SearchType
   cmp_uint8_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MAX_C_(
   max_uint8_c,   // FuncName
   cUint8Slice,   // SliceType
   uint8_t const, // ValueType
   cmp_uint8_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_uint8_c,   // FuncName
   cUint8Slice,   // SliceType
   uint8_t const, // ValueType
   cmp_uint8_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

PROD_C_(
   prod_uint8_c,  // FuncName
   cUint8Slice,   // SliceType
   uint8_t,       // ValueType
   uint64_t,      // ResType
   umul64_c       // MulFunc
)

QSORT_C_(
   qsort_uint8_slice_c, // FuncName
   cVarUint8Slice,      // SliceType
   uint8_t,             // ValueType
   cmp_uint8_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

REVERSE_C_(
   reverse_uint8_slice_c,  // FuncName
   cVarUint8Slice,         // SliceType
   uint8_t                 // ValueType
)

ROTATE_C_(
   rotate_uint8_slice_c,   // FuncName
   cVarUint8Slice,         // SliceType
   uint8_t                 // ValueType
)

SUM_C_(
   sum_uint8_c,   // FuncName
   cUint8Slice,   // SliceType
   uint8_t,       // ValueType
   uint64_t,      // ResType
   uadd64_c       // AddFunc
)
