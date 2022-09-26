#ifndef CLINGO_COLOR_CHSV_H
#define CLINGO_COLOR_CHSV_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cHsv
{
   float hue;
   float saturation;
   float value;
};

typedef struct cHsv cHsv;

SLICES_C_(
   cHsv,             // Type
   cHsvSlice,        // SliceType
   cVarHsvSlice      // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define hsv_c_( Hue, Saturation, Value ) \
   ((cHsv){ .hue=(Hue), .saturation=(Saturation), .value=(Value) })

#define eq_hsv_c_( A, B )                                                      \
   eq_hsv_c( (A), (B), FLT_EPSILON )
CLINGO_API bool eq_hsv_c( cHsv a, cHsv b, float epsilon );

#endif
