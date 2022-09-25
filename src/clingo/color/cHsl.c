#include "clingo/color/cHsl.h"

#include <iso646.h>

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

bool eq_hsl_c( cHsl a, cHsl b, float epsilon )
{
   return eq_float_c( a.hue, b.hue, epsilon ) and
          eq_float_c( a.saturation, b.saturation, epsilon ) and
          eq_float_c( a.lightness, b.lightness, epsilon );
}

bool read_hsl_c( cScanner sca[static 1],
                 cHsl hsl[static 1],
                 char const fmt[static 1] )
{
   return false;
}

bool write_hsl_c( cRecorder rec[static 1],
                  cHsl hsl,
                  char const fmt[static 1] )
{
   return false;
}