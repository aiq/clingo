#include "clingo/color/cCmyk.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cCmyk color = cmyk_from_cmyk32_c( cmyk32_c_( 128, 128, 128, 128 ) );

   float f = 0.501960814f;
   expect_at_c_( eq_cmyk_c_( color, cmyk_c_( f, f, f, f ) ) );

   return finish_tap_c_();
}