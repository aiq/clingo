#ifndef CLINGO_COLOR_CCMYK_H
#define CLINGO_COLOR_CCMYK_H

#include "clingo/apidecl.h"
#include "clingo/color/cCmyk32.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cCmyk
{
   float cyan;
   float magenta;
   float yellow;
   float key;
};
typedef struct cCmyk cCmyk;

SLICE_DEF_C_(
   cCmyk,            // Type
   cCmykSlice,       // SliceType
   cVarCmykSlice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define cmyk_c_( Cyan, Magenta, Yellow, Key )                                  \
   ((cCmyk){ .cyan=(Cyan), .magenta=(Magenta), .yellow=(Yellow), .key=(Key) })

#define eq_cmyk_c_( A, B )                                                     \
   eq_cmyk_c( (A), (B), FLT_EPSILON )
CLINGO_API bool eq_cmyk_c( cCmyk a, cCmyk b, float epsilon );

CLINGO_API cCmyk32 cmyk32_from_cmyk_c( cCmyk cmyk );

CLINGO_API cCmyk cmyk_from_cmyk32_c( cCmyk32 cCmyk32 );

#endif
