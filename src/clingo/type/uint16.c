#include "clingo/type/uint16.h"

#include "_/prod.h"
#include "_/sum.h"
#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_uint16_c( uint16_t a, uint16_t b );

/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_uint16_c( int64_t src, uint16_t dest[static 1] );
extern inline bool uint64_to_uint16_c( uint64_t src, uint16_t dest[static 1] );

/*******************************************************************************
 swap
*******************************************************************************/

extern inline uint16_t swap_uint16_c( uint16_t val );
extern inline uint16_t swap_uint16_from_c( uint16_t val, c_ByteOrder order );
extern inline uint16_t swap_uint16_to_c( uint16_t val, c_ByteOrder order );

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_uint16_slice_c,  // FuncName
   cUint16Slice,        // SliceType
   uint16_t const,      // ValueType
   cmp_uint16_c,        // CmpFunc
   do_deref_c_          // DoDeref
)

COUNT_EQ_C_(
   count_eq_uint16_c,   // FuncName
   cUint16Slice,        // SliceType
   uint16_t const,      // ValueType
   uint16_t,            // SearchType
   cmp_uint16_c,        // CmpFunc
   do_deref_c_          // DoDeref
)

FIND_VAL_C_(
   find_uint16_c,    // FuncName
   cUint16Slice,     // SliceType
   uint16_t const,   // ValueType
   uint16_t,         // SearchType
   cmp_uint16_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MAX_C_(
   max_uint16_c,     // FuncName
   cUint16Slice,     // SliceType
   uint16_t const,   // ValueType
   cmp_uint16_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_MIN_C_(
   min_uint16_c,     // FuncName
   cUint16Slice,     // SliceType
   uint16_t const,   // ValueType
   cmp_uint16_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

PROD_C_(
   prod_uint16_c, // FuncName
   cUint16Slice,  // SliceType
   uint16_t,      // ValueType
   uint64_t,      // ResType
   umul64_c       // MulFunc
)

QSORT_C_(
   qsort_uint16_slice_c,   // FuncName
   cVarUint16Slice,        // SliceType
   uint16_t,               // ValueType
   cmp_uint16_c,           // CmpFunc
   do_deref_c_             // DoDeref
)

REVERSE_C_(
   reverse_uint16_slice_c, // FuncName
   cVarUint16Slice,        // SliceType
   uint16_t                // ValueType
)

ROTATE_C_(
   rotate_uint16_slice_c,  // FuncName
   cVarUint16Slice,        // SliceType
   uint16_t                // ValueType
)

SUM_C_(
   sum_uint16_c,  // FuncName
   cUint16Slice,  // SliceType
   uint16_t,      // ValueType
   uint64_t,      // ResType
   uadd64_c       // AddFunc
)
