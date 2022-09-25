#ifndef CLINGO_TYPE_BOOL_H
#define CLINGO_TYPE_BOOL_H

#include <stdbool.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

SLICE_DEF_C_(
   bool,             // Type
   cBoolSlice,       // SliceType
   cVarBoolSlice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
**************+*****************************************************************
 overall
*******************************************************************************/

#define bool_c_( Value )                                                       \
(                                                                              \
   (bool)(Value)                                                               \
)

CLINGO_API inline int cmp_bool_c( bool a, bool b )
{
   return a - b;
}

/*******************************************************************************
 bool
*******************************************************************************/

CLINGO_API bool and_bool_slice_values_c( cBoolSlice slice );

CLINGO_API int64_t count_eq_bool_c( cBoolSlice slice, bool val );

CLINGO_API bool or_bool_slice_values_c( cBoolSlice slice );

#endif
