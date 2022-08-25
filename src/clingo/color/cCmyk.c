#include "clingo/color/cCmyk.h"

#include <iso646.h>

#include "_/color/color_util.h"
#include "clingo/io/write.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

SLICE_IMPL_C_(
   cCmyk,            // Type
   cCmykSlice,       // SliceType
   cmyk_slice_c,     // FuncName
   cVarCmykSlice,    // VarSliceType
   var_cmyk_slice_c  // VarFuncName
)

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

bool read_cmyk_c( cScanner sca[static 1],
                  cCmyk cmyk[static 1],
                  char const fmt[static 1] )
{
   return false;
}

bool write_cmyk_c( cRecorder rec[static 1],
                   cCmyk cmyk,
                   char const fmt[static 1] )
{
   cChars format = c_c( fmt );

   if ( is_empty_c_( format ) or chars_is_c( format, "()" ))
   {
      return write_c_( rec,
         "cmyk({f:f.3}%,{f:f.3}%,{f:f.3}%,{f:f.3}%)",
         cmyk.cyan*100.0, cmyk.magenta*100.0, cmyk.yellow*100.0, cmyk.key*100.0
      );
   }

   return false;
}