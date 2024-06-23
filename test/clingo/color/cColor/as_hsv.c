#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cHsv hsv = as_hsv_c( rgb_color_c( 0xabcdef ) );
   cHsv exp = hsv_c_( 210.0f, 0.285f, 0.937f );
   expect_at_c_( eq_hsv_c( hsv, exp, 0.0005f ) );

   return finish_tap_c_();
}