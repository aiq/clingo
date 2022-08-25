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

SLICE_DEF_C_(
   cHsv,             // Type
   cHsvSlice,        // SliceType
   hsv_slice_c,      // FuncName
   cVarHsvSlice,     // VarSliceType
   var_hsv_slice_c   // VarFuncName
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

#define read_hsv_c_( Sca, Hsv )                                                \
   read_hsv_c( (Sca), (Hsv), "" )
CLINGO_API bool read_hsv_c( cScanner sca[static 1],
                            cHsv hsv[static 1],
                            char const fmt[static 1] );

#define write_hsv_c_( Rec, Hsv )                                               \
   write_hsv_c( (Rec), (Hsv), "" )
CLINGO_API bool write_hsv_c( cRecorder rec[static 1],
                             cHsv hsv,
                             char const fmt[static 1] );

#endif
