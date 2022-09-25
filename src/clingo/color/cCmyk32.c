#include "clingo/color/cCmyk32.h"

#include "clingo/io/write.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline bool eq_cmyk32_c( cCmyk32 a, cCmyk32 b );

bool read_cmyk32_c( cScanner sca[static 1],
                    cCmyk32 cmyk[static 1],
                    char const fmt[static 1] )
{
   return false;
}

bool write_cmyk32_c( cRecorder rec[static 1],
                     cCmyk32 cmyk,
                     char const fmt[static 1] )
{
   cChars format = c_c( fmt );

   if ( is_empty_c_( format ) )
   {
      return write_c_( rec,
         "cmyk({u8},{u8},{u8},{u8})",
         cmyk.cyan, cmyk.magenta, cmyk.yellow, cmyk.key
      );
   }
   return false;
}
