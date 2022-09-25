#include "clingo/color/cRgb.h"

#include <iso646.h>

#include "_/color/color_util.h"
#include "clingo/type/float.h"

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
