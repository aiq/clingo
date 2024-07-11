#include "clingo/color/cCmyk.h"

#include <iso646.h>

#include "_/color_util.h"
#include "clingo/io/write.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cCmyk32 cmyk32_from_cmyk_c( cCmyk color )
{
   return cmyk32_c_(
      uint8_from_percent_c( color.cyan ),
      uint8_from_percent_c( color.magenta ),
      uint8_from_percent_c( color.yellow ),
      uint8_from_percent_c( color.key )
   );
}

cCmyk cmyk_from_cmyk32_c( cCmyk32 color )
{
   return cmyk_c_(
      uint8_in_percent_c( color.cyan ),
      uint8_in_percent_c( color.magenta ),
      uint8_in_percent_c( color.yellow ),
      uint8_in_percent_c( color.key )
   );
}

bool eq_cmyk_c( cCmyk a, cCmyk b, float epsilon )
{
   return eq_float_c( a.cyan, b.cyan, epsilon ) and
          eq_float_c( a.magenta, b.magenta, epsilon ) and
          eq_float_c( a.yellow, b.yellow, epsilon ) and
          eq_float_c( a.key, b.key, epsilon );
}
