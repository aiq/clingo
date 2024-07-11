#include "clingo/type/int16.h"

#include "_/prod.h"
#include "_/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_int16_c( int16_t a, int16_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_int16_c( int64_t src, int16_t dst[static 1] );
extern inline bool uint64_to_int16_c( uint64_t src, int16_t dst[static 1] );

/*******************************************************************************
 swap
*******************************************************************************/

extern inline int16_t swap_int16_c( int16_t val );
extern inline int16_t swap_int16_from_c( int16_t val, c_ByteOrder order );
extern inline int16_t swap_int16_to_c( int16_t val, c_ByteOrder order );

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_int16_slice_c,   // FuncName
   cInt16Slice,         // SliceType
   int16_t const,       // ValueType
   cmp_int16_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_int16_c, // FuncName
   cInt16Slice,      // SliceType
   int16_t const,    // ValueType
   int16_t,          // SearchType
   cmp_int16_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_VAL_C_(
   find_int16_c,  // FuncName
   cInt16Slice,   // SliceType
   int16_t const, // ValueType
   int16_t,       // SearchType
   cmp_int16_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MAX_C_(
   max_int16_c,   // FuncName
   cInt16Slice,   // SliceType
   int16_t const, // ValueType
   cmp_int16_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

FIND_MIN_C_(
   min_int16_c,   // FuncName
   cInt16Slice,   // SliceType
   int16_t const, // ValueType
   cmp_int16_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

PROD_C_(
   prod_int16_c,  // FuncName
   cInt16Slice,   // SliceType
   int16_t,       // ValueType
   int64_t,       // ResType
   imul64_c       // MulFunc
)

QSORT_C_(
   qsort_int16_slice_c, // FuncName
   cVarInt16Slice,      // SliceType
   int16_t,             // ValueType
   cmp_int16_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

REVERSE_C_(
   reverse_int16_slice_c,  // FuncName
   cVarInt16Slice,         // SliceType
   int16_t                 // ValueType
)

ROTATE_C_(
   rotate_int16_slice_c,   // FuncName
   cVarInt16Slice,         // SliceType
   int16_t                 // ValueType
)

SUM_C_(
   sum_int16_c,   // FuncName
   cInt16Slice,   // SliceType
   int16_t,       // ValueType
   int64_t,       // ResType
   iadd64_c       // AddFunc
)
