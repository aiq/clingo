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

SLICE_DEF_C_(
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

#define read_hsl_c_( Sca, Hsl )                                                \
   read_hsl_c( (Sca), (Hsl), "" )
CLINGO_API bool read_hsl_c( cScanner sca[static 1],
                            cHsl hsl[static 1],
                            char const fmt[static 1] );

#define write_hsl_c_( Rec, Hsl )                                               \
   write_hsl_c( (Rec), (Hsl), "" )
CLINGO_API bool write_hsl_c( cRecorder rec[static 1],
                             cHsl hsl,
                             char const fmt[static 1] );

#endif
