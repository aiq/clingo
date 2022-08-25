#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor color = greyscale_color_c( from_hsl_c_( 90.0, 0.9, 0.5 ) );
   expect_c_( eq_color_c( color, rgb_color_c( 0x808080 ) ) );

   return finish_tap_c_();
}
