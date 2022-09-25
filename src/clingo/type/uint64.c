#include "clingo/type/uint64.h"

#include "_/algo/prod.h"
#include "_/algo/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_uint64_c( uint64_t a, uint64_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_uint64_c( int64_t src, uint64_t dest[static 1] );

/*******************************************************************************
 swap
*******************************************************************************/

extern inline uint64_t swap_uint64_c( uint64_t val );
extern inline uint64_t swap_uint64_from_c( uint64_t val, c_ByteOrder order );
extern inline uint64_t swap_uint64_to_c( uint64_t val, c_ByteOrder order );

/*******************************************************************************
 math
*******************************************************************************/

extern inline bool is_pow2_uint64_c( uint64_t val );
extern inline uint8_t log2_uint64_c( uint64_t val );
extern inline uint64_t next_pow2_uint64_c( uint64_t val );

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_uint64_slice_c,  // FuncName
   cUint64Slice,        // SliceType
   uint64_t const,      // ValueType
   cmp_uint64_c,        // CmpFunc
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_uint64_c,   // FuncName
   cUint64Slice,        // SliceType
   uint64_t const,      // ValueType
   uint64_t,            // SearchType
   cmp_uint64_c,        // CmpFunc
   do_deref_c_          // DoDeref
)

FIND_VAL_C_(
   find_uint64_c,    // FuncName
   cUint64Slice,     // SliceType
   uint64_t const,   // ValueType
   uint64_t,         // SearchType
   cmp_uint64_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MAX_C_(
   max_uint64_c,     // FuncName
   cUint64Slice,     // SliceType
   uint64_t const,   // ValueType
   cmp_uint64_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MIN_C_(
   min_uint64_c,     // FuncName
   cUint64Slice,     // SliceType
   uint64_t const,   // ValueType
   cmp_uint64_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

PROD_C_(
   prod_uint64_c, // FuncName
   cUint64Slice,  // SliceType
   uint64_t,      // ValueType
   uint64_t,      // ResType
   umul64_c       // MulFunc
)

QSORT_C_(
   qsort_uint64_slice_c,   // FuncName
   cVarUint64Slice,        // SliceType
   uint64_t,               // ValueType
   cmp_uint64_c,           // CmpFunc
   do_deref_c_             // DoDeref
)

REVERSE_C_(
   reverse_uint64_slice_c, // FuncName
   cVarUint64Slice,        // SliceType
   uint64_t                // ValueType
)

ROTATE_C_(
   rotate_uint64_slice_c,  // FuncName
   cVarUint64Slice,        // SliceType
   uint64_t                // ValueType
)

SUM_C_(
   sum_uint64_c,  // FuncName
   cUint64Slice,  // SliceType
   uint64_t,      // ValueType
   uint64_t,      // ResType
   uadd64_c       // AddFunc
)
