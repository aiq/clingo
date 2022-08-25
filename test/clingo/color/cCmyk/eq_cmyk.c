#include "clingo/color/cCmyk.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cCmyk a = cmyk_c_( 0.25f, 0.46f, 0.75f, 0.83f );
   cCmyk b = cmyk_c_( 0.83f, 0.75f, 0.46f, 0.25f );

   expect_c_(  eq_cmyk_c_( a, a ) );
   expect_c_( !eq_cmyk_c_( a, b ) );

   return finish_tap_c_();
}