#include "clingo/color/cHsv.h"

#include <iso646.h>

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

SLICE_IMPL_C_(
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

bool eq_hsv_c( cHsv a, cHsv b, float epsilon )
{
   return eq_float_c( a.hue, b.hue, epsilon ) and
          eq_float_c( a.saturation, b.saturation, epsilon ) and
          eq_float_c( a.value, b.value, epsilon );
}

bool read_hsv_c( cScanner sca[static 1],
                 cHsv hsv[static 1],
                 char const fmt[static 1] )
{
   return false;
}

bool write_hsv_c( cRecorder rec[static 1],
                  cHsv hsv,
                  char const fmt[static 1] )
{
   return false;
}
