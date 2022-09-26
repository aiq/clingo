#ifndef CLINGO_COLOR_CHSL_H
#define CLINGO_COLOR_CHSL_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cHsl
{
   float hue;
   float saturation;
   float lightness;
};

typedef struct cHsl cHsl;

SLICES_C_(
   cHsl,             // Type
   cHslSlice,        // SliceType
   cVarHslSlice      // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define hsl_c_( Hue, Saturation, Lightness )                                   \
   ((cHsl){ .hue=(Hue), .saturation=(Saturation), .lightness=(Lightness) })

#define eq_hsl_c_( A, B )                                                      \
   eq_hsl_c( (A), (B), FLT_EPSILON )
CLINGO_API bool eq_hsl_c( cHsl a, cHsl b, float epsilon );

#endif
