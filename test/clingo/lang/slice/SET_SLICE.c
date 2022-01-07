#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

#define expect_cs_( VarChars, Exp )                                            \
   expect_c_(                                                                  \
      chars_is_c( as_chars_c( VarChars ), (Exp) )                              \
   )

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cVarChars dest = scalars_c_( 8, char );
   dest.s = set_chars_c_( dest, "abcdef" );
   expect_cs_( dest, "abcdef" );

   dest.s = 8;
   dest.s = set_chars_c_( dest, "abcdefgh" );
   expect_cs_( dest, "abcdefgh" );

   dest.s = 8;
   dest.s = set_chars_c_( dest, "abcdefghij" );
   expect_cs_( dest, "abcdefgh" );

   return finish_tap_c_();
}
