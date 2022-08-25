#include "clingo/color/cRgb.h"

#include <iso646.h>

#include "_/color/color_util.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

SLICE_IMPL_C_(
   cRgb,             // Type
   cRgbSlice,        // SliceType
   rgb_slice_c,      // FuncName
   cVarRgbSlice,     // VarSliceType
   var_rgb_slice_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

bool eq_rgb_c( cRgb a, cRgb b, float epsilon )
{
   return eq_float_c( a.red, b.red, epsilon ) and
          eq_float_c( a.green, b.green, epsilon ) and
          eq_float_c( a.blue, b.blue, epsilon );
}

cRgb rgb_from_rgb24_c( cRgb24 color )
{
   return rgb_c_(
      uint8_in_percent_c( color.red ),
      uint8_in_percent_c( color.green ),
      uint8_in_percent_c( color.blue )
   );
}

cRgb24 rgb24_from_rgb_c( cRgb color )
{
   return rgb24_c_(
      uint8_from_percent_c( color.red ),
      uint8_from_percent_c( color.green ),
      uint8_from_percent_c( color.blue )
   );
}

bool read_rgb_c( cScanner sca[static 1],
                 cRgb rgb[static 1],
                 char const fmt[static 1] )
{
   return false;
}

bool write_rgb_c( cRecorder rec[static 1],
                  cRgb rgb,
                  char const fmt[static 1] )
{
   return false;
}