#ifndef CLINGO_LANG_CRANGE_H
#define CLINGO_LANG_CRANGE_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"
#include "clingo/type/char.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cRange
{
   int64_t min;
   int64_t max;
};
typedef struct cRange cRange;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cRange,           // Type
   cRangeSlice,      // SliceType
   cVarRangeSlice    // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/
// https://google.github.io/guava/releases/19.0/api/docs/com/google/common/collect/Range.html

// closed_open_range_c_ [a..b)
#define closed_open_range_c_( Start, End )                                     \
(                                                                              \
   (cRange){                                                                   \
      .min = (Start),                                                          \
      .max = (End)-1                                                           \
   }                                                                           \
)

// closed_range_c_ [a..b]
#define closed_range_c_( Start, End )                                          \
(                                                                              \
   (cRange){                                                                   \
      .min = (Start),                                                          \
      .max = (End)                                                             \
   }                                                                           \
)

// open_closed_range_c_ (a..b]
#define open_closed_range_c_( Start, End )                                     \
(                                                                              \
   (cRange){                                                                   \
      .min = (Start)+1,                                                        \
      .max = (End)                                                             \
   }                                                                           \
)

// open_range_c_ (a..b)
#define open_range_c_( Start, End )                                            \
(                                                                              \
   (cRange){                                                                   \
      .min = (Start)+1,                                                        \
      .max = (End)-1                                                           \
   }                                                                           \
)

#define sized_range_c_( Start, Size )                                          \
(                                                                              \
   (cRange){                                                                   \
      .min = (Start),                                                          \
      .max = (((Start) + (Size)) - 1)                                          \
   }                                                                           \
)

/*******************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int64_t clamp_into_range_c( cRange range, int64_t value )
{
   return clamp_c_( range.min, value, range.max );
}

CLINGO_API inline bool eq_range_c( cRange a, cRange b )
{
   return a.min == b.min and a.max == b.max;
}

CLINGO_API inline bool in_range_c( cRange range, int64_t value )
{
   return in_range_c_( range.min, value, range.max );
}

CLINGO_API inline bool range_is_valid_c( cRange range )
{
   return range.min <= range.max;
}

CLINGO_API inline int64_t range_size_c( cRange range )
{
   return ( range.max - range.min ) + 1;
}

CLINGO_API inline cRange shift_range_c( cRange range, int64_t distance )
{
   return closed_range_c_( range.min + distance, range.max + distance );
}

#endif
