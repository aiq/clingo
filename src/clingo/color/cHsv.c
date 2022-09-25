#include "clingo/color/cHsv.h"

#include <iso646.h>

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
