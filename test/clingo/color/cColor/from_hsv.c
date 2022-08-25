#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor c = from_hsv_c_( 90.0f, 1.0f, 0.5f );
   expect_c_( eq_color_c( c, rgb_color_c( 0x408000 ) ) );

   return finish_tap_c_();
}