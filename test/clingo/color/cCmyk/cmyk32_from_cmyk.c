#include "clingo/color/cCmyk.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cCmyk32 color = cmyk32_from_cmyk_c( cmyk_c_( 0.5f, 0.5f, 0.5f, 0.5f ) );
   expect_c_( eq_cmyk32_c( color, cmyk32_c_( 128, 128, 128, 128 ) ) );

   return finish_tap_c_();
}
