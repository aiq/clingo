#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cHsl hsl = as_hsl_c( color_c_( 128, 255, 0, 255 ) );
   cHsl exp = hsl_c_( 89.9f, 1.0f, 0.5f );
   expect_at_c_( eq_hsl_c( hsl, exp, 0.05f ) );

   return finish_tap_c_();
}