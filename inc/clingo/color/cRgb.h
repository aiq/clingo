#ifndef CLINGO_COLOR_CRGB_H
#define CLINGO_COLOR_CRGB_H

#include "clingo/apidecl.h"
#include "clingo/color/cRgb24.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cRgb
{
   float red;
   float green;
   float blue;
};
typedef struct cRgb cRgb;

SLICES_C_(
   cRgb,             // Type
   cRgbSlice,        // SliceType
   cVarRgbSlice      // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define rgb_c_( Red, Green, Blue )                                             \
   ((cRgb){ .red=(Red), .green=(Green), .blue=(Blue) })

CLINGO_API cRgb rgb_from_rgb24_c( cRgb24 rgb );

CLINGO_API cRgb24 rgb24_from_rgb_c( cRgb rgb );

#define eq_rgb_c_( A, B )                                                      \
   eq_rgb_c( (A), (B), FLT_EPSILON )
CLINGO_API bool eq_rgb_c( cRgb a, cRgb b, float epsilon );

#endif
