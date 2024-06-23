#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor base = from_hsl_c_( 90.0f, 0.9f, 0.5f );
   cColor light = lighten_color_c( base, 0.1f );
   expect_at_c_( eq_color_c( light, rgb_color_c( 0x99f53d ) ) );

   return finish_tap_c_();
}